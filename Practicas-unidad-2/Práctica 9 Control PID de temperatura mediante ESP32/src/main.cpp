#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include <Keypad.h>

// -------- LCD I2C (SDA: 27, SCL: 26) --------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// -------- SENSOR LM35 --------
const int pinLM35 = 35;

// -------- SERVOMOTOR (Pin 13) --------
const uint8_t SERVO_PIN = 13;
Servo miServomotor;
const int ANG_MIN = 5;
const int ANG_MAX = 175;

// -------- KEYPAD 4x4 --------
const byte FILAS = 4;
const byte COLUMNAS = 4;
char teclas[FILAS][COLUMNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte pinesFilas[FILAS] = {19, 18, 5, 4};
byte pinesColumnas[COLUMNAS] = {32, 33, 25, 14};

Keypad teclado = Keypad(
  makeKeymap(teclas),
  pinesFilas,
  pinesColumnas,
  FILAS,
  COLUMNAS
);

// -------- ENTRADA NUMERICA --------
String entrada = "";
const size_t MAX_CARACTERES = 5;

// -------- VARIABLES DE PROCESO Y PID --------
float tempReal = 0.0;
float tempAnterior = 0.0;
float setpoint = 30.0;
float error = 0.0;
float errorAnterior = 0.0;

// Constantes PID (ajustables desde el teclado)
float Kp = 0.0;
float Ki = 0.0;
float Kd = 0.0;

// Términos del PID discreto
float P = 0.0;
float I = 0.0;
float D = 0.0;
float salidaP = 0.0;         // u[k] limitada (0-100%)
float salidaSinSaturar = 0.0;
const float Ts = 3.0;        // Periodo de muestreo en segundos

// Control de estados para el teclado (A=SP, B=Kp, C=Ki, D=Kd)
enum Estado { NORMAL, SP_EDIT, KP_EDIT, KI_EDIT, KD_EDIT };
Estado estado = NORMAL;

// -------- LECTURA DEL LM35 --------
float leerLM35Promedio() {
  long sumaMv = 0;
  int numMuestras = 5;
  for (int i = 0; i < numMuestras; i++) {
    sumaMv += analogReadMilliVolts(pinLM35);
    delay(10);
  }
  float promedioMv = sumaMv / (float)numMuestras;

  float offsetMv = 100.0;
  float mvReales = promedioMv - offsetMv;
  if (mvReales < 0) mvReales = 0;

  return mvReales / 10.0;
}

// -------- ACTUALIZAR LCD --------
void actualizarLCDNormal() {
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(tempReal, 1);
  lcd.print((char)223);
  lcd.print("C SP:");
  lcd.print(setpoint, 1);
  lcd.print(" ");

  lcd.setCursor(0, 1);
  lcd.print("E:");
  lcd.print(error, 1);
  lcd.print("C OUT:");
  lcd.print((int)salidaP);
  lcd.print("%   ");
}

// -------- CONFIGURACION --------
void setup() {
  Serial.begin(115200);
  analogSetAttenuation(ADC_2_5db);

  // LCD
  Wire.begin(27, 26);
  lcd.init();
  lcd.backlight();

  // Servomotor
  miServomotor.setPeriodHertz(50);
  miServomotor.attach(SERVO_PIN, 500, 2400);
  miServomotor.write(ANG_MIN);

  lcd.setCursor(0, 0);
  lcd.print("PID Iniciado");
  delay(1500);
  lcd.clear();

  tempReal = leerLM35Promedio();
  tempAnterior = tempReal;
}

// -------- PROGRAMA PRINCIPAL --------
void loop() {
  // 1. Lectura del Teclado Matricial
  char tecla = teclado.getKey();

  if (tecla != NO_KEY) {
    Serial.print("Tecla: ");
    Serial.println(tecla);

    if (tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D') {
      if (tecla == 'A') estado = SP_EDIT;
      else if (tecla == 'B') estado = KP_EDIT;
      else if (tecla == 'C') estado = KI_EDIT;
      else if (tecla == 'D') estado = KD_EDIT;

      entrada = "";
      lcd.clear();
      lcd.setCursor(0, 0);
      if (estado == SP_EDIT) lcd.print("Nuevo Set Point:");
      else if (estado == KP_EDIT) lcd.print("Nueva Kp:");
      else if (estado == KI_EDIT) lcd.print("Nueva Ki:");
      else if (estado == KD_EDIT) lcd.print("Nueva Kd:");

      lcd.setCursor(0, 1);
      lcd.print("Val: _");
    }
    else if (tecla == '#') {
      if (entrada.length() > 0) {
        float val = entrada.toFloat();
        if (estado == SP_EDIT) {
          setpoint = val;
          Serial.print("Nuevo SP: ");
          Serial.println(setpoint);
        } else if (estado == KP_EDIT) {
          Kp = val;
          Serial.print("Nuevo Kp: ");
          Serial.println(Kp);
        } else if (estado == KI_EDIT) {
          Ki = val;
          Serial.print("Nuevo Ki: ");
          Serial.println(Ki);
        } else if (estado == KD_EDIT) {
          Kd = val;
          Serial.print("Nuevo Kd: ");
          Serial.println(Kd);
        }
      }
      estado = NORMAL;
      entrada = "";
      lcd.clear();
    }
    else if ((tecla >= '0' && tecla <= '9') || tecla == '*') {
      if (estado != NORMAL) {
        if (tecla == '*' && entrada.indexOf('.') == -1) {
          entrada += '.';
        } else if (tecla != '*' && entrada.length() < MAX_CARACTERES) {
          entrada += tecla;
        }
        lcd.setCursor(0, 1);
        lcd.print("Val: ");
        lcd.print(entrada);
        lcd.print("_   ");
      }
    }
  }

  // 2. Ejecución del algoritmo PID discreto cada Ts (3 segundos)
  static unsigned long ultimoMuestreo = 0;
  unsigned long ahora = millis();
  if (ahora - ultimoMuestreo >= (unsigned long)(Ts * 1000.0)) {
    ultimoMuestreo = ahora;

    tempAnterior = tempReal;
    tempReal = leerLM35Promedio();
    errorAnterior = error;
    error = setpoint - tempReal;

    // --- ACCIÓN PROPORCIONAL ---
    P = Kp * error;

    // --- ACCIÓN INTEGRAL CON PROTECCIÓN ANTI-WINDUP ---
    bool saturadoArriba = (salidaP >= 100.0 && error > 0);
    bool saturadoAbajo = (salidaP <= 0.0 && error < 0);
    if (!saturadoArriba && !saturadoAbajo) {
      I = I + (Ki * error * Ts);
      I = constrain(I, 0.0, 100.0);
    }

    // --- ACCIÓN DERIVATIVA ---
    D = -Kd * (tempReal - tempAnterior) / Ts;

    // --- ECUACIÓN GENERAL DEL PID ---
    salidaSinSaturar = P + I + D;

    // --- SATURACIÓN DE LA SALIDA (0% a 100%) ---
    if (salidaSinSaturar < 0.0) {
      salidaP = 0.0;
    } else if (salidaSinSaturar > 100.0) {
      salidaP = 100.0;
    } else {
      salidaP = salidaSinSaturar;
    }

    // Mapeo de la salida al servomotor
    int anguloServo = map((int)(salidaP * 10), 0, 1000, ANG_MIN, ANG_MAX);
    miServomotor.write(anguloServo);

    // Depuración en Monitor Serie
    Serial.print("[PID 9] SP: "); Serial.print(setpoint);
    Serial.print(" | T: "); Serial.print(tempReal, 1);
    Serial.print(" | Err: "); Serial.print(error, 1);
    Serial.print(" | OUT: "); Serial.print(salidaP, 1);
    Serial.print("% | Ang: "); Serial.println(anguloServo);

    // Actualizar LCD
    if (estado == NORMAL) {
      actualizarLCDNormal();
    }
  }
}

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include <Keypad.h>

// LCD I2C (SDA: 27, SCL: 26)[cite: 14]
LiquidCrystal_I2C lcd(0x27, 16, 2);

// SENSOR LM35
const int pinLM35 = 35; //[cite: 14]

// SERVOMOTOR (Pin 13)[cite: 14]
const uint8_t SERVO_PIN = 13;
Servo miServomotor;
const int ANG_MIN = 5;
const int ANG_MAX = 175;

// KEYPAD 4x4[cite: 14]
const byte FILAS = 4;
const byte COLUMNAS = 4;
char teclas[FILAS][COLUMNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte pinesFilas[FILAS] = {19, 18, 5, 4};        //[cite: 14]
byte pinesColumnas[COLUMNAS] = {32, 33, 25, 14}; //[cite: 14]

Keypad teclado = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

// ENTRADA NUMERICA
String entrada = "";
const size_t MAX_CARACTERES = 5;

// VARIABLES DE PROCESO Y CONTROL[cite: 14]
float tempReal = 0.0, setpoint = 30.0, error = 0.0;
float salidaP = 0.0;
float Kp = 10.0;
const float MARGEN_ESTABILIDAD = 1.3; 

// Control de estados para el ingreso por teclado (A=SP, B=Kp)[cite: 14]
enum Estado { NORMAL, SP_EDIT, KP_EDIT };
Estado estado = NORMAL;

// LECTURA DEL LM35 (Filtro de 7 muestras + offset 100 mV)[cite: 15]
float leerLM35Promedio() {
  long sumaMv = 0;
  int numMuestras = 7;
  for (int i = 0; i < numMuestras; i++) {
    sumaMv += analogReadMillivolts(pinLM35);
    delay(10);
  }
  float promedioMv = sumaMv / (float)numMuestras;
  float offsetMv = 100.0; 
  float mvReales = promedioMv - offsetMv;
  if (mvReales < 0) mvReales = 0;
  return mvReales / 10.0;
}

// ACTUALIZAR LCD[cite: 15]
void actualizarLCDNormal() {
  lcd.setCursor(0, 0);
  lcd.print("T:"); 
  lcd.print(tempReal, 1); 
  lcd.print((char)223); 
  lcd.print("C SP:"); 
  lcd.print(setpoint, 1); 
  
  lcd.setCursor(0, 1);
  lcd.print("E:"); 
  lcd.print(error, 1); 
  lcd.print("C OUT:");
  lcd.print((int)salidaP); 
  lcd.print("%   ");
}

void setup() {
  Serial.begin(115200);
  analogSetAttenuation(ADC_2_5db);
  
  // LCD[cite: 15]
  Wire.begin(27, 26);
  lcd.init();
  lcd.backlight();
  
  // Servomotor[cite: 15, 16]
  miServomotor.setPeriodHertz(50);
  miServomotor.attach(SERVO_PIN, 500, 2400);
  miServomotor.write(ANG_MIN);
  
  lcd.setCursor(0, 0);
  lcd.print("Sistema Iniciando...");
  delay(1500);
  lcd.clear();
  tempReal = leerLM35Promedio();
}

void loop() {
  // 1. Leer teclado matricial[cite: 16]
  char tecla = teclado.getKey();
  if (tecla != NO_KEY) {
    Serial.print("Tecla: ");
    Serial.println(tecla);
    
    if (tecla == 'A' || tecla == 'B') {
      estado = (tecla == 'A') ? SP_EDIT : KP_EDIT;
      entrada = "";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(estado == SP_EDIT ? "Nuevo Set Point:" : "Nueva Kp:");
      lcd.setCursor(0, 1);
      lcd.print("val: _");
    } 
    else if (tecla == '*') {
      entrada = "";
      if (estado != NORMAL) {
        lcd.setCursor(0, 1);
        lcd.print("val: _    ");
      }
    } 
    else if (tecla == '#') {
      if (entrada.length() > 0) {
        float val = entrada.toFloat();
        if (estado == SP_EDIT) {
          setpoint = val;
          Serial.print("Nuevo Set Point aplicado: "); 
          Serial.println(setpoint);
        } else if (estado == KP_EDIT) {
          Kp = val;
          Serial.print("Nueva Kp aplicada: "); 
          Serial.println(Kp);
        }
        estado = NORMAL;
        entrada = "";
        lcd.clear();
      }
    } 
    else if ((tecla >= '0' && tecla <= '9') || tecla == '.') {
      if (estado != NORMAL) {
        if (tecla == '.' && entrada.indexOf('.') == -1) entrada += '.';
        else if (tecla != '.' && entrada.length() < MAX_CARACTERES) entrada += tecla;
        
        lcd.setCursor(0, 1);
        lcd.print("val: ");
        lcd.print(entrada);
        lcd.print(" ");
      }
    }
  }

  // 2. Control proporcional y lectura de temperatura cada 3 segundos[cite: 16]
  static unsigned long ultimoMuestreo = 0;
  unsigned long ahora = millis();
  if (ahora - ultimoMuestreo >= 3000) {
    ultimoMuestreo = ahora;
    
    tempReal = leerLM35Promedio();
    error = setpoint - tempReal; //[cite: 17]
    
    // ECUACIÓN PROPORCIONAL PURA[cite: 17]
    salidaP = Kp * error;
    salidaP = constrain(salidaP, 0.0, 100.0);
    
    int anguloServo = map((int)(salidaP * 10), 0, 1000, ANG_MIN, ANG_MAX);
    miServomotor.write(anguloServo);
    
    // Depuración en Monitor Serie[cite: 17]
    Serial.print("[CONTROL PROPORCIONAL] ");
    Serial.print("SP: "); Serial.print(setpoint);
    Serial.print(" Real: "); Serial.print(tempReal, 1);
    Serial.print(" Err: "); Serial.print(error, 1);
    Serial.print(" | Out: "); Serial.print(salidaP, 1);
    Serial.print("% | Ang: "); Serial.println(anguloServo);
  }

  // Actualizar pantalla solo si estamos en modo normal[cite: 17]
  if (estado == NORMAL) {
    actualizarLCDNormal();
  }
}

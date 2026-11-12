#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LM35_PIN 32
#define PIN_RELE_FOCO 18
#define PIN_RELE_PELTIER 19
#define PIN_RELE_CIRCULACION 23

#define RELE_ON HIGH
#define RELE_OFF LOW

const byte FILAS = 4;
const byte COLUMNAS = 4;
char teclas[FILAS][COLUMNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte pinesFilas[FILAS] = {4, 12, 13, 14};
byte pinesColumnas[COLUMNAS] = {25, 26, 27, 33};

Keypad teclado = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

enum EstadoTeclado { NORMAL, EDITANDO_LL, EDITANDO_HL };
EstadoTeclado estadoActual = NORMAL;
String entrada = "";

const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;
long total = 0;

int ll = 35;
int hl = 50;
unsigned long previousMillis = 0;
const long updateInterval = 500;
float temperaturaActual = 0.0;
int porcentajeActual = 0;

void actualizarPantalla() {
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperaturaActual, 1);
  lcd.print((char)223);
  lcd.print("C P:");
  lcd.print(porcentajeActual);
  lcd.print("%  ");

  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  
  if (estadoActual == EDITANDO_LL) {
    lcd.print("Nuevo LL:");
    lcd.print(entrada);
    lcd.print("_");
  } else if (estadoActual == EDITANDO_HL) {
    lcd.print("Nuevo HL:");
    lcd.print(entrada);
    lcd.print("_");
  } else {
    lcd.print("LL:");
    lcd.print(ll);
    lcd.print("  HL:");
    lcd.print(hl);
    lcd.print("   ");
  }
}

float leerTemperaturaFiltrada() {
    total = total - readings[readIndex];
    readings[readIndex] = analogRead(LM35_PIN);
    total = total + readings[readIndex];
    readIndex = (readIndex + 1) % numReadings;
    float promedioADC = (float)total / numReadings;
    float voltaje = (promedioADC * 3300.0) / 4095.0;
    return voltaje / 10.0;
}

void setup() {
    Serial.begin(115200);
    analogReadResolution(12);
    analogSetPinAttenuation(LM35_PIN, ADC_11db);
    for (int i = 0; i < numReadings; i++) {
        readings[i] = 0;
    }
    Wire.begin(21, 22);
    lcd.init();
    lcd.backlight();
    pinMode(PIN_RELE_FOCO, OUTPUT);
    pinMode(PIN_RELE_PELTIER, OUTPUT);
    pinMode(PIN_RELE_CIRCULACION, OUTPUT);
    digitalWrite(PIN_RELE_FOCO, RELE_OFF);
    digitalWrite(PIN_RELE_PELTIER, RELE_OFF);
    digitalWrite(PIN_RELE_CIRCULACION, RELE_ON); 
    lcd.setCursor(0, 0);
    lcd.print("Sistema Control");
    lcd.setCursor(0, 1);
    lcd.print("Iniciando...");
    delay(1500);
    lcd.clear();
}

void loop() {
    unsigned long currentMillis = millis();
    char tecla = teclado.getKey();
    if (tecla != NO_KEY) {
        if (tecla == 'A') {
            estadoActual = EDITANDO_HL;
            entrada = "";
        } else if (tecla == 'B') {
            estadoActual = EDITANDO_LL;
            entrada = "";
        } else if (tecla == '*') {
            estadoActual = NORMAL;
            entrada = "";
        } else if (tecla == '#') {
            if (entrada.length() > 0) {
                int valor = entrada.toInt();
                if (estadoActual == EDITANDO_HL && valor > ll && valor <= 60) {
                    hl = valor;
                } else if (estadoActual == EDITANDO_LL && valor >= 0 && valor < hl) {
                    ll = valor;
                }
            }
            estadoActual = NORMAL;
            entrada = "";
        } else if (isDigit(tecla)) {
            if (estadoActual != NORMAL && entrada.length() < 3) {
                entrada += tecla;
            }
        }
        actualizarPantalla();
    }

    if (currentMillis - previousMillis >= updateInterval) {
        previousMillis = currentMillis;
        temperaturaActual = leerTemperaturaFiltrada();

        if (temperaturaActual <= (float)ll) {
            digitalWrite(PIN_RELE_FOCO, RELE_ON);
            digitalWrite(PIN_RELE_PELTIER, RELE_OFF);
        } else if (temperaturaActual >= (float)hl) {
            digitalWrite(PIN_RELE_FOCO, RELE_OFF);
            digitalWrite(PIN_RELE_PELTIER, RELE_ON);
        }

        porcentajeActual = 0;
        if (temperaturaActual > 30.0 && temperaturaActual < 60.0) {
            porcentajeActual = (int)(((temperaturaActual - 30.0) / 30.0) * 100.0);
        } else if (temperaturaActual >= 60.0) {
            porcentajeActual = 100;
        }

        actualizarPantalla();
    }
}

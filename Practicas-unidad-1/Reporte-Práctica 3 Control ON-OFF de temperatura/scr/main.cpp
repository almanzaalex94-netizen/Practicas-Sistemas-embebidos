#include <Arduino.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "LiquidCrystal_I2C.h"

// ==========================================
// CONFIGURACIÓN DS18B20
// ==========================================
#define DS18B20_PIN 4
OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

// ==========================================
// CONFIGURACIÓN LCD I2C
// ==========================================
#define SDA_PIN 21
#define SCL_PIN 22
#define LCD_ADDRESS 0x27
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

// ==========================================
// PINES DE BOTONES
// ==========================================
#define PIN_BTN_UP 12
#define PIN_BTN_DOWN 13
#define PIN_BTN_SEL 14

// ==========================================
// PINES DE RELÉ
// ==========================================
#define PIN_RELE_FOCO 18        // Foco / Calentador en D18
#define PIN_RELE_PELTIER 19     // Celda Peltier + Disipador en D19
#define PIN_RELE_CIRCULACION 23 // Ventilador de circulación en D23[cite: 37]

#define RELE_ON HIGH
#define RELE_OFF LOW

// ==========================================
// VARIABLES GLOBALES
// ==========================================
int ll = 35; 
int hl = 50; 
int modo_edicion = 0; // 0 = Normal, 1 = Editar LL, 2 = Editar HL[cite: 37]

bool lastSelState = HIGH;
bool lastUpState = HIGH;
bool lastDownState = HIGH;
unsigned long lastDebounceTimeSel = 0;
unsigned long lastDebounceTimeUp = 0;
unsigned long lastDebounceTimeDown = 0;
const unsigned long debounceDelay = 200; 

unsigned long previousMillis = 0;
const long updateInterval = 500; 

void setup() {
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN);
    sensors.begin();
    
    lcd.init();
    lcd.backlight();

    pinMode(PIN_BTN_UP, INPUT_PULLUP);
    pinMode(PIN_BTN_DOWN, INPUT_PULLUP);
    pinMode(PIN_BTN_SEL, INPUT_PULLUP);

    pinMode(PIN_RELE_FOCO, OUTPUT);
    pinMode(PIN_RELE_PELTIER, OUTPUT);
    pinMode(PIN_RELE_CIRCULACION, OUTPUT);

    digitalWrite(PIN_RELE_FOCO, RELE_OFF);
    digitalWrite(PIN_RELE_PELTIER, RELE_OFF);
    digitalWrite(PIN_RELE_CIRCULACION, RELE_ON); 

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sistema Control");
    lcd.setCursor(0, 1);
    lcd.print("Iniciando...");
    delay(2000);
    lcd.clear();
}

void loop() {
    unsigned long currentMillis = millis();

    // 1. LECTURA Y LÓGICA DE BOTÓN SELECCIÓN (D14)[cite: 37]
    bool readingSel = digitalRead(PIN_BTN_SEL);
    if (readingSel == LOW && lastSelState == HIGH && (currentMillis - lastDebounceTimeSel > debounceDelay)) {
        lastDebounceTimeSel = currentMillis;
        modo_edicion++;
        if (modo_edicion > 2) modo_edicion = 0;
        
        if (modo_edicion == 0) {
            lcd.noBlink();
        } else {
            lcd.blink();
        }
        lastUpState = digitalRead(PIN_BTN_UP);
        lastDownState = digitalRead(PIN_BTN_DOWN);
        lastDebounceTimeUp = currentMillis;
        lastDebounceTimeDown = currentMillis;
    }
    lastSelState = readingSel;

    // 2. LECTURA DE BOTONES SUBIR (D12) Y BAJAR (D13)[cite: 37]
    if (modo_edicion != 0) {
        bool readingUp = digitalRead(PIN_BTN_UP);
        if (readingUp == LOW && lastUpState == HIGH && (currentMillis - lastDebounceTimeUp > debounceDelay)) {
            lastDebounceTimeUp = currentMillis;
            if (modo_edicion == 1 && ll < 60) ll += 5;
            if (modo_edicion == 2 && hl < 60) hl += 5;
            previousMillis = currentMillis - updateInterval; 
        }
        lastUpState = readingUp;

        bool readingDown = digitalRead(PIN_BTN_DOWN);
        if (readingDown == LOW && lastDownState == HIGH && (currentMillis - lastDebounceTimeDown > debounceDelay)) {
            lastDebounceTimeDown = currentMillis;
            if (modo_edicion == 1 && ll > 30) ll -= 5;
            if (modo_edicion == 2 && hl > 30) hl -= 5;
            previousMillis = currentMillis - updateInterval; 
        }
        lastDownState = readingDown;
    } else {
        lastUpState = digitalRead(PIN_BTN_UP);
        lastDownState = digitalRead(PIN_BTN_DOWN);
    }

    // 3. CONTROL DE SENSORES, RELÉS Y PANTALLA LCD[cite: 37]
    if (currentMillis - previousMillis >= updateInterval) {
        previousMillis = currentMillis;
        sensors.requestTemperatures();
        float temperatura = sensors.getTempCByIndex(0);

        if (temperatura != DEVICE_DISCONNECTED_C) {
            if (temperatura <= ll) {
                digitalWrite(PIN_RELE_FOCO, RELE_ON);
                digitalWrite(PIN_RELE_PELTIER, RELE_OFF);
            } 
            else if (temperatura >= hl) {
                digitalWrite(PIN_RELE_FOCO, RELE_OFF);
                digitalWrite(PIN_RELE_PELTIER, RELE_ON);
            }
        }

        int porcentaje = 0;
        if (temperatura <= 30.0) {
            porcentaje = 0;
        } else if (temperatura >= 60.0) {
            porcentaje = 100;
        } else {
            porcentaje = (int)(((temperatura - 30.0) / 30.0) * 100.0);
        }

        lcd.setCursor(0, 0);
        lcd.print("T:");
        if (temperatura == DEVICE_DISCONNECTED_C) {
            lcd.print("Error ");
        } else {
            lcd.print(temperatura, 1);
            lcd.print("C ");
        }
        lcd.print("P:");
        lcd.print(porcentaje);
        lcd.print("%   ");

        lcd.setCursor(0, 1);
        lcd.print("LL:");
        lcd.print(ll);
        lcd.print("  HL:");
        lcd.print(hl);
        lcd.print("   ");

        if (modo_edicion == 1) {
            lcd.setCursor(3, 1);  
        } else if (modo_edicion == 2) {
            lcd.setCursor(10, 1); 
        }
    }
}

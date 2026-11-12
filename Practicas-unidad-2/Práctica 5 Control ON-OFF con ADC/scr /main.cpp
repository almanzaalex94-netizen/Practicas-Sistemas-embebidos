#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SDA_PIN 21
#define SCL_PIN 22
#define LCD_ADDRESS 0x27
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

#define PIN_SENSOR_LM35 34
#define PIN_POT_LL 35
#define PIN_POT_HL 32

#define PIN_RELE_FOCO 18
#define PIN_RELE_PELTIER 19
#define PIN_RELE_CIRCULACION 23

#define RELE_ON HIGH
#define RELE_OFF LOW

int ll = 35;
int hl = 50;
unsigned long previousMillis = 0;
const long updateInterval = 500;

void setup() {
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN);
    lcd.init();
    lcd.backlight();
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

    int lecturaPotLL = analogRead(PIN_POT_LL);
    int lecturaPotHL = analogRead(PIN_POT_HL);
    ll = map(lecturaPotLL, 0, 4095, 30, 60);
    hl = map(lecturaPotHL, 0, 4095, 30, 60);
    if (ll >= hl) {
        ll = hl - 1;
    }

    if (currentMillis - previousMillis >= updateInterval) {
        previousMillis = currentMillis;

        int rawADC = analogRead(PIN_SENSOR_LM35);
        float voltaje = (rawADC * 3300.0) / 4095.0;
        float temperatura = voltaje / 10.0;

        if (temperatura <= (float)ll) {
            digitalWrite(PIN_RELE_FOCO, RELE_ON);
            digitalWrite(PIN_RELE_PELTIER, RELE_OFF);
        } else if (temperatura >= (float)hl) {
            digitalWrite(PIN_RELE_FOCO, RELE_OFF);
            digitalWrite(PIN_RELE_PELTIER, RELE_ON);
        }

        int porcentaje = 0;
        if (temperatura > 30.0 && temperatura < 60.0) {
            porcentaje = (int)(((temperatura - 30.0) / 30.0) * 100.0);
        } else if (temperatura >= 60.0) {
            porcentaje = 100;
        }

        lcd.setCursor(0, 0);
        lcd.print("T:");
        lcd.print(temperatura, 1);
        lcd.print("C P:");
        lcd.print(porcentaje);
        lcd.print("%  ");

        lcd.setCursor(0, 1);
        lcd.print("LL:");
        lcd.print(ll);
        lcd.print("  HL:");
        lcd.print(hl);
        lcd.print("   ");
    }
}

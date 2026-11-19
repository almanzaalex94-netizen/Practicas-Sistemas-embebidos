#include "Wire.h"
#include "LiquidCrystal_I2C.h"

// ==================== PINES ====================
const int TRIG_PIN = 13;
const int ECHO_PIN = 14;
const int BTN_SELECT = 18;
const int BTN_UP = 32;
const int BTN_DOWN = 19;
const int RELAY_LLENAR = 4;
const int RELAY_DRENAR = 5;

// =================== CONFIGURACIÓN RELÉ ===================
const int RELAY_ON = LOW;
const int RELAY_OFF = HIGH;

// =================== PARÁMETROS DEL TANQUE ===================
const float DISTANCIA_VACIO = 11.5;
const float DISTANCIA_LLENO = 4.0;
const float ALTURA_MAXIMA = DISTANCIA_VACIO - DISTANCIA_LLENO;
const float CAPACIDAD_LITROS = 0.589;

// =================== AJUSTES ===================
const int PASO = 5;

// =================== VARIABLES ===================
int LL = 20;
int HL = 80;
int AL = 0;
float litrosActuales = 0.0;

enum Estado { ESPERA, LLENANDO, DRENANDO };
Estado estadoActual = ESPERA;

unsigned long ultimaLecturaBotones = 0;
unsigned long ultimaMedicion = 0;
unsigned long ultimoChequeoI2C = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("=== Modo FUENTE ===");
  Serial.println("Sube LL y HL para empezar el ciclo");

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BTN_SELECT, INPUT_PULLUP);
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(RELAY_LLENAR, OUTPUT);
  pinMode(RELAY_DRENAR, OUTPUT);

  digitalWrite(RELAY_LLENAR, RELAY_OFF);
  digitalWrite(RELAY_DRENAR, RELAY_OFF);

  Wire.begin(26, 27);
  Wire.setClock(100000);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");
  delay(1000);
}

// =================== RECUPERACIÓN I2C ===================
void recoverI2C() {
  Serial.println("Reiniciando I2C...");
  Wire.end();
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  delay(10);
  if (digitalRead(26) == LOW) {
    pinMode(27, OUTPUT);
    for (int i = 0; i < 16; i++) {
      digitalWrite(27, HIGH); delayMicroseconds(5);
      digitalWrite(27, LOW); delayMicroseconds(5);
    }
  }
  pinMode(26, OUTPUT);
  digitalWrite(26, HIGH); delayMicroseconds(5);
  digitalWrite(27, HIGH); delayMicroseconds(5);
  Wire.begin(26, 27);
  Wire.setClock(100000);
  lcd.init();
  lcd.backlight();
  Serial.println("I2C recuperado");
}

// =================== MEDIR DISTANCIA ===================
float medirDistancia() {
  float medidas[5];
  int validas = 0;

  for (int i = 0; i < 5; i++) {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duracion = pulseIn(ECHO_PIN, HIGH, 30000);
    float d = duracion * 0.0343 / 2;

    if (d > 0.5 && d < 30) {
      medidas[validas] = d;
      validas++;
    }
    delay(3);
  }

  if (validas == 0) return DISTANCIA_VACIO;

  // Ordenar para obtener la mediana
  for (int i = 0; i < validas - 1; i++) {
    for (int j = 0; j < validas - i - 1; j++) {
      if (medidas[j] > medidas[j + 1]) {
        float temp = medidas[j];
        medidas[j] = medidas[j + 1];
        medidas[j + 1] = temp;
      }
    }
  }
  return medidas[validas / 2];
}

// =================== CONTROL MODO FUENTE ===================
void controlarFuente() {
  if (HL == 0 || LL == 0 || HL <= LL) {
    digitalWrite(RELAY_LLENAR, RELAY_OFF);
    digitalWrite(RELAY_DRENAR, RELAY_OFF);
    estadoActual = ESPERA;
    return;
  }

  if (estadoActual == LLENANDO) {
    digitalWrite(RELAY_DRENAR, RELAY_OFF);
    digitalWrite(RELAY_LLENAR, RELAY_ON);
    if (AL >= HL) {
      estadoActual = DRENANDO;
      digitalWrite(RELAY_LLENAR, RELAY_OFF);
      digitalWrite(RELAY_DRENAR, RELAY_ON);
      Serial.println("HL alcanzado -> DRENANDO");
    }
  } 
  else if (estadoActual == DRENANDO) {
    digitalWrite(RELAY_LLENAR, RELAY_OFF);
    digitalWrite(RELAY_DRENAR, RELAY_ON);
    if (AL <= LL) {
      estadoActual = LLENANDO;
      digitalWrite(RELAY_DRENAR, RELAY_OFF);
      digitalWrite(RELAY_LLENAR, RELAY_ON);
      Serial.println("LL alcanzado -> LLENANDO");
    }
  } 
  else {
    if (AL <= LL) {
      estadoActual = LLENANDO;
      digitalWrite(RELAY_LLENAR, RELAY_ON);
      digitalWrite(RELAY_DRENAR, RELAY_OFF);
      Serial.println("Iniciando ciclo -> LLENANDO");
    } else if (AL >= HL) {
      estadoActual = DRENANDO;
      digitalWrite(RELAY_LLENAR, RELAY_OFF);
      digitalWrite(RELAY_DRENAR, RELAY_ON);
      Serial.println("Iniciando ciclo -> DRENANDO");
    }
  }
}

// =================== LOOP ===================
void loop() {
  unsigned long ahora = millis();

  // Leer botones cada 150ms
  if (ahora - ultimaLecturaBotones >= 150) {
    ultimaLecturaBotones = ahora;

    bool select = (digitalRead(BTN_SELECT) == LOW);
    bool up = (digitalRead(BTN_UP) == LOW);
    bool down = (digitalRead(BTN_DOWN) == LOW);

    if (select) {
      if (up) { HL += PASO; if (HL > 100) HL = 100; }
      if (down) { HL -= PASO; if (HL < 0) HL = 0; }
    } else {
      if (up) { LL += PASO; if (LL > 100) LL = 100; }
      if (down) { LL -= PASO; if (LL < 0) LL = 0; }
    }

    if (HL <= LL && HL > 0 && LL > 0) {
      HL = LL + PASO;
      if (HL > 100) HL = 100;
    }
  }

  // Medir sensor cada 100ms
  if (ahora - ultimaMedicion >= 100) {
    ultimaMedicion = ahora;

    float distancia = medirDistancia();
    if (distancia < DISTANCIA_LLENO || distancia <= 0) distancia = DISTANCIA_LLENO;
    if (distancia > DISTANCIA_VACIO) distancia = DISTANCIA_VACIO;

    float nivelAguaCm = DISTANCIA_VACIO - distancia;
    if (nivelAguaCm < 0) nivelAguaCm = 0;
    if (nivelAguaCm > ALTURA_MAXIMA) nivelAguaCm = ALTURA_MAXIMA;

    AL = (int)((nivelAguaCm / ALTURA_MAXIMA) * 100.0);
    litrosActuales = (AL / 100.0) * CAPACIDAD_LITROS;

    controlarFuente();

    char fila0[17];
    char fila1[17];
    const char* indicador = "--";

    if (estadoActual == LLENANDO) indicador = "^^";
    else if (estadoActual == DRENANDO) indicador = "vv";

    snprintf(fila0, sizeof(fila0), "LL %-3d AL %-3d %s", LL, AL, indicador);
    snprintf(fila1, sizeof(fila1), "HL %-3d L: %-4.2f", HL, litrosActuales);

    lcd.setCursor(0, 0); lcd.print(fila0);
    lcd.setCursor(0, 1); lcd.print(fila1);
  }

  // Chequeo I2C cada 2 segundos
  if (ahora - ultimoChequeoI2C > 2000) {
    ultimoChequeoI2C = ahora;
    Wire.beginTransmission(0x27);
    if (Wire.endTransmission() != 0) {
      Serial.println("LCD no responde, reiniciando I2C...");
      recoverI2C();
    }
  }

  delay(10);
}

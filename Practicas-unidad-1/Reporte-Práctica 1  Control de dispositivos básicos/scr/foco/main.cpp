#define RELAY 2
#define SW1 21
#define SW2 19
#define ENCIENDE_FOCO digitalWrite(RELAY, HIGH)
#define APAGA_FOCO digitalWrite(RELAY, LOW)
#define PRESSED(x) digitalRead(x) == 0

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(RELAY, OUTPUT);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  APAGA_FOCO; // Estado inicial: foco apagado
}

void loop() {
  if (PRESSED(SW1)) {
    ENCIENDE_FOCO;
    Serial.println("Boton 1 pulsado: Foco encendido");
    delay(100);
  }
  if (PRESSED(SW2)) {
    APAGA_FOCO;
    Serial.println("Boton 2 pulsado: Foco apagado");
    delay(100);
  }
}

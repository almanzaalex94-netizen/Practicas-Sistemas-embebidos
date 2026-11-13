#include <Arduino.h>
#include <ESP32Servo.h>
#include <DFRobotDFPlayerMini.h>

// ==================== PINES ====================
#define PIN_PIR    27   
#define PIN_SERVO  18   
#define PIN_LED    4    // LED rojo (apagado por defecto)
#define DF_RX      25   
#define DF_TX      26   

// ==================== AJUSTES ====================
const int   ANGULO_CERRADA = 20;     
const int   ANGULO_ABIERTA = 70;     
const unsigned long PERIODO_MOV         = 250;   
const unsigned long DURACION_ANIM_MS    = 6000;  // Duración de la animación (6 seg)
const unsigned long PAUSA_REINICIO_MS   = 3000;  // Espera antes de volver a activarse

// Pistas en la MicroSD:
const int   PISTA_IDLE   = 1;        // Audio de fondo / ambiente (0001.mp3)
const int   PISTA_ACTIVA = 2;        // Audio cuando detecta movimiento (0002.mp3)
const int   VOLUMEN      = 15;       

// ==================== OBJETOS Y VARIABLES ====================
Servo servo;
HardwareSerial dfSerial(2);
DFRobotDFPlayerMini player;

bool activo = false;
bool bocaAbierta = false;
unsigned long inicioAnimacion = 0;
unsigned long ultimoMovimiento = 0;
unsigned long finAnimacion = 0;
unsigned long ultimoInicioIdle = 0; 
unsigned long intervaloActualIdle = 10000; // Tiempo para el fondo

void setup() {
  Serial.begin(115200);

  // El LED inicia completamente apagado
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  pinMode(PIN_PIR, INPUT);

  servo.setPeriodHertz(50);
  servo.attach(PIN_SERVO, 500, 2400);
  servo.write(ANGULO_CERRADA);

  dfSerial.begin(9600, SERIAL_8N1, DF_RX, DF_TX);
  
  Serial.println("Esperando 4 segundos a que despierte el DFPlayer...");
  delay(4000); 

  player.begin(dfSerial, false, true);
  player.volume(VOLUMEN);
  delay(500);
  
  // Arrancar la primera pista de fondo
  player.play(PISTA_IDLE);
  ultimoInicioIdle = millis();
  intervaloActualIdle = random(8000, 20000);
  Serial.println("Audio de fondo iniciado.");

  Serial.println("Calentando sensor PIR...");
  delay(20000);
  Serial.println("¡Sistema animatrónico listo!");
}

void loop() {
  unsigned long ahora = millis();

  if (!activo) {
    // REPRODUCCIÓN DE FONDO CON TIEMPO ALEATORIO
    if (ahora - ultimoInicioIdle >= intervaloActualIdle) {
      player.play(PISTA_IDLE);
      ultimoInicioIdle = ahora;
      
      // Siguiente intervalo aleatorio de fondo (entre 8 y 25 segundos)
      intervaloActualIdle = random(8000, 25000);
      
      Serial.println("Reproduciendo audio de fondo. Próximo en: " + String(intervaloActualIdle / 1000) + " segundos.");
    }

    // Detección de movimiento (PIR)
    if (digitalRead(PIN_PIR) == HIGH && (ahora - finAnimacion >= PAUSA_REINICIO_MS)) {
      activo = true;
      inicioAnimacion = ahora;
      ultimoMovimiento = ahora;
      
      // Encender el LED solo durante la animación
      digitalWrite(PIN_LED, HIGH);
      
      // Reproducir pista activa
      player.play(PISTA_ACTIVA);
      Serial.println("¡Presencia detectada! LED encendido y reproduciendo Pista Activa.");
    }
  } else {
    // Animación en curso: mover mandíbula
    if (ahora - ultimoMovimiento >= PERIODO_MOV) {
      ultimoMovimiento = ahora;
      bocaAbierta = !bocaAbierta;
      servo.write(bocaAbierta ? ANGULO_ABIERTA : ANGULO_CERRADA);
    }

    // Fin de la animación
    if (ahora - inicioAnimacion >= DURACION_ANIM_MS) {
      activo = false;
      bocaAbierta = false;
      servo.write(ANGULO_CERRADA);
      
      // Apagar el LED al terminar
      digitalWrite(PIN_LED, LOW);
      
      // CAMBIO: En lugar de reproducir audio, dejamos 10 segundos exactos de silencio (10000 ms)
      // y a partir de ahí se retoman los tiempos aleatorios.
      ultimoInicioIdle = millis();
      intervaloActualIdle = 10000; 
      
      finAnimacion = ahora;
      Serial.println("Animación terminada. LED apagado, guardando 10 segundos de silencio...");
    }
  }
}

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>

// --- CONFIGURACIÓN DE LA PANTALLA LCD I2C ---
LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- PINES ---
const int pinServo = 13;   
const int botonSubir = 33; 
const int botonBajar = 32; 

// --- LÍMITES DE SEGURIDAD MECÁNICA ---
const int ANGULO_MINIMO = 5;     // 0% de potencia
const int ANGULO_MAXIMO = 175;   // 100% de potencia

// --- VARIABLES ---
int porcentajeActual = 0;        // Va de 0 a 100%
unsigned long ultimoTiempo = 0;  
const int tiempoAntirrebote = 250; // Tiempo de espera entre pulsaciones

Servo miServomotor;

void setup() {
  Serial.begin(115200);

  // Inicializar bus I2C con los pines del LCD (SDA: 27, SCL: 26)
  Wire.begin(27, 26);

  // Configurar botones con resistencia interna
  pinMode(botonSubir, INPUT_PULLUP);
  pinMode(botonBajar, INPUT_PULLUP);

  // Inicializar LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Control Dimmer");
  lcd.setCursor(0, 1);
  lcd.print("Listo!");
  delay(1500);

  // Inicializar Servo
  miServomotor.attach(pinServo, 500, 2400);
  miServomotor.write(ANGULO_MINIMO); // Posición inicial 0%

  actualizarPantallaYServo();
}

void loop() {
  // Leer botones solo si ha pasado el tiempo de antirrebote
  if (millis() - ultimoTiempo > tiempoAntirrebote) {
    
    // Botón Subir presionado (LOW porque usa INPUT_PULLUP)
    if (digitalRead(botonSubir) == LOW) {
      porcentajeActual += 10;
      if (porcentajeActual > 100) {
        porcentajeActual = 100;
      }
      actualizarPantallaYServo();
      ultimoTiempo = millis();
    }
    
    // Botón Bajar presionado
    if (digitalRead(botonBajar) == LOW) {
      porcentajeActual -= 10;
      if (porcentajeActual < 0) {
        porcentajeActual = 0;
      }
      actualizarPantallaYServo();
      ultimoTiempo = millis();
    }
  }
}

// --- FUNCIÓN PARA ACTUALIZAR TODO DE GOLPE ---
void actualizarPantallaYServo() {
  // 1. Mapear porcentaje a grados seguros del servo
  int anguloDestino = map(porcentajeActual, 0, 100, ANGULO_MINIMO, ANGULO_MAXIMO);
  
  // 2. Mover el servo directamente
  miServomotor.write(anguloDestino);

  // 3. Actualizar la Pantalla LCD
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Potencia: ");
  lcd.print(porcentajeActual);
  lcd.print("%   ");

  lcd.setCursor(0, 1);
  lcd.print("Angulo:   ");
  lcd.print(anguloDestino);
  lcd.print(" deg   ");

  // Depuración opcional en Serial
  Serial.print("Porcentaje: ");
  Serial.print(porcentajeActual);
  Serial.print("% -> Ángulo: ");
  Serial.println(anguloDestino);
}

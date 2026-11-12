# Sistema de Control Térmico Automatizado con ESP32

Este proyecto implementa un sistema de control de temperatura en lazo cerrado para una cámara térmica utilizando un ESP32, un sensor de temperatura LM35, potenciómetros para el ajuste dinámico de umbrales, lógica de relevadores para actuadores de calentamiento y enfriamiento, y visualización en tiempo real mediante una pantalla LCD I2C.

---

## Componentes y Hardware Utilizado

* Microcontrolador: ESP32 NodeMCU.
* Sensor de Temperatura: LM35 conectado al pin analógico GPIO 34.
* Entradas Analógicas de Umbrales: 
  * Potenciómetro Límite Inferior (LL): GPIO 35.
  * Potenciómetro Límite Superior (HL): GPIO 32.
* Actuadores y Relevadores:
  * Foco de Calefacción: GPIO 18.
  * Módulo Peltier de Enfriamiento: GPIO 19.
  * Ventilador de Circulación: GPIO 23.
* Pantalla LCD: LCD 16x2 con interfaz I2C en los pines SDA GPIO 21, SCL GPIO 22 y dirección 0x27.

---

## Características Principales

* Control Dinámico por Potenciómetros: Permite ajustar en tiempo real los límites de temperatura inferior y superior en un rango de 30 grados Celsius a 60 grados Celsius mediante lectura analógica.
* Validación de Seguridad de Umbrales: Cuenta con una verificación lógica que evita que el límite inferior sea mayor o igual al límite superior.
* Lógica de Control de Actuadores: 
  * Si la temperatura es menor o igual al límite inferior, se activa el foco y se desactiva la celda Peltier.
  * Si la temperatura es mayor o igual al límite superior, se apaga el foco y se activa la celda Peltier.
  * El ventilador de circulación se mantiene encendido de forma permanente.
* Actualización Asíncrona: Utiliza la función millis con un intervalo de 500 milisegundos para la lectura del sensor y actualización de la pantalla sin bloquear el ciclo principal.

---

## Estructura de Archivos del Proyecto

```text
Practicas-Sistemas-embebidos/
└── unidad-1/
    └── control_termico_esp32/
        ├── platformio.ini
        ├── wokwi.toml
        └── src/
            └── main.cpp

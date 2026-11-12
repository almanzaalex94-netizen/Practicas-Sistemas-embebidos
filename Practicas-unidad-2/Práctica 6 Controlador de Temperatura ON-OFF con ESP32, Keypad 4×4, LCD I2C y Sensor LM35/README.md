# Sistema de Control Térmico con Teclado Matricial y ESP32

Este proyecto implementa un sistema avanzado de control de temperatura en lazo cerrado para una cámara térmica utilizando un ESP32, un sensor de temperatura LM35 con filtro de promedio móvil, un teclado matricial de 4x4 para el ajuste interactivo de umbrales, lógica de relevadores para actuadores de calefacción y enfriamiento, y visualización en tiempo real mediante una pantalla LCD I2C.

---

## Componentes y Hardware Utilizado

* Microcontrolador: ESP32 NodeMCU.
* Sensor de Temperatura: LM35 conectado al pin analógico GPIO 32.
* Interfaz de Entrada: Teclado matricial 4x4 (Filas en GPIO 4, 12, 13, 14; Columnas en GPIO 25, 26, 27, 33).
* Actuadores y Relevadores:
  * Foco de Calefacción: GPIO 18.
  * Módulo Peltier de Enfriamiento: GPIO 19.
  * Ventilador de Circulación: GPIO 23.
* Pantalla LCD: LCD 16x2 con interfaz I2C en los pines SDA GPIO 21, SCL GPIO 22 y dirección 0x27.

---

## Características Principales

* Ajuste Interactivo por Teclado: Permite modificar dinámicamente los límites de temperatura inferior (tecla B) y superior (tecla A) de forma digital, confirmando con '#' o cancelando con '*'.
* Filtrado de Señal: Implementa un algoritmo de promedio móvil con 10 lecturas y configuración de resolución ADC de 12 bits para estabilizar la lectura analógica del sensor LM35.
* Lógica de Control de Actuadores: 
  * Si la temperatura desciende al límite inferior o menos, se activa el foco y se desactiva la celda Peltier.
  * Si la temperatura asciende al límite superior o más, se apaga el foco y se activa la celda Peltier.
  * El ventilador de circulación se mantiene encendido de forma permanente.
* Actualización Asíncrona: Utiliza la función millis con un intervalo de 500 milisegundos para la lectura térmica y actualización de la interfaz de usuario sin bloqueos.

---

## Estructura de Archivos del Proyecto

```text
Practicas-Sistemas-embebidos/
└── unidad-1/
    ├── docs/
    ├── img/
    ├── src/
    │   └── main.cpp
    ├── README.md
    ├── platformio.ini
    ├── wokwi.toml
    └── diagram.json

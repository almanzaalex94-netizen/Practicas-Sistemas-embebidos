# Sistema Animatrónico con ESP32 y Reproductor MP3 (DFPlayer Mini)

Proyecto de sistema embebido desarrollado en **C++** utilizando el framework de **Arduino** en **PlatformIO**. El sistema controla una mandíbula animatrónica mediante un servomotor y un reproductor de audio DFPlayer Mini, activándose automáticamente al detectar presencia humana a través de un sensor PIR.

## Características Principales
- **Control de Servomotor:** Movimiento de apertura y cierre de la mandíbula sincronizado durante la animación.
- **Audio Ambiental Aleatorio:** Reproducción periódica de pistas de fondo (Idle) en intervalos de tiempo aleatorios cuando no hay presencia.
- **Detección de Movimiento (PIR):** Activación inmediata de pista de audio activa, giro del servomotor e iluminación LED al detectar presencia.
- **Gestión de Silencios:** Periodo de silencio programado al finalizar la animación antes de retomar el ciclo de fondo.

---

## Componentes del Hardware

| Componente | Pin / Conexión ESP32 | Descripción |
| :--- | :--- | :--- |
| **Sensor PIR** | GPIO 27 | Detector de presencia infrarroja |
| **Servomotor** | GPIO 18 | Control de apertura de la mandíbula |
| **LED Indicador** | GPIO 4 | LED indicador de estado activo |
| **DFPlayer Mini (RX)** | GPIO 25 | Comunicación Serial 2 (TX del DFPlayer) |
| **DFPlayer Mini (TX)** | GPIO 26 | Comunicación Serial 2 (RX del DFPlayer) |

---

## Estructura del Proyecto

```text
Practicas-Sistemas-embebidos/
├── docs/                     # Documentación y reportes de práctica
├── img/                      # Capturas de pantalla y diagramas
├── src/
│   └── main.cpp              # Código fuente principal del ESP32
├── diagram.json              # Simulación de circuitos para Wokwi
├── platformio.ini            # Configuración de dependencias de PlatformIO
└── wokwi.toml                # Configuración del entorno de simulación

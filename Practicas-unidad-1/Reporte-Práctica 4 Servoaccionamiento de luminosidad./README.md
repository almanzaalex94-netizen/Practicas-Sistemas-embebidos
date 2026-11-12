# Control de Dimmer por Servomotor con ESP32

Este proyecto implementa un sistema de control de potencia tipo dimmer utilizando un **ESP32**, un servomotor para el ajuste mecánico, una pantalla **LCD I2C** para la interfaz visual y dos botones físicos con lógica de antirrebote para incrementar o disminuir la potencia en incrementos del 10%.

---

## 🛠️ Componentes y Hardware Utilizado

* **Microcontrolador:** ESP32 NodeMCU.
* **Actuador:** Servomotor (conectado al pin GPIO 13).
* **Pantalla LCD:** LCD 16x2 con interfaz I2C (pines SDA: GPIO 27, SCL: GPIO 26).
* **Entradas:** 2 Botones pulsadores configurados con resistencia interna pull-up (`INPUT_PULLUP`):
  * Botón Subir: GPIO 33
  * Botón Bajar: GPIO 32

---

## ⚙️ Características Principales

* **Mapeo Lineal Seguro:** Convierte automáticamente un rango porcentual de potencia ($0\%$ a $100\%$) a ángulos mecánicos seguros definidos por límites de seguridad (`ANGULO_MINIMO = 5` hasta `ANGULO_MAXIMO = 175`).
* **Antirrebote por Software:** Implementa un control de tiempo (`millis`) de $250\text{ ms}$ para evitar lecturas falsas o múltiples activaciones por rebote en los pulsadores.
* **Interfaz en Tiempo Real:** Actualiza de forma simultánea la posición del servomotor y los valores mostrados en la pantalla LCD (Porcentaje y Grados).
* **Monitor Serial:** Envía trazas de depuración a una tasa de $115200\text{ bauds}$.

---

## 📦 Librerías Necesarias

Para compilar este código en el IDE de Arduino, asegúrate de tener instaladas las siguientes librerías:

1. **Wire** (Incluida por defecto en el framework de Arduino para ESP32).
2. **LiquidCrystal_I2C** (de Frank de Brabander o Marco Schwartz).
3. **ESP32Servo** (de Kevin Harrington / John K. Bennett).

---

## 🔌 Diagrama de Conexiones (Pinout)

| Componente | Pin del Componente | Pin del ESP32 |
| :--- | :--- | :--- |
| **Servomotor** | Señal (PWM) | GPIO 13 |
| **Pantalla LCD I2C** | SDA | GPIO 27 |
| **Pantalla LCD I2C** | SCL | GPIO 26 |
| **Botón Subir** | Pin 1 | GPIO 33 (con resistencia a GND al presionar) |
| **Botón Bajar** | Pin 1 | GPIO 32 (con resistencia a GND al presionar) |

---

## 💻 Código Fuente

El código fuente principal se encuentra en el archivo del proyecto. Aquí un fragmento de la lógica de control y mapeo:

```cpp
int anguloDestino = map(porcentajeActual, 0, 100, ANGULO_MINIMO, ANGULO_MAXIMO);
miServomotor.write(anguloDestino);

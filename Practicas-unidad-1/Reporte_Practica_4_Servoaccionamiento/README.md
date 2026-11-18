# 💡 Práctica 4: Servoaccionamiento de Luminosidad

![ESP32](https://img.shields.io/badge/Microcontrolador-ESP32-blue)
![Framework](https://img.shields.io/badge/Framework-Arduino%20IDE-00979D)
![Protocolo](https://img.shields.io/badge/Comunicaci%C3%B3n-I2C-orange)
![Asignatura](https://img.shields.io/badge/Asignatura-Sistemas%20Embebidos-green)

Sistema embebido desarrollado con un microcontrolador **ESP32** para regular 
la intensidad luminosa de un foco incandescente de 100 W mediante el acoplamiento 
mecánico entre un **servomotor** y la perilla de un **dimmer AC**[cite: 3, 6].

---

## 📋 Descripción del Proyecto

El sistema permite ajustar la potencia entregada a una carga de corriente alterna 
(foco de 100 W a 127 V) en intervalos de **10%** mediante dos pulsadores físicos 
(subir y bajar)[cite: 3]. El ESP32 procesa las entradas digitales, mapea el porcentaje 
seleccionado a un rango angular seguro ($5^\circ$ a $175^\circ$) y posiciona el servomotor 
para girar físicamente la perilla del dimmer[cite: 5, 6]. Tanto el porcentaje como el 
ángulo actual se visualizan en tiempo real en una pantalla **LCD 16x2 con interfaz I2C**[cite: 3, 5].

---

## 🎯 Objetivo

Implementar un sistema de regulación de luminosidad mediante un dimmer accionado 
mecánicamente por un servomotor, utilizando una tarjeta ESP32, dos pulsadores y una 
pantalla LCD I2C[cite: 6]. El sistema permite incrementar o disminuir el nivel de regulación 
en pasos de 10%, controlar la posición angular del actuador y visualizar las variables 
de estado en pantalla[cite: 6].

---

## 🛠️ Hardware y Materiales

* **Microcontrolador:** 1x Tarjeta de desarrollo ESP32[cite: 7]
* **Actuador:** 1x Servomotor (ej. MG995 / MG996R)[cite: 7, 18]
* **Visualización:** 1x Pantalla LCD 16x2 con módulo adaptador I2C (Dirección `0x27`)[cite: 5, 7]
* **Control de entrada:** 2x Pulsadores (Push buttons)[cite: 7]
* **Etapa de potencia:**
  * 1x Dimmer regulador de luminosidad (2000 W / 127 V AC)[cite: 7]
  * 1x Foco incandescente de 100 W compatible con dimmer[cite: 7]
  * 1x Portalámparas (socket) y clavija de alimentación[cite: 7]
* **Alimentación y montaje:**
  * 1x Fuente de alimentación externa de **6 V / 0.75 A** para el servomotor[cite: 7]
  * Protoboard y cables Dupont[cite: 7]

---

## 🔌 Pinout y Conexiones

| Componente | Pin ESP32 | Función / Observaciones |
| :--- | :---: | :--- |
| **Servomotor (Señal)** | `GPIO 13` | Señal PWM de control angular (500–2400 µs)[cite: 7, 10] |
| **Pulsador SUBIR** | `GPIO 33` | Incrementa +10% (configurado como `INPUT_PULLUP` hacia GND)[cite: 7, 8] |
| **Pulsador BAJAR** | `GPIO 32` | Decrementa -10% (configurado como `INPUT_PULLUP` hacia GND)[cite: 7, 8] |
| **LCD I2C (SDA)** | `GPIO 27` | Línea de datos I2C[cite: 7, 9] |
| **LCD I2C (SCL)** | `GPIO 26` | Línea de reloj I2C[cite: 7, 9] |

> ⚠️ **Nota de Seguridad y Alimentación:**
> 1. El servomotor debe alimentarse con una fuente externa de **6 V** compartiendo 
> referencia común (**GND**) con el ESP32[cite: 8].
> 2. Mantener la etapa de potencia de **127 V AC** (dimmer y foco) completamente 
> aislada físicamente de la etapa de control de baja tensión[cite: 9].

---

## 💻 Dependencias de Software

Para compilar y cargar el código desde **Arduino IDE**, instala las siguientes bibliotecas:
* `Wire.h` (Integrada en el core de ESP32)[cite: 9]
* `LiquidCrystal_I2C` (Control de pantalla LCD por I2C)[cite: 9]
* `ESP32Servo` (Control PWM de servomotores en arquitectura ESP32)[cite: 9]

---

## 📊 Tabla de Mapeo (Porcentaje vs. Ángulo)

La relación lineal utilizada en el firmware sigue la ecuación[cite: 6]:

$$\text{Ángulo} = 5 + \left(\text{Porcentaje} \times \frac{170}{100}\right)$$

| Porcentaje (%) | Ángulo del Servo (°) | Porcentaje (%) | Ángulo del Servo (°) |
| :---: | :---: | :---: | :---: |
| **0%** | $5^\circ$[cite: 15] | **60%** | $107^\circ$[cite: 16] |
| **10%** | $22^\circ$[cite: 15] | **70%** | $124^\circ$[cite: 16] |
| **20%** | $39^\circ$[cite: 15] | **80%** | $141^\circ$[cite: 16] |
| **30%** | $56^\circ$[cite: 15] | **90%** | $158^\circ$[cite: 16] |
| **40%** | $73^\circ$[cite: 15] | **100%** | $175^\circ$[cite: 16] |
| **50%** | $90^\circ$[cite: 16] | — | — |

---

## ⚙️ Lógica de Funcionamiento

1. **Inicialización:** Al encender el sistema, se configura el bus I2C en los pines 
`27` y `26`, se activan las resistencias internas `INPUT_PULLUP` en los pulsadores y el 
servomotor se posiciona en su límite seguro inicial de **$5^\circ$ (0%)**[cite: 10, 14].
2. **Lectura con Antirrebote:** Se implementa un filtro antirrebote por software mediante 
`millis()` con un umbral de **250 ms** para evitar lecturas múltiples por una sola pulsación[cite: 4, 10].
3. **Actualización:** Cada cambio válido recalcula el ángulo mediante `map()`, mueve el 
actuador, actualiza los valores en el LCD (`Potencia` y `Angulo`) y envía la traza de 
depuración por puerto Serial a `115200` baudios[cite: 10, 11].

---

## 👥 Autores y Créditos

* **Alejandro Almanza Perez**[cite: 1]
* **Vanessa Guadalupe Soria Zavala**[cite: 1]
* **Adán Rodriguez Ortiz**[cite: 1]
* **America Aranzazu Rodriguez Perez**[cite: 1]

**Institución:** Universidad Politécnica del Bicentenario (UPB) — Silao, Guanajuato[cite: 1]  
**Asignatura:** Sistemas Embebidos (Grupo IME 702)[cite: 2]  
**Docente:** Hugo Antonio Méndez Guzmán[cite: 1]

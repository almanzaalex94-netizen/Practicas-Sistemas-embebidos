# 📚 Prácticas de Unidad 2 — Sistemas Embebidos (ESP32)

![Microcontrolador](https://img.shields.io/badge/Microcontrolador-ESP32-blue)
![Framework](https://img.shields.io/badge/Framework-Arduino%20IDE-00979D)
![Asignatura](https://img.shields.io/badge/Asignatura-Sistemas%20Embebidos-green)
![Grupo](https://img.shields.io/badge/Grupo-IME%20702-orange)

Repositorio correspondiente a las prácticas de la **Unidad 2** de la asignatura de 
**Sistemas Embebidos**, desarrolladas con el microcontrolador **ESP32** e integrando 
adquisición analógica (ADC), control ON-OFF con histéresis, control proporcional (P), 
interfaces de usuario (LCD I2C y Keypad 4x4), servomotores, regulación de potencia y 
reproducción de audio[cite: 2, 23, 25, 40, 56, 75].

---

## 📁 Estructura del Directorio

* **`Práctica 5 Control ON-OFF con ...`:** Monitor de voltaje y temperatura con sensor LM35, 
  potenciómetros para ajuste dinámico de umbrales (LL/HL) y control por histéresis sobre 
  foco calefactor, celda Peltier y ventilador[cite: 22, 25, 92].
* **`Práctica 6 Controlador de Temp...`:** Controlador térmico ON-OFF con histéresis 
  utilizando teclado matricial 4x4, filtro digital de media móvil por software para el 
  sensor LM35, pantalla LCD I2C y etapas de potencia por relés[cite: 38, 40, 92].
* **`Práctica 7 Animatronico`:** Animatrónico interactivo inspirado en Foxy con sensor PIR, 
  servomotor SG90 para movimiento de mandíbula, LED rojo y módulo DFPlayer Mini vía UART[cite: 56, 58, 59, 92].
* **`Práctica 8`:** Control proporcional de temperatura (P) en cámara térmica con sensor LM35, 
  teclado matricial 4x4, LCD I2C y servomotor acoplado a dimmer para regular un foco[cite: 75, 81, 92].

---

## 🛠️ Resumen de Prácticas y Hardware Clave

| Práctica | Enfoque Principal | Sensores / Entradas | Actuadores y Salidas |
| :--- | :--- | :--- | :--- |
| **Práctica 5** | Control ON-OFF con histéresis[cite: 25] | LM35 (`GPIO 34`) y 2x Potenciómetros (`GPIO 35`, `32`)[cite: 26] | 3x Relés (`GPIO 18, 19, 23`) + LCD I2C (`21, 22`)[cite: 26] |
| **Práctica 6** | Teclado 4x4 y filtro media móvil[cite: 38, 40] | LM35 (`GPIO 32`) y Keypad 4x4 (`Filas 4,12,13,14` / `Cols 25,26,27,33`)[cite: 41, 42] | 3x Relés (`GPIO 18, 19, 23`) + LCD I2C (`21, 22`)[cite: 41, 43] |
| **Práctica 7** | Animatrónico y temporizadores (`millis`)[cite: 58, 65] | Sensor PIR HC-SR501 (`GPIO 27`)[cite: 59, 60] | Servo SG90 (`GPIO 18`), LED (`GPIO 4`), DFPlayer (`25, 26`)[cite: 59, 60] |
| **Práctica 8** | Control proporcional ($\text{Salida} = K_p \cdot e$)[cite: 77] | LM35 (`GPIO 35`) y Keypad 4x4 (`Filas 19,18,5,4` / `Cols 32,33,25,14`)[cite: 79, 80] | Servo + Dimmer (`GPIO 13`) + LCD I2C (`27, 26`)[cite: 78, 79, 80] |

---

## ⚠️ Notas Generales de Seguridad y Montaje

* **Aislamiento eléctrico:** Mantén físicamente separadas las etapas de potencia (120V/127V AC 
  o cargas de mayor corriente) de las líneas de control de baja tensión del ESP32[cite: 9, 27, 83].
* **Tierra común (GND):** Cuando utilices fuentes de alimentación externas para servomotores, 
  celdas Peltier o módulos de audio, unifica siempre la referencia **GND** con el ESP32[cite: 8, 27, 61, 82].
* **Estabilización y tiempos:** Respeta los tiempos de estabilización de sensores (como el PIR) 
  y utiliza temporización no bloqueante con `millis()` para mantener la respuesta del sistema[cite: 31, 47, 58, 62].

---

## 👥 Autores y Créditos

* **Alejandro Almanza Perez**[cite: 1, 20, 36, 53, 72]
* **Vanessa Guadalupe Soria Zavala**[cite: 1, 20, 36, 53, 72]
* **Adán Rodriguez Ortiz**[cite: 1, 20, 36, 53, 72]
* **America Aranzazu Rodriguez Perez**[cite: 1, 20, 36, 53]

**Institución:** Universidad Politécnica del Bicentenario (UPB) — Silao, Guanajuato[cite: 1, 20, 36, 53, 71, 72]  
**Asignatura:** Sistemas Embebidos (Grupo IME 702)[cite: 2, 21, 37, 54, 72, 73]  
**Docente:** Hugo Antonio Méndez Guzmán[cite: 1, 20, 36, 53, 72]

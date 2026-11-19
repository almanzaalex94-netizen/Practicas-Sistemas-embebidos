# 📘 Sistemas Embebidos — Repositorio General de Prácticas (ESP32)

![Microcontrolador](https://img.shields.io/badge/Microcontrolador-ESP32-blue)
![Framework](https://img.shields.io/badge/Framework-Arduino%20IDE-00979D)
![Simulación](https://img.shields.io/badge/Simulación-Wokwi%20%26%20LabVIEW-purple)
![Asignatura](https://img.shields.io/badge/Asignatura-Sistemas%20Embebidos-green)
![Grupo](https://img.shields.io/badge/Grupo-IME%20702-orange)

Repositorio general de la asignatura de **Sistemas Embebidos** en la 
**Universidad Politécnica del Bicentenario (UPB)**[cite: 1, 2, 20, 21, 94, 95]. 
Reúne las prácticas de la **Unidad 1** (Prácticas 1 a 4) y la **Unidad 2** 
(Prácticas 5 a 8), desarrolladas con el microcontrolador **ESP32** e integrando 
entradas/salidas digitales, conmutación de potencia, adquisición analógica (ADC), 
control ON-OFF con histéresis, control proporcional (P), buses **I2C** y **1-Wire**, 
interfaces HMI, servomotores, audio y pruebas en simulación y protoboard[cite: 2, 23, 25, 40, 56, 75, 92, 97, 123, 150].

---

## 📁 Estructura General del Repositorio

* **`Unidad 1` (Prácticas 1 a 4):** Fundamentos de E/S digitales (`INPUT_PULLUP`), 
  conmutación con transistor NPN y diodo *flyback*, control de cargas AC mediante 
  relevador, monitoreo y control ON-OFF de nivel con sensor ultrasónico **HC-SR04**, 
  y control térmico ON-OFF con histéresis usando **DS18B20** y **LCD 16x2 I2C**[cite: 97, 102, 108, 114, 123, 150].
* **`Practicas-unidad-2` (Prácticas 5 a 8):** Evolución hacia control ON-OFF con 
  histéresis usando **LM35** y potenciómetros (**Práctica 5**), teclado matricial 4x4 
  y filtro de media móvil (**Práctica 6**), sistema interactivo con sensor PIR, 
  servomotor SG90 y reproductor DFPlayer (**Práctica 7**), y control proporcional (P) 
  de temperatura con servomotor acoplado a dimmer (**Práctica 8**)[cite: 22, 25, 38, 40, 56, 58, 75, 81, 92].

---

## 🛠️ Mapa General de Prácticas por Unidad

| Unidad / Práctica | Tema / Enfoque | Sensores / Entradas | Actuadores / Salidas Clave |
| :--- | :--- | :--- | :--- |
| **U1 — Práctica 1** | E/S digital, transistor y relé AC[cite: 102, 108, 114] | Pulsadores (`GPIO 21`, `19`)[cite: 101, 107, 113] | LED (`GPIO 2`), Motor DC + 2N2222, Relé + Foco AC[cite: 101, 107, 113] |
| **U1 — Práctica 2** | Control ON-OFF de nivel con mediana[cite: 123, 130, 142] | HC-SR04 (`13, 14`) + 3 botones (`18, 32, 19`)[cite: 128, 129] | 2 Relés (`GPIO 4, 5`) + LCD I2C (`26, 27`)[cite: 129] |
| **U1 — Práctica 3** | Control ON-OFF térmico e histéresis[cite: 150, 154] | DS18B20 (`4`) + 3 botones (`12, 13, 14`)[cite: 155, 156] | 3 Relés (`GPIO 18, 19, 23`) + LCD I2C (`21, 22`)[cite: 155, 156] |
| **U1 — Práctica 4** | Integración de señales y control (U1) | Entradas digitales/analógicas | Indicadores y actuadores de control |
| **U2 — Práctica 5** | Control ON-OFF con histéresis y ADC[cite: 2, 22, 25] | LM35 (`34`) + 2 potenciómetros (`35, 32`)[cite: 26] | 3 Relés (`GPIO 18, 19, 23`) + LCD I2C (`21, 22`)[cite: 26] |
| **U2 — Práctica 6** | Teclado 4x4 y filtro media móvil[cite: 38, 40] | LM35 (`32`) + Keypad 4x4 (`4,12,13,14` / `25,26,27,33`)[cite: 41, 42] | 3 Relés (`GPIO 18, 19, 23`) + LCD I2C (`21, 22`)[cite: 41, 43] |
| **U2 — Práctica 7** | Animatrónico y temporización `millis()`[cite: 58, 65] | Sensor PIR HC-SR501 (`GPIO 27`)[cite: 59, 60] | Servo SG90 (`18`), LED (`4`), DFPlayer (`25, 26`)[cite: 59, 60] |
| **U2 — Práctica 8** | Control proporcional ($\text{Salida} = K_p \cdot e$)[cite: 77] | LM35 (`35`) + Keypad 4x4 (`19,18,5,4` / `32,33,25,14`)[cite: 79, 80] | Servo + Dimmer (`13`) + LCD I2C (`27, 26`)[cite: 78, 79, 80] |

---

## ⚠️ Seguridad Eléctrica y Buenas Prácticas

* **Separación de potencia y control:** Aísla físicamente las etapas de corriente 
  alterna (110–127 V AC) y cargas de mayor corriente respecto a los pines del ESP32, 
  manipulando conexiones AC siempre sin energía[cite: 9, 27, 83, 114, 119].
* **Tierra común (`GND`):** Unifica la referencia `GND` entre el ESP32 y las 
  fuentes externas de motores, bombas, celdas Peltier, servomotores o módulos de 
  audio[cite: 8, 27, 61, 82, 108, 131, 157].
* **Disipación y verificación previa:** Emplea disipador en celdas Peltier, diodo 
  *flyback* en cargas inductivas DC y revisa *pinout* y lógica de relés antes de 
  energizar[cite: 108, 144, 154, 155].

---

## 👥 Autores y Créditos

* **Alejandro Almanza Perez**[cite: 1, 20, 36, 53, 72, 94, 121, 148]
* **Vanessa Guadalupe Soria Zavala**[cite: 1, 20, 36, 53, 72, 94, 121, 148]
* **Adán Rodriguez Ortiz**[cite: 1, 20, 36, 53, 72, 94, 121, 148]

**Institución:** Universidad Politécnica del Bicentenario (UPB) — Silao, Guanajuato[cite: 1, 20, 36, 53, 71, 72, 94, 121, 148]  
**Asignatura:** Sistemas Embebidos (Grupo IME 702)[cite: 2, 21, 37, 54, 72, 73, 95, 122, 149]  
**Docente:** Hugo Antonio Méndez Guzmán[cite: 1, 20, 36, 53, 72, 94, 121, 148]

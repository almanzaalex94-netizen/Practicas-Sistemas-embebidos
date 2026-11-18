# 🦊 Práctica 7: Animatrónico Interactivo tipo Foxy con ESP32

![ESP32](https://img.shields.io/badge/Microcontrolador-ESP32-blue)
![Framework](https://img.shields.io/badge/Framework-Arduino%20IDE-00979D)
![Sensor](https://img.shields.io/badge/Sensor-PIR-orange)
![Audio](https://img.shields.io/badge/Modulo-DFPlayer%20Mini-green)

Sistema embebido interactivo inspirado en el personaje **Foxy** (Five Nights at Freddy's), 
desarrollado con una tarjeta **ESP32**[cite: 56]. El sistema detecta presencia humana mediante 
un sensor infrarrojo pasivo (**PIR**) y activa una secuencia animada compuesta por efectos 
luminosos, reproducción de audio MP3 vía **UART** y movimiento mecánico de la mandíbula con un **servomotor**[cite: 56].

---

## 📋 Descripción del Proyecto

El prototipo opera en dos estados principales: **Reposo (Idle)** y **Activo (Animación)**[cite: 65, 66]. 
En reposo, reproduce de forma aleatoria pistas de audio ambiental a través de un módulo 
**DFPlayer Mini** y una tarjeta MicroSD[cite: 58, 62]. Cuando el sensor PIR detecta movimiento en 
el entorno, el ESP32 conmuta a la secuencia activa: enciende un **LED rojo** (representando el 
ojo visible del personaje), reproduce una pista de audio de alerta y acciona un **servomotor SG90** 
que abre y cierra rítmicamente la mandíbula del peluche[cite: 56, 62, 65]. Al finalizar la animación, 
el sistema guarda un periodo de silencio programado antes de reanudar la escucha[cite: 63, 65].

---

## 🎯 Objetivo

Diseñar e implementar un animatrónico interactivo utilizando un ESP32, capaz de detectar presencia 
humana y responder mediante la conmutación sincronizada de elementos mecánicos, lumínicos y de 
reproducción de audio digital[cite: 59].

---

## 🛠️ Hardware y Materiales

* **Unidad de Control:** 1x Tarjeta ESP32 DevKit V4[cite: 59]
* **Detección de Movimiento:** 1x Sensor PIR HC-SR501[cite: 59]
* **Actuador Mecánico:** 1x Servomotor SG90 (movimiento de mandíbula)[cite: 59]
* **Señalización Visual:** 1x LED rojo + 1x Resistencia de 220 $\Omega$[cite: 59]
* **Audio:** 
  * 1x Módulo reproductor MP3 DFPlayer Mini[cite: 59]
  * 1x Tarjeta MicroSD (con archivos `0001.mp3` y `0002.mp3`)[cite: 59, 63]
  * 1x Altavoz compatible[cite: 59]
* **Estructura y Montaje:** Estructura de peluche (Foxy), cables Dupont y fuente de alimentación externa[cite: 59, 60]

---

## 🔌 Pinout y Conexiones

| Componente | Señal / Terminal | Pin ESP32 | Función Principal |
| :--- | :---: | :---: | :--- |
| **Sensor PIR** | `OUT` | `GPIO 27` | Entrada digital de detección de movimiento[cite: 60] |
| **Servomotor SG90** | `Señal PWM` | `GPIO 18` | Control angular de apertura/cierre de mandíbula[cite: 60] |
| **LED Rojo** | `Ánodo (via 220Ω)` | `GPIO 4` | Indicador visual del ojo visible activo[cite: 60] |
| **DFPlayer Mini** | `TX Módulo` | `GPIO 25` | Línea de recepción serial (RX del ESP32)[cite: 60] |
| **DFPlayer Mini** | `RX Módulo` | `GPIO 26` | Línea de transmisión serial (TX del ESP32)[cite: 60] |
| **Altavoz** | `SPK1 / SPK2` | Módulo DFPlayer | Salida directa de audio amplificado[cite: 60] |

> ⚠️ **Nota de Alimentación:** Asegúrate de conectar una fuente de alimentación externa adecuada para 
> el servomotor y el módulo de audio, unificando siempre la referencia de tierra (**GND**) con el ESP32[cite: 61].

---

## ⚙️ Parámetros y Configuración del Software

| Parámetro | Valor Configurado | Descripción |
| :--- | :---: | :--- |
| **Ángulo Mandíbula Cerrada** | $20^\circ$ | Posición de reposo de la boca (`ANGULO_CERRADA`)[cite: 61, 66] |
| **Ángulo Mandíbula Abierta** | $70^\circ$ | Posición de apertura durante la animación (`ANGULO_ABIERTA`)[cite: 61, 66] |
| **Periodo de Movimiento** | $250\text{ ms}$ | Intervalo de cambio de ángulo del servo (`PERIODO_MOV`)[cite: 61, 66] |
| **Duración de Animación** | $6000\text{ ms}$ | Tiempo total de ejecución de la respuesta activa[cite: 61, 66] |
| **Pausa Post-Animación** | $3000\text{ ms}$ | Tiempo mínimo de espera para permitir una nueva activación[cite: 61, 66] |
| **Volumen DFPlayer** | `15` (Escala 0-30) | Nivel de salida de audio configurado por UART[cite: 61, 66] |

---

## 👥 Autores y Créditos

* **Alejandro Almanza Perez**[cite: 53]
* **Vanessa Guadalupe Soria Zavala**[cite: 53]
* **Adán Rodriguez Ortiz**[cite: 53]
* **America Aranzazu Rodriguez Perez**[cite: 53]

**Institución:** Universidad Politécnica del Bicentenario (UPB) — Silao, Guanajuato[cite: 53]  
**Asignatura:** Sistemas Embebidos (Grupo IME 702)[cite: 54]  
**Docente:** Hugo Antonio Méndez Guzmán[cite: 53]

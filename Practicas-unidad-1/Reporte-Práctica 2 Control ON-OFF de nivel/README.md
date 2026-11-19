# 💡 Práctica 1 — Control de Dispositivos Básicos (ESP32)

![Microcontrolador](https://img.shields.io/badge/Microcontrolador-ESP32-blue)
![Framework](https://img.shields.io/badge/Framework-Arduino%20IDE-00979D)
![Simulación](https://img.shields.io/badge/Simulación-Wokwi-purple)
![Grupo](https://img.shields.io/badge/Grupo-IME%20702-orange)

Práctica dividida en tres etapas (**Práctica 1.1 LED**, **Práctica 1.2 Motor** y 
**Práctica 1.3 Socket y Foco**) para comprender el manejo de entradas/salidas 
digitales (`INPUT_PULLUP`), conmutación de cargas de corriente directa mediante 
transistor NPN y aislamiento eléctrico para corriente alterna (110–127 V AC) 
mediante relevador[cite: 95, 102, 108, 113, 114].

---

## 🎯 Objetivos y Enfoque por Subpráctica

* **Práctica 1.1 (LED):** Controlar el encendido y apagado de un LED mediante dos 
  pulsadores en `INPUT_PULLUP` con confirmación en el Monitor Serial[cite: 101, 102, 105].
* **Práctica 1.2 (Motor DC):** Conmutar un motor de corriente directa alimentado con 
  fuente externa de 5 V usando un transistor **2N2222** y diodo *flyback* (**1N4007/1N4001**)[cite: 107, 108].
* **Práctica 1.3 (Socket y Foco AC):** Controlar un foco de 110–127 V AC mediante un 
  módulo relevador de 5 V, separando el circuito de control del circuito de potencia[cite: 113, 114].

---

## 📌 Asignación de Pines y Hardware Clave

| Subpráctica | Entradas (Botones) | Salida de Control | Etapa de Potencia / Carga |
| :--- | :--- | :--- | :--- |
| **1.1 LED** | Botón 1 (`GPIO 21`), Botón 2 (`GPIO 19`)[cite: 101] | `GPIO 2` (vía `1 kΩ`)[cite: 101] | LED rojo/azul a `GND`[cite: 101, 103, 105] |
| **1.2 Motor DC** | Botón 1 (`GPIO 21`), Botón 2 (`GPIO 19`)[cite: 107] | `GPIO 2` (vía `1 kΩ` a base)[cite: 107] | Transistor 2N2222 + diodo *flyback* + fuente 5 V[cite: 107, 108] |
| **1.3 Socket y Foco** | Botón 1 (`GPIO 21`), Botón 2 (`GPIO 19`)[cite: 113] | `GPIO 2` al pin `IN` del relé[cite: 113, 115] | Módulo relé 5 V (`COM`/`NO`) + socket y foco 110–127 V AC[cite: 113, 115] |

---

## ⚠️ Seguridad y Buenas Prácticas de Montaje

* **Tierra común (GND):** En el control del motor DC con fuente externa de 5 V, une 
  siempre el `GND` de la fuente externa con el `GND` del ESP32[cite: 108, 112].
* **Protección inductiva:** Coloca el diodo *flyback* en paralelo con el motor 
  (cátodo a `+5 V`, ánodo al colector) para absorber picos de voltaje inverso[cite: 108, 109].
* **Aislamiento en 110–127 V AC:** Mantén físicamente separadas las conexiones de 
  corriente alterna del área de control de bajo voltaje y manipula el circuito 
  únicamente con la alimentación AC desconectada[cite: 114, 119].

---

## 👥 Autores y Créditos

* **Alejandro Almanza Perez**[cite: 94]
* **Vanessa Guadalupe Soria Zavala**[cite: 94]
* **Adán Rodriguez Ortiz**[cite: 94]
* **America Aranzazu Rodriguez Perez**[cite: 94]

**Institución:** Universidad Politécnica del Bicentenario (UPB) — Silao, Guanajuato[cite: 94]  
**Asignatura:** Sistemas Embebidos (Grupo IME 702)[cite: 95]  
**Docente:** Hugo Antonio Méndez Guzmán[cite: 94]

# 🌡️ Práctica 3 — Control ON-OFF de Temperatura (ESP32)

![Microcontrolador](https://img.shields.io/badge/Microcontrolador-ESP32-blue)
![Sensor](https://img.shields.io/badge/Sensor-DS18B20%20(1--Wire)-success)
![Control](https://img.shields.io/badge/Control-ON--OFF%20Histéresis-red)
![Grupo](https://img.shields.io/badge/Grupo-IME%20702-orange)

Sistema de control térmico ON-OFF con histéresis en una cámara de pruebas 
utilizando el sensor digital **DS18B20** (bus 1-Wire), pantalla **LCD 16x2 I2C**, 
tres pulsadores (`SEL`, `UP`, `DOWN`) y tres relevadores para controlar un **foco 
calefactor**, una **celda Peltier con disipador** y un **ventilador de circulación**[cite: 150, 155, 156].

---

## 📌 Asignación de Pines

| Componente | Pin ESP32 | Tipo / Modo | Función |
| :--- | :--- | :--- | :--- |
| **Sensor DS18B20 (DQ)** | `GPIO 4`[cite: 155] | Digital 1-Wire (pull-up `4.7 kΩ`)[cite: 155, 156] | Lectura de temperatura interna de la caja[cite: 155, 156] |
| **LCD I2C (SDA / SCL)** | `GPIO 21` / `GPIO 22`[cite: 155, 156] | Bus I2C (`0x27`)[cite: 154, 156] | Muestra temperatura, porcentaje (`30–60 °C`) y `LL`/`HL`[cite: 154, 156, 166, 167] |
| **Botón UP** | `GPIO 12`[cite: 156] | `INPUT_PULLUP`[cite: 156] | Incrementa en `+5 °C` el umbral en edición[cite: 156] |
| **Botón DOWN** | `GPIO 13`[cite: 156] | `INPUT_PULLUP`[cite: 156] | Decrementa en `-5 °C` el umbral en edición[cite: 156] |
| **Botón SEL** | `GPIO 14`[cite: 156] | `INPUT_PULLUP`[cite: 156] | Alterna entre modo normal, edición de `LL` y edición de `HL`[cite: 156, 166] |
| **Relé Foco (Calentador)** | `GPIO 18`[cite: 156] | Salida digital (`RELE_ON = HIGH`)[cite: 156, 161, 166] | Enciende el foco cuando la temperatura baja a `LL` o menos[cite: 154, 156, 163] |
| **Relé Celda Peltier** | `GPIO 19`[cite: 156] | Salida digital (`RELE_ON = HIGH`)[cite: 156, 161, 166] | Activa enfriamiento con disipador al llegar a `HL` o más[cite: 154, 156, 163] |
| **Relé Ventilador** | `GPIO 23`[cite: 156] | Salida digital (`RELE_ON = HIGH`)[cite: 156, 161, 166] | Mantiene la circulación de aire dentro de la caja[cite: 156, 162, 166] |

---

## ⚙️ Lógica de Control y Funcionamiento

* **Histéresis térmica:** Si `T <= LL`, enciende el foco y apaga la Peltier; si 
  `T >= HL`, apaga el foco y enciende la Peltier; entre `LL` y `HL` conserva el 
  último estado activo para evitar conmutaciones constantes[cite: 153, 154, 157].
* **Antirrebote y no bloqueo:** Implementa antirrebote por software (`200 ms`) y 
  actualización periódica cada `500 ms` mediante `millis()`[cite: 161, 166, 168].
* **Dinámica térmica:** Debido a la inercia térmica y al aislamiento de la caja, los 
  cambios de temperatura ocurren de forma gradual (aprox. 15–20 minutos en pruebas)[cite: 150, 154, 167, 168].

---

## ⚠️ Notas de Seguridad y Montaje

* **Disipación en celda Peltier:** Utiliza siempre el disipador acoplado a la celda 
  Peltier para evacuar el calor generado y evitar daños térmicos[cite: 154, 155].
* **Aislamiento y tierra común:** Separa las etapas de potencia (12V DC y carga del 
  foco) del circuito de control del ESP32 y comparte `GND` donde corresponda[cite: 157].

---

## 👥 Autores y Créditos

* **Alejandro Almanza Perez**[cite: 148]
* **Vanessa Guadalupe Soria Zavala**[cite: 148]
* **Adán Rodriguez Ortiz**[cite: 148]

**Institución:** Universidad Politécnica del Bicentenario (UPB) — Silao, Guanajuato[cite: 148]  
**Asignatura:** Sistemas Embebidos (Grupo IME 702)[cite: 149]  
**Docente:** Hugo Antonio Méndez Guzmán[cite: 148]

# 📚 Prácticas de Unidad 1 — Sistemas Embebidos (ESP32)

![Microcontrolador](https://img.shields.io/badge/Microcontrolador-ESP32-blue)
![Framework](https://img.shields.io/badge/Framework-Arduino%20IDE-00979D)
![Simulación](https://img.shields.io/badge/Simulación-Wokwi%20%26%20LabVIEW-purple)
![Grupo](https://img.shields.io/badge/Grupo-IME%20702-orange)

Repositorio correspondiente a las prácticas de la **Unidad 1** de la asignatura de 
**Sistemas Embebidos** (Prácticas 1 a 4), desarrolladas con el microcontrolador **ESP32** 
e integrando entradas/salidas digitales, conmutación de potencia (transistor y relés), 
sensores ultrasónicos y térmicos, buses **I2C** y **1-Wire**, control ON-OFF con 
histéresis y pruebas en simulación y hardware físico[cite: 97, 102, 108, 114, 123, 150].

---

## 📁 Estructura del Directorio

* **`Práctica 1 — Control de dispositivos básicos`:** Control digital en tres etapas 
  (**1.1 LED**, **1.2 Motor DC** con transistor 2N2222 y diodo *flyback*, y **1.3 Socket y Foco AC** 
  con relevador de 5 V) mediante pulsadores en `INPUT_PULLUP`[cite: 95, 102, 107, 108, 113].
* **`Práctica 2 — Control ON-OFF de nivel`:** Monitoreo y control de nivel de líquido con 
  sensor ultrasónico **HC-SR04**, pantalla **LCD 16x2 I2C**, botones de ajuste (`SELECT`, `UP`, `DOWN`) 
  para umbrales **LL** y **HL**, y dos relevadores para bombas de llenado y drenado[cite: 123, 128, 129].
* **`Práctica 3 — Control ON-OFF de temperatura`:** Control térmico con histéresis en cámara 
  de pruebas usando sensor **DS18B20** (1-Wire), **LCD 16x2 I2C**, tres pulsadores y tres 
  relevadores para foco calefactor, celda Peltier con disipador y ventilador de circulación[cite: 150, 155, 156].
* **`Práctica 4`:** Práctica complementaria de la Unidad 1 en el entorno de la asignatura 
  (integración de entradas/salidas, instrumentación y control con ESP32).

---

## 🛠️ Resumen de Prácticas y Hardware Clave

| Práctica | Enfoque Principal | Sensores / Entradas | Actuadores y Salidas |
| :--- | :--- | :--- | :--- |
| **Práctica 1** | E/S digital, transistor y relé AC[cite: 102, 108, 114] | Pulsadores (`GPIO 21`, `GPIO 19`)[cite: 101, 107, 113] | LED (`GPIO 2`), Motor DC + 2N2222, Relé + Foco AC[cite: 101, 107, 113] |
| **Práctica 2** | Control ON-OFF de nivel y mediana[cite: 123, 130, 142] | HC-SR04 (`TRIG 13`, `ECHO 14`) + 3 botones (`18, 32, 19`)[cite: 128, 129] | 2 Relés (`GPIO 4, 5`) + LCD I2C (`SDA 26, SCL 27`)[cite: 129] |
| **Práctica 3** | Control ON-OFF térmico con histéresis[cite: 150, 154] | DS18B20 (`GPIO 4`, pull-up `4.7 kΩ`) + 3 botones (`12, 13, 14`)[cite: 155, 156] | 3 Relés (`GPIO 18, 19, 23`) + LCD I2C (`SDA 21, SCL 22`)[cite: 155, 156] |
| **Práctica 4** | Integración de control y señales (Unidad 1) | Entradas digitales/analógicas de prueba | Indicadores y actuadores de control |

---

## ⚠️ Notas Generales de Seguridad y Montaje

* **Aislamiento en 110–127 V AC:** Mantén físicamente separadas las líneas de corriente 
  alterna del circuito de control del ESP32 y manipula el cableado únicamente sin energía[cite: 114, 119].
* **Tierra común (GND):** Unifica la referencia `GND` entre el ESP32 y las fuentes de 
  alimentación externas de motores, bombas o etapas de potencia cuando corresponda[cite: 108, 131, 157].
* **Disipación y revisión previa:** Acompaña la celda Peltier con disipador y verifica 
  el *pinout* de sensores, LCD y relés antes de energizar para evitar daños en la tarjeta[cite: 144, 154, 155].

---

## 👥 Autores y Créditos

* **Alejandro Almanza Perez**[cite: 94, 121, 148]
* **Vanessa Guadalupe Soria Zavala**[cite: 94, 121, 148]
* **Adán Rodriguez Ortiz**[cite: 94, 121, 148]

**Institución:** Universidad Politécnica del Bicentenario (UPB) — Silao, Guanajuato[cite: 94, 121, 148]  
**Asignatura:** Sistemas Embebidos (Grupo IME 702)[cite: 95, 122, 149]  
**Docente:** Hugo Antonio Méndez Guzmán[cite: 94, 121, 148]

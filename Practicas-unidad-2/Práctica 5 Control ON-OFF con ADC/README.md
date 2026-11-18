# 🌡️ Práctica 5: Monitor de Voltaje y Temperatura con ESP32

![ESP32](https://img.shields.io/badge/Microcontrolador-ESP32-blue)
![Framework](https://img.shields.io/badge/Framework-Arduino%20IDE-00979D)
![Sensor](https://img.shields.io/badge/Sensor-LM35-orange)
![Protocolo](https://img.shields.io/badge/Comunicaci%C3%B3n-I2C-green)

Sistema embebido desarrollado con una tarjeta **ESP32** para el monitoreo de temperatura 
mediante un sensor analógico **LM35** y el ajuste dinámico de umbrales por medio de potenciómetros[cite: 25]. 
El sistema implementa un control **ON-OFF con histéresis** para gestionar cargas de calefacción 
y enfriamiento[cite: 25].

---

## 📋 Descripción del Proyecto

El circuito mide la temperatura interna de una cámara ambiental utilizando un sensor LM35 
conectado al canal analógico del ESP32[cite: 22, 25]. Dos potenciómetros permiten configurar en tiempo real 
los umbrales de Límite Inferior (LL) y Límite Superior (HL)[cite: 25]. Según la lectura térmica y 
aplicando una banda de histéresis, el microcontrolador conmuta tres relés que accionan un **foco 
calefactor (120V AC)**, una **celda Peltier con disipador (12V DC)** y un **ventilador de circulación**[cite: 22, 25, 27]. 
Los datos en tiempo real (temperatura, porcentaje de escala y umbrales) se despliegan en una 
**pantalla LCD 16x2 I2C**[cite: 25].

---

## 🎯 Objetivo

Implementar un sistema de monitoreo analógico y control térmico ON-OFF con histéresis utilizando 
un ESP32, un sensor LM35 y potenciómetros de ajuste dinámico[cite: 25]. Gestionar la activación de 
cargas de potencia y visualizar las variables de estado en una pantalla LCD I2C[cite: 25].

---

## 🛠️ Hardware y Materiales

* **Microcontrolador:** 1x Tarjeta de desarrollo ESP32 DevKit V4[cite: 25]
* **Sensor de Temperatura:** 1x Sensor analógico de precisión LM35[cite: 25]
* **Entrada Analógica:** 2x Potenciómetros de 10 k$\Omega$ (ajuste dinámico de LL y HL)[cite: 25]
* **Visualización:** 1x Pantalla LCD 16x2 con adaptador I2C (Dirección `0x27`)[cite: 21, 25]
* **Etapa de Potencia:** 
  * 3x Módulos relé de 1 canal (5V / 120V AC)[cite: 25]
  * 1x Foco incandescente con socket (calefactor)[cite: 25]
  * 1x Celda Peltier con disipador de aluminio y ventilador[cite: 25]
  * 1x Ventilador DC de 12V (circulación interna)[cite: 25]
* **Montaje y Alimentación:** 1x Fuente externa 12V/5V DC, protoboard y cables Dupont[cite: 25, 26]

---

## 🔌 Pinout y Conexiones

| Componente | Pin ESP32 | Tipo / Configuración | Función |
| :--- | :---: | :---: | :--- |
| **Sensor LM35 ($V_{OUT}$)** | `GPIO 34` | Entrada Analógica (`ADC1_CH6`) | Lectura proporcional a la temperatura[cite: 26] |
| **Potenciómetro LL** | `GPIO 35` | Entrada Analógica (`ADC1_CH7`) | Ajuste dinámico del límite inferior (LL)[cite: 26] |
| **Potenciómetro HL** | `GPIO 32` | Entrada Analógica (`ADC1_CH4`) | Ajuste dinámico del límite superior (HL)[cite: 26] |
| **LCD I2C (SDA)** | `GPIO 21` | Bus I2C (Datos) | Comunicación de datos con la pantalla[cite: 26] |
| **LCD I2C (SCL)** | `GPIO 22` | Bus I2C (Reloj) | Señal de reloj para la pantalla[cite: 26] |
| **Relevador Foco** | `GPIO 18` | Salida Digital | Activa/desactiva el foco calefactor[cite: 26] |
| **Relevador Peltier** | `GPIO 19` | Salida Digital | Activa/desactiva la celda Peltier[cite: 26] |
| **Relevador Circulación** | `GPIO 23` | Salida Digital | Controla el ventilador de circulación interna[cite: 26] |

---

## ⚙️ Lógica de Funcionamiento (Histéresis)

La conmutación de los actuadores se rige por las siguientes condiciones respecto a la temperatura medida ($T$)[cite: 24]:

| Condición de Temperatura | Estado del Foco (Calefactor) | Estado de la Celda Peltier (Enfriamiento) |
| :--- | :---: | :---: |
| **$T \le LL$** | **ENCENDIDO (ON)**[cite: 24] | APAGADO (OFF)[cite: 24] |
| **$T \ge HL$** | APAGADO (OFF)[cite: 24] | **ENCENDIDO (ON)**[cite: 24] |
| **$LL < T < HL$** | *Conserva estado anterior*[cite: 24] | *Conserva estado anterior* (Banda muerta)[cite: 24] |

---

## 👥 Autores y Créditos

* **Alejandro Almanza Perez**[cite: 20]
* **Vanessa Guadalupe Soria Zavala**[cite: 20]
* **Adán Rodriguez Ortiz**[cite: 20]
* **America Aranzazu Rodriguez Perez**[cite: 20]

**Institución:** Universidad Politécnica del Bicentenario (UPB) — Silao, Guanajuato[cite: 20]  
**Asignatura:** Sistemas Embebidos (Grupo IME 702)[cite: 21]  
**Docente:** Hugo Antonio Méndez Guzmán[cite: 20]

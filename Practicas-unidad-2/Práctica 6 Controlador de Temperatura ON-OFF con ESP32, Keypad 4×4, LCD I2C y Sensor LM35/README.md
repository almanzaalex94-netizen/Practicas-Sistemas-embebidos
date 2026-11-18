# ⌨️ Práctica 6: Controlador de Temperatura ON-OFF con ESP32, Keypad 4x4, LCD I2C y LM35

![ESP32](https://img.shields.io/badge/Microcontrolador-ESP32-blue)
![Framework](https://img.shields.io/badge/Framework-Arduino%20IDE-00979D)
![Input](https://img.shields.io/badge/Keypad-4x4-orange)
![Sensor](https://img.shields.io/badge/Sensor-LM35-green)

Sistema embebido de control térmico que sustituye los potenciómetros tradicionales por un 
**teclado matricial 4x4** para la configuración numérica directa de umbrales[cite: 40, 41]. 
Integra un **filtro digital de media móvil** por software para estabilizar la lectura analógica 
del sensor **LM35** frente al ruido electromagnético[cite: 38].

---

## 📋 Descripción del Proyecto

Este sistema implementa un lazo de control ON-OFF con histéresis para cámaras ambientales[cite: 40]. 
Debido a la migración del hardware por daños en el sensor digital original, se emplea un **LM35** 
en el pin analógico `GPIO 32`[cite: 38, 42]. El usuario puede ingresar de manera interactiva los nuevos 
valores de los umbrales inferior (LL) y superior (HL) utilizando el teclado matricial 4x4, ayudado 
por una máquina de estados visualizada en una **pantalla LCD I2C**[cite: 40, 46]. Las cargas térmicas 
(foco calefactor, celda Peltier y ventilador) son gestionadas mediante módulos de relé[cite: 41].

---

## 🎯 Objetivo

Implementar un sistema de control de temperatura ON-OFF con histéresis utilizando un ESP32, un 
sensor analógico LM35 con filtro de media móvil, un teclado matricial 4x4 para introducción 
numérica de umbrales y una pantalla LCD I2C para supervisión en tiempo real[cite: 40, 41].

---

## 🛠️ Hardware y Materiales

* **Microcontrolador:** 1x Tarjeta ESP32 DevKit V4[cite: 41]
* **Sensor Analógico:** 1x Sensor de temperatura LM35[cite: 41]
* **Interfaz de Usuario:** 1x Teclado matricial de membrana 4x4[cite: 41]
* **Visualización:** 1x Pantalla LCD 16x2 con adaptador I2C (Dirección `0x27`)[cite: 37, 41]
* **Etapa de Potencia:** 
  * 3x Módulos relé de 1 canal (5V / 120V AC)[cite: 41]
  * 1x Foco incandescente (calentador) con socket[cite: 41]
  * 1x Celda Peltier con disipador y ventilador[cite: 41]
  * 1x Ventilador DC de 12V (circulación continua)[cite: 41]
* **Montaje:** Cámara ambiental (caja de cartón), protoboard y cables Dupont[cite: 42]

---

## 🔌 Pinout y Conexiones

| Componente / Periférico | Pin ESP32 | Tipo / Configuración | Función |
| :--- | :---: | :---: | :--- |
| **Sensor LM35 ($V_{OUT}$)** | `GPIO 32` | Entrada Analógica (`ADC1_CH4`) | Lectura analógica de temperatura con filtro de media móvil[cite: 41, 42] |
| **LCD I2C (SDA / SCL)** | `GPIO 21 / 22`| Bus I2C | Comunicación de datos y reloj para la pantalla[cite: 42] |
| **Keypad (Filas 1 al 4)** | `GPIO 4, 12, 13, 14` | Salida Digital / Barrido | Líneas de escaneo de filas del teclado[cite: 41, 42] |
| **Keypad (Columnas 1 al 4)** | `GPIO 25, 26, 27, 33` | Entrada Digital (`PULL_UP`) | Líneas de lectura de columnas del teclado[cite: 42, 43] |
| **Relevador Foco** | `GPIO 18` | Salida Digital | Activa/desactiva el foco calefactor[cite: 43] |
| **Relevador Peltier** | `GPIO 19` | Salida Digital | Activa/desactiva la celda Peltier de enfriamiento[cite: 43] |
| **Relevador Circulación** | `GPIO 23` | Salida Digital | Mantiene encendido el ventilador de aire interno[cite: 43] |

---

## ⌨️ Comandos del Teclado Matricial

* **Tecla `A`:** Inicia el modo de edición para configurar el Límite Superior (**HL**)[cite: 45, 48].
* **Tecla `B`:** Inicia el modo de edición para configurar el Límite Inferior (**LL**)[cite: 45, 48].
* **Teclas `0` al `9`:** Ingreso numérico de los dígitos deseados[cite: 46, 48].
* **Tecla `#`:** Valida, verifica la coherencia lógica ($LL < HL$) y guarda el nuevo umbral[cite: 46, 48].
* **Tecla `*`:** Cancela la edición actual y regresa al estado operativo `NORMAL`[cite: 46, 48].

---

## 👥 Autores y Créditos

* **Alejandro Almanza Perez**[cite: 36]
* **Vanessa Guadalupe Soria Zavala**[cite: 36]
* **Adán Rodriguez Ortiz**[cite: 36]
* **America Aranzazu Rodriguez Perez**[cite: 36]

**Institución:** Universidad Politécnica del Bicentenario (UPB) — Silao, Guanajuato[cite: 36]  
**Asignatura:** Sistemas Embebidos (Grupo IME 702)[cite: 37]  
**Docente:** Hugo Antonio Méndez Guzmán[cite: 36]

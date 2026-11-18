# 🔥 Práctica 8: Control Proporcional de Temperatura mediante ESP32

![ESP32](https://img.shields.io/badge/Microcontrolador-ESP32-blue)
![Framework](https://img.shields.io/badge/Framework-Arduino%20IDE-00979D)
![Control](https://img.shields.io/badge/Control-Proporcional%20(P)-orange)
![Sensor](https://img.shields.io/badge/Sensor-LM35-green)

Sistema embebido implementado con una tarjeta **ESP32** para regular la temperatura 
interna de una cámara de pruebas mediante un **controlador proporcional (P)**[cite: 75]. 
Utiliza un sensor analógico **LM35**, un **teclado matricial 4x4**, una **pantalla LCD I2C** 
y un **servomotor** acoplado mecánicamente a la perilla de un **dimmer** que regula un foco[cite: 75, 81].

---

## 📋 Descripción del Proyecto

El sistema mide la temperatura dentro de una caja de cartón mediante el sensor LM35 y compara 
el valor obtenido con un *setpoint* (valor de referencia) configurable desde el teclado 
matricial 4x4[cite: 75, 79]. A partir del error calculado ($\text{Error} = \text{Setpoint} - \text{Temperatura real}$) 
y de una ganancia proporcional $K_p$, el ESP32 calcula un porcentaje de salida limitado entre 
0% y 100%[cite: 77, 78]. Ese porcentaje se mapea a un ángulo del servomotor ($5^\circ$ a $175^\circ$) 
para girar la perilla del dimmer y ajustar la potencia del foco, mostrando los parámetros 
principales en la pantalla LCD I2C[cite: 75, 78, 79].

---

## 🎯 Objetivo

Implementar un sistema de control proporcional de temperatura con ESP32, sensor LM35, 
teclado matricial 4x4, pantalla LCD I2C, servomotor y dimmer conectado a un foco[cite: 79]. 
El sistema permite ajustar el *setpoint* y la constante $K_p$, calcular el error térmico, 
posicionar el servomotor para accionar la perilla del dimmer y visualizar el estado del 
proceso en tiempo real[cite: 79, 87].

---

## 🛠️ Hardware y Materiales

* **Microcontrolador:** 1x Tarjeta ESP32[cite: 80]
* **Sensor de Temperatura:** 1x Sensor analógico LM35[cite: 80]
* **Actuador y Potencia:** 
  * 1x Servomotor acoplado a la perilla del dimmer[cite: 80, 81]
  * 1x Dimmer regulador de luminosidad compatible con el foco[cite: 80]
  * 1x Foco compatible con el dimmer y 1x portalámparas (socket)[cite: 80]
  * 1x Fuente de alimentación adecuada para el servomotor[cite: 80]
* **Interfaz y Visualización:** 
  * 1x Teclado matricial 4x4[cite: 80]
  * 1x Pantalla LCD 16x2 con interfaz I2C (Dirección `0x27`)[cite: 79, 80]
* **Montaje y Software:** Caja de cartón, protoboard, cables Dupont, cable USB y Arduino IDE 
  con bibliotecas `Wire`, `LiquidCrystal_I2C`, `ESP32Servo` y `Keypad`[cite: 80].

---

## 🔌 Pinout y Conexiones

| Componente | Pin ESP32 | Función |
| :--- | :---: | :--- |
| **Sensor LM35** | `GPIO 35` | Lectura analógica de temperatura[cite: 80] |
| **Señal del servomotor** | `GPIO 13` | Control de posición angular[cite: 80] |
| **LCD I2C (SDA / SCL)** | `GPIO 27 / 26` | Comunicación de datos y reloj I2C[cite: 80] |
| **Teclado - Filas (1 a 4)** | `GPIO 19, 18, 5, 4` | Lectura de filas del teclado matricial[cite: 80] |
| **Teclado - Columnas (1 a 4)**| `GPIO 32, 33, 25, 14` | Lectura de columnas del teclado matricial[cite: 80, 81] |

> ⚠️ **Nota de Seguridad:** Mantén separadas físicamente las conexiones de baja tensión del 
> ESP32 y las conexiones de potencia del foco[cite: 83]. Asegúrate de que la alimentación de 
> corriente alterna esté aislada y protegida, y manipúlala sin energía conectada[cite: 83].

---

## ⚙️ Parámetros y Ecuaciones del Controlador

* **Error de control:** $\text{Error} = \text{Setpoint} - \text{Temperatura real}$[cite: 78]
* **Salida proporcional:** $\text{Salida} = K_p \times \text{Error}$ (limitada entre `0%` y `100%`)[cite: 77]
* **Teclado matricial:** tecla `A` para editar *Setpoint*, tecla `B` para editar $K_p$, `#` para 
  confirmar y `*` para borrar la entrada[cite: 78, 79].

| Parámetro | Valor Inicial | Parámetro | Valor Inicial |
| :--- | :---: | :--- | :---: |
| **Setpoint** | $30^\circ\text{C}$[cite: 89] | **Intervalo entre muestras** | $10\text{ ms}$[cite: 89] |
| **Constante $K_p$** | $10$[cite: 89] | **Salida mínima / máxima** | $0\%$ / $100\%$[cite: 89] |
| **Margen de estabilidad** | $\pm 1.3^\circ\text{C}$[cite: 89] | **Ángulo servo mín. / máx.** | $5^\circ$ / $175^\circ$[cite: 89] |
| **Actualización del control** | $3\text{ segundos}$[cite: 89] | **Muestras LM35 / Offset** | $7\text{ muestras}$ / $100\text{ mV}$[cite: 77, 89] |

---

## 👥 Autores y Créditos

* **Alejandro Almanza Perez**[cite: 72]
* **Vanessa Guadalupe Soria Zavala**[cite: 72]
* **Adán Rodriguez Ortiz**[cite: 72]

**Institución:** Universidad Politécnica del Bicentenario (UPB) — Silao, Guanajuato[cite: 71, 72]  
**Asignatura:** Sistemas Embebidos (Grupo IME 702)[cite: 72, 73]  
**Docente:** Hugo Antonio Méndez Guzmán[cite: 72]

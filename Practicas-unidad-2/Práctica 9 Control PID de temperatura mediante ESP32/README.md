# 🎛️ Práctica 9 — Control PID de Temperatura mediante ESP32

![Microcontrolador](https://img.shields.io/badge/Microcontrolador-ESP32-blue)
![Control](https://img.shields.io/badge/Control-PID%20%2B%20Anti--Windup-red)
![Sensor](https://img.shields.io/badge/Sensor-LM35%20(ADC)-teal)
![Grupo](https://img.shields.io/badge/Grupo-IME%20702-orange)

Sistema de regulación térmica en lazo cerrado implementado en **ESP32** con el 
sensor analógico **LM35**, un **servomotor** acoplado mecánicamente a la perilla 
de un **dimmer** para variar la potencia de un **foco** dentro de una caja, un 
**teclado matricial 4x4** para ajustar el *Set Point* y las constantes (`Kp`, `Ki`, `Kd`) 
en tiempo real, y una **pantalla LCD 16x2 I2C** para monitorear el proceso[cite: 155, 159, 160].

---

## 📌 Asignación de Pines

| Componente | Pin / Terminal | Pin del ESP32 | Función |
| :--- | :--- | :--- | :--- |
| **Sensor LM35** | Salida analógica | `GPIO 35`[cite: 159] | Medición de temperatura interna (`10 mV/°C`)[cite: 156, 159] |
| **Servomotor** | Señal PWM (`50 Hz`) | `GPIO 13`[cite: 159, 164] | Posición angular (`5°` a `175°`) acoplada al dimmer[cite: 158, 163, 168] |
| **LCD 16x2 I2C** | `SDA` / `SCL` | `GPIO 27` / `GPIO 26`[cite: 159] | Bus I2C (`0x27`) para `T`, `SP`, `E` y `OUT` (%)[cite: 163, 168, 169] |
| **Teclado 4x4 (Filas)** | Filas 1 a 4 | `GPIO 19`, `18`, `5`, `4`[cite: 159, 160] | Barrido de filas del teclado matricial[cite: 160, 163] |
| **Teclado 4x4 (Columnas)** | Columnas 1 a 4 | `GPIO 32`, `33`, `25`, `14`[cite: 160, 163] | Lectura de columnas del teclado matricial[cite: 160, 163] |

---

## ⌨️ Mapa de Teclas y Algoritmo PID

### Configuración desde el Teclado Matricial 4x4

| Tecla | Función |
| :--- | :--- |
| **`A`** | Seleccionar / editar **Set Point** (`SP`)[cite: 164, 167] |
| **`B`** | Seleccionar / editar constante proporcional (**`Kp`**)[cite: 164, 167] |
| **`C`** | Seleccionar / editar constante integral (**`Ki`**)[cite: 164, 167] |
| **`D`** | Seleccionar / editar constante derivativa (**`Kd`**)[cite: 164, 167] |
| **`0–9`** | Ingresar caracteres numéricos[cite: 167] |
| **`*`** | Ingresar punto decimal[cite: 167] |
| **`#`** | Confirmar y aplicar el valor ingresado[cite: 167] |

### Características del Control PID Discreto

* **Periodo de muestreo (`Ts`):** Ejecución periódica cada `3.0 s` mediante `millis()`[cite: 164, 165, 167].
* **Acondicionamiento del LM35:** Promedio de 5 muestras (separadas `10 ms`), 
  compensación de offset de `100 mV` y conversión a `°C`[cite: 164, 167].
* **Ecuaciones PID:** Calcula $P = K_p \cdot \text{Error}$, acumulación integral 
  discreta con $T_s$ y término derivativo sobre la medición ($D = -K_d \cdot \frac{T_{\text{actual}} - T_{\text{anterior}}}{T_s}$)[cite: 157, 166, 168].
* **Anti-windup y saturación:** Limita la salida a `0–100%` y detiene la 
  acumulación integral cuando el actuador está saturado en el sentido del error[cite: 166, 168].

---

## ⚠️ Notas de Seguridad y Montaje

* **Manipulación de dimmer y foco:** El acoplamiento mecánico entre el servomotor 
  y la perilla del dimmer opera sobre una carga de iluminación y calentamiento; 
  mantén aisladas las conexiones de potencia y verifica la fijación mecánica 
  antes de energizar[cite: 155, 158, 160, 162].
* **Calibración inicial:** Las constantes `Kp`, `Ki` y `Kd` inician en `0.0`, 
  por lo que es necesario ingresarlas mediante el teclado para activar la respuesta 
  de control y ajustarlas según la dinámica térmica de la caja[cite: 163, 164, 171].

---

## 👥 Autores y Créditos

* **Alejandro Almanza Perez** (Matrícula: `24033177`)[cite: 152]
* **Vanessa Guadalupe Soria Zavala** (Matrícula: `24030215`)[cite: 152]
* **Adán Rodriguez Ortiz** (Matrícula: `24033563`)[cite: 152]

**Institución:** Universidad Politécnica del Bicentenario (UPB) — Silao, Guanajuato[cite: 152]  
**Asignatura:** Sistemas Embebidos (Grupo IME 702)[cite: 153]  
**Docente:** Hugo Antonio Méndez Guzmán[cite: 152]

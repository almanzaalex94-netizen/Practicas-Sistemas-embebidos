# 💧 Práctica 2 — Control ON-OFF de Nivel (ESP32)

![Microcontrolador](https://img.shields.io/badge/Microcontrolador-ESP32-blue)
![Sensor](https://img.shields.io/badge/Sensor-HC--SR04-teal)
![Bus](https://img.shields.io/badge/Comunicación-I2C%20(0x27)-blueviolet)
![Grupo](https://img.shields.io/badge/Grupo-IME%20702-orange)

Sistema de monitoreo y control automático del nivel de líquido en un tanque 
mediante un sensor ultrasónico **HC-SR04**, pantalla **LCD 16x2 I2C**, tres 
pulsadores (`SELECT`, `UP`, `DOWN`) para ajustar los umbrales de nivel bajo (**LL**) 
y nivel alto (**HL**), y dos relevadores que accionan bombas de llenado y drenado[cite: 123, 128, 129].

---

## 📌 Asignación de Pines

| Componente | Pin ESP32 | Tipo / Modo | Función |
| :--- | :--- | :--- | :--- |
| **HC-SR04 (TRIG)** | `GPIO 13`[cite: 128] | Salida digital[cite: 128] | Emite el pulso ultrasónico de disparo[cite: 128] |
| **HC-SR04 (ECHO)** | `GPIO 14`[cite: 128] | Entrada digital[cite: 128] | Recibe el eco para calcular la distancia[cite: 128] |
| **Botón SELECT** | `GPIO 18`[cite: 128] | `INPUT_PULLUP`[cite: 128] | Selecciona el umbral a editar (`LL` o `HL`)[cite: 128, 129] |
| **Botón UP** | `GPIO 32`[cite: 129] | `INPUT_PULLUP`[cite: 129] | Incrementa en 5% el umbral seleccionado[cite: 129, 130] |
| **Botón DOWN** | `GPIO 19`[cite: 129] | `INPUT_PULLUP`[cite: 129] | Decrementa en 5% el umbral seleccionado[cite: 129, 130] |
| **LCD I2C (SDA / SCL)** | `GPIO 26` / `GPIO 27`[cite: 129] | Bus I2C (`0x27`)[cite: 129, 130] | Muestra `LL`, `AL`, `HL`, litros y estado del ciclo[cite: 130, 141, 142] |
| **Relé de Llenado (IN)** | `GPIO 4`[cite: 129] | Salida digital (activo en bajo)[cite: 129] | Activa la bomba de llenado (`LOW` = encendido)[cite: 129, 130] |
| **Relé de Drenado (IN)** | `GPIO 5`[cite: 129] | Salida digital (activo en bajo)[cite: 129] | Activa la bomba de drenado (`LOW` = encendido)[cite: 129, 130] |

---

## ⚙️ Características Clave del Diseño y Software

* **Filtrado ultrasónico:** Toma 5 lecturas consecutivas, descarta valores fuera de 
  rango (menores a `0.5 cm` o mayores a `30 cm`) y calcula la mediana[cite: 130, 139].
* **Temporización con `millis()`:** Lectura de botones cada `150 ms`, medición del 
  sensor cada `100 ms` y verificación del bus I2C cada `2 s` sin bloqueos[cite: 130, 141, 142].
* **Recuperación de bus I2C:** Si la LCD deja de responder en `0x27`, ejecuta 
  `recoverI2C()` para reinicializar el bus y la pantalla[cite: 130, 139, 141].
* **Ciclo ON-OFF con histéresis:** Llena hasta alcanzar **HL**, cambia a drenado 
  hasta bajar a **LL** y repite el ciclo de forma continua[cite: 130, 140, 142].

---

## ⚠️ Notas de Seguridad y Montaje

* **Verificación de *pinout* y fuentes:** Alimenta las bombas con fuente externa 
  independiente, mantén una tierra común (`GND`) y revisa las conexiones de los 
  relevadores antes de energizar para evitar daños en el ESP32[cite: 131, 144].
* **Lógica activa en bajo:** Verifica la lógica del módulo de relevadores; en la 
  versión final se utiliza `RELAY_ON = LOW` y `RELAY_OFF = HIGH`[cite: 130, 138, 144].

---

## 👥 Autores y Créditos

* **Alejandro Almanza Perez**[cite: 121]
* **Vanessa Guadalupe Soria Zavala**[cite: 121]
* **Adán Rodriguez Ortiz**[cite: 121]

**Institución:** Universidad Politécnica del Bicentenario (UPB) — Silao, Guanajuato[cite: 121]  
**Asignatura:** Sistemas Embebidos (Grupo IME 702)[cite: 122]  
**Docente:** Hugo Antonio Méndez Guzmán[cite: 121]

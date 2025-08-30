# Obstacle Detection System

An **ultrasonic-based obstacle detection system** that uses LEDs, a buzzer, and an LCD to provide real-time distance measurement and alerts.  
Ideal for **embedded systems, robotics, and assistive navigation** applications.  

## 📌 Features
- 📡 **Ultrasonic Sensor (HC-SR04):** Measures distance to nearby objects.  
- 🔴🟡🟢 **LED Indicators:**
  - **Red LED + Buzzer** → Obstacle very close (danger zone).  
  - **Yellow LED** → Obstacle at moderate distance (warning zone).  
  - **Green LED** → No obstacle nearby (safe zone).  
- 📟 **16x2 I2C LCD Display:** Shows live distance readings in cm.  
- ⏱️ **Non-blocking timing logic** using `millis()` for smooth LED blinking and buzzer control.  

## 🛠️ Components Used
- Arduino UNO / Nano / Mega  
- HC-SR04 Ultrasonic Sensor  
- LEDs (Red, Yellow, Green)  
- Buzzer  
- 16x2 LCD with I²C Module  
- Resistors, Jumper wires, Breadboard  

## ⚡ Circuit Connections

| Component            | Arduino Pin |
|----------------------|-------------|
| HC-SR04 Trigger      | D4          |
| HC-SR04 Echo         | D3          |
| Red LED              | D12         |
| Yellow LED           | D11         |
| Green LED            | D10         |
| Buzzer               | D9          |
| Push Button (optional)| D2          |
| LCD (I²C)            | SDA → A4, SCL → A5 |

## 📂 Code
The Arduino sketch handles:
- Triggering and reading the ultrasonic sensor.  
- Distance calculation (cm).  
- Controlling LEDs and buzzer based on thresholds.  
- Displaying distance on the LCD.  

👉 Full code is available in [`obstacle_detection.ino`](https://github.com/KaashyaPing/obstactle-detection/blob/main/obstacle_detection.ino).  

## 🚀 How It Works
1. The ultrasonic sensor continuously measures the distance to obstacles.  
2. Depending on distance thresholds:  
   - `< 10 cm` → Red LED blinks + buzzer sounds.  
   - `10–20 cm` → Yellow LED blinks.  
   - `> 20 cm` → Green LED stays ON.  
3. The LCD displays the live distance in centimeters.  

## 📸 Demo 

![Green LED](https://raw.githubusercontent.com/KaashyaPing/obstactle-detection/refs/heads/main/green.jpg)

When the obstacle is placed at a distance of more than 20cm, then the **Green LED** is ON.

![Yellow LED](https://raw.githubusercontent.com/KaashyaPing/obstactle-detection/refs/heads/main/yellow.jpg)

When the obstacle is placed at a distance between 10cm and 20cm, then the **Yellow LED** is ON.

![Red LED](https://raw.githubusercontent.com/KaashyaPing/obstactle-detection/refs/heads/main/red.jpg)

When the obstacle is placed at a distance less than 10cm, then the **Red LED** is ON with **buzzer** noise.

## Caveats

- **Occasional buzzer activation** may occur even when no obstacle is in the red (danger) zone.
- This is **not** due to intentional “idle bursts” from the Arduino board. Rather, the most plausible cause is **electrical interference introduced via wiring**, i.e., **noise on the ground or supply lines** (especially in noisy environments or with inadequate decoupling) may induce transient signals that trigger the buzzer.

## 🧑‍💻 Author
**Kaashyap Sai Varma Bhupathiraju**  
ECE Enthusiast | Embedded Systems | Arduino & IoT  


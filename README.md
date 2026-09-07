# 🏠 Edge Intelligence-Based Adaptive Home Automation and Security Alert System using TinyML & IoT

> An intelligent IoT-based home automation and security system that combines **Embedded Systems, TinyML, Edge AI, and IoT** to detect hazardous gas and flame conditions and automatically initiate safety responses.

---

## 📌 Project Overview

The **Edge Intelligence-Based Adaptive Home Automation and Security Alert System** is an intelligent safety and automation solution developed using an **ESP32 microcontroller, TinyML, IoT, and multiple sensors**.

The system continuously monitors the home environment for **gas leakage, smoke, flame, temperature, and humidity**.

A **TinyML classification model trained using Edge Impulse** is deployed directly on the ESP32 using a **quantized TensorFlow Lite model**. This enables the system to perform gas-related classification locally at the edge.

When a hazardous condition is detected, the system automatically responds by activating appropriate safety mechanisms such as an **exhaust fan, servo-controlled window, buzzer, and visual indicators**.

The system is also connected to a **Blynk IoT mobile dashboard**, allowing the user to monitor environmental parameters and security conditions remotely.

---

## 🎯 Objectives

The main objectives of this project are:

- To develop an intelligent home security and automation system using ESP32.
- To detect hazardous gas conditions using TinyML.
- To detect flame/fire using a flame sensor.
- To monitor temperature and humidity in real time.
- To perform AI-based decision-making directly at the edge.
- To automatically activate safety mechanisms during hazardous conditions.
- To provide remote monitoring through Blynk IoT.
- To reduce response latency through local processing.
- To integrate AI, IoT, sensors, and actuators into a single embedded system.

---

## 💡 Problem Statement

Conventional home safety systems often depend on simple threshold-based detection or cloud processing.

Threshold-based systems may not provide intelligent classification, while cloud-dependent systems can introduce communication delays and require continuous internet connectivity for decision-making.

Therefore, this project proposes an **edge-intelligent home safety system** where sensor data can be processed locally using **TinyML on an ESP32**, while IoT connectivity is used for remote monitoring and notification.

---

## 💭 Proposed Solution

The proposed system combines:

**Embedded Systems + TinyML + IoT + Sensors + Automation**

The ESP32 acts as the central controller.

The MQ-2 sensor monitors gas/smoke conditions, while a flame sensor detects fire. The DHT11 sensor measures temperature and humidity.

The gas-related sensor data is processed using a TinyML classification model deployed on the ESP32.

When a hazardous condition is detected, the system automatically activates the required safety mechanism.

---

# 🧩 System Architecture

```text
                         ┌─────────────────────┐
                         │        ESP32        │
                         │  Main Controller    │
                         └──────────┬──────────┘
                                    │
              ┌─────────────────────┼─────────────────────┐
              │                     │                     │
              ▼                     ▼                     ▼
       ┌─────────────┐       ┌─────────────┐       ┌─────────────┐
       │ MQ-2 Gas    │       │   Flame     │       │   DHT11     │
       │   Sensor    │       │   Sensor    │       │   Sensor    │
       └──────┬──────┘       └──────┬──────┘       └──────┬──────┘
              │                     │                     │
              ▼                     ▼                     ▼
       ┌─────────────┐       ┌─────────────┐       Temperature
       │   TinyML    │       │    Fire     │       & Humidity
       │Classification│      │  Detection  │        Monitoring
       └──────┬──────┘       └──────┬──────┘
              │                     │
              └──────────┬──────────┘
                         │
                         ▼
                ┌──────────────────┐
                │ Safety Decision  │
                └────────┬─────────┘
                         │
             ┌───────────┼───────────┐
             │           │           │
             ▼           ▼           ▼
       ┌──────────┐ ┌──────────┐ ┌──────────┐
       │  Relay   │ │  Servo   │ │  Buzzer  │
       │   Fan    │ │  Window  │ │  Alert   │
       └────┬─────┘ └────┬─────┘ └──────────┘
            │             │
            ▼             ▼
       Exhaust Fan    Window Opens


```

## 📁 Project Demonstration

![Project Demonstration](project-demo.png)

## 🔧 Hardware Components

| Component | Purpose |
|---|---|
| ESP32 | Main controller and edge processing |
| MQ-2 Gas Sensor | Gas and smoke detection |
| Flame Sensor | Fire/flame detection |
| DHT11 | Temperature and humidity monitoring |
| Relay Module | Controls exhaust fan |
| Servo Motor | Controls automatic window |
| Buzzer | Audible safety alert |
| LED | Visual status indication |

## 💻 Software & Technologies

- Embedded C/C++
- ESP32
- Arduino IDE
- TinyML
- Edge Impulse
- TensorFlow Lite
- Blynk IoT
- Wi-Fi

## 🤖 TinyML Implementation

The gas detection component uses a machine-learning classification model trained using Edge Impulse.

The trained model is converted into a **quantized TensorFlow Lite model** and deployed directly on the ESP32.

This enables local inference without depending on cloud processing for the primary gas classification decision.

## ⚙️ System Working

1. The MQ-2 sensor continuously monitors gas/smoke conditions.
2. Sensor data is processed by the TinyML model running on the ESP32.
3. The flame sensor independently monitors for fire.
4. DHT11 measures temperature and humidity.
5. When a hazardous gas condition is detected, the relay activates the exhaust fan.
6. The servo motor opens the window automatically.
7. When flame is detected, the buzzer provides an audible alert.
8. Sensor and system status are displayed on the Blynk IoT dashboard.
9. The user can remotely monitor the system through the mobile dashboard.

## 🚨 Detection Conditions

### 🟢 Normal Condition

- No hazardous gas detected
- No flame detected
- Exhaust fan remains OFF
- Servo remains in normal position
- Environmental data is monitored through Blynk

### 🔴 Hazardous Condition

- Gas detected by TinyML
- Flame detected by flame sensor
- Exhaust fan turns ON
- Servo-controlled window is activated
- Buzzer provides an alert
- Status is displayed on Blynk

## 📱 Blynk IoT Dashboard

The Blynk dashboard provides remote monitoring of:

- Gas status
- Flame status
- Temperature
- Humidity
- System connectivity

## 📌 Pin Configuration

| Component | ESP32 Pin |
|---|---:|
| DHT11 | GPIO 14 |
| MQ-2 Gas Sensor | GPIO 34 |
| Flame Sensor | GPIO 27 |
| Relay Module | GPIO 26 |
| Servo Motor | GPIO 13 |

## 📂 Project Structure

```text
Edge-Intelligence-based-Adaptive-Home-Automation-and-Security-alert-System-using-TinyML-and-IoT/
│
├── README.md
├── project-demo.png
│
└── src/
    └── main.ino
```

## 🛠️ How to Run

1. Install the **Arduino IDE**.
2. Install ESP32 board support.
3. Install the required libraries.
4. Add the Edge Impulse inference library.
5. Open the Arduino `.ino` file.
6. Enter your Wi-Fi and Blynk credentials.
7. Select the correct ESP32 board and COM port.
8. Upload the program to the ESP32.
9. Connect the sensors and actuators according to the pin configuration.
10. Open the Blynk dashboard and monitor the system.

## 📚 Libraries Used

```cpp
WiFi.h
BlynkSimpleEsp32.h
DHT.h
ESP32Servo.h
Gas_Detection_inferencing.h
```

## 🔐 Safety Note

This project is developed as an **academic prototype** for demonstrating TinyML-based edge intelligence, IoT monitoring, and automated safety responses. It should not be considered a certified replacement for professional gas or fire safety systems.

## 👩‍💻 Author

**Devadharshini Esther D**

Embedded Systems & IoT | TinyML | Edge AI | Data Analytics

## ⭐ Future Enhancements

- Improved gas classification accuracy
- Additional gas sensors
- Advanced fire detection
- Mobile notification improvements
- Cloud data logging
- Energy-efficient operation
- PCB-based implementation
- Integration with automotive and industrial safety applications
                         ▼
                 ┌─────────────────┐
                 │    Blynk IoT     │
                 │ Mobile Dashboard │
                 └─────────────────┘



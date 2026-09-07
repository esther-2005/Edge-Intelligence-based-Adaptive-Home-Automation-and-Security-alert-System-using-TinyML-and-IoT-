# Edge-Intelligence-based-Adaptive-Home-Automation-and-Security-alert-System-using-TinyML-and-IoT-
An intelligent home automation and security system that combines ESP32, TinyML, IoT, and sensor-based automation to detect gas leakage and fire conditions and automatically trigger safety actions.

📌Project Overview
The system continuously monitors the home environment using multiple sensors. Gas-related sensor data is processed using a TinyML classification model deployed on the ESP32, enabling local and low-latency decision-making.
When a hazardous condition is detected, the system automatically activates safety mechanisms such as an exhaust fan, servo-controlled window, buzzer, and remote IoT alerts.
The user can monitor the system remotely through a Blynk mobile dashboard.

🎯Objectives
Detect hazardous gas conditions using TinyML
Detect flame/fire using a flame sensor
Monitor temperature and humidity
Automatically activate safety mechanisms
Provide real-time remote monitoring through IoT
Perform intelligent decision-making at the edge
Reduce response latency by processing data locally

⚙️Hardware Components
Component
Purpose
ESP32
Main controller and edge-processing unit
MQ-2 Gas Sensor
Gas/smoke sensing
DHT11
Temperature and humidity monitoring
Flame Sensor
Fire/flame detection
Servo Motor
Automatic window mechanism
Relay Module
Controls exhaust fan
Exhaust Fan
Removes contaminated air
Buzzer
Audible safety alert
LEDs
Visual indication
Breadboard & Jumper Wires
Circuit prototyping

💻 Software & Technologies
Embedded C/C++
ESP32
Arduino IDE
TinyML
Edge Impulse
TensorFlow Lite
Blynk IoT
Wi-Fi
Sensor interfacing

🤖 TinyML Implementation
The gas detection component uses a machine-learning classification model trained using Edge Impulse.
The trained model is converted into a quantized TensorFlow Lite model and deployed directly on the ESP32.
Why TinyML?
Instead of sending all sensor data to a cloud server for processing, the ESP32 can perform the classification locally.
This provides:
⚡ Faster decision-making
📉 Lower latency
🔒 Local data processing
🌐 Reduced dependence on cloud processing
🔋 Efficient edge operation

⚙️ Working Principle
1. Normal Condition
The sensors continuously monitor the environment.
Sensors → ESP32 → Monitoring
No hazardous condition is detected, so the safety mechanisms remain inactive.
2. Gas Detection
When the TinyML model identifies a hazardous gas condition:
MQ-2
  ↓
ESP32
  ↓
TinyML Classification
  ↓
Gas Detected
  ↓
Relay → Exhaust Fan ON
  ↓
Servo → Window Opens
  ↓
Blynk → Status Updated
3. Flame Detection
When the flame sensor detects fire:
Flame Sensor
      ↓
    ESP32
      ↓
Flame Detected
      ↓
Buzzer / Alert
      ↓
Blynk Dashboard

IoT Monitoring
The system is integrated with Blynk IoT for remote monitoring.
The dashboard displays:
🌫️ Gas status
🔥 Flame status
🌡️ Temperature
💧 Humidity
🔔 Safety alerts
📸 Project Demonstration
🔌 Connection & Setup

📊 Key Features
✅ TinyML-based gas classification
✅ Flame detection
✅ ESP32 edge processing
✅ Automated exhaust fan control
✅ Servo-based window automation
✅ Real-time IoT monitoring
✅ Blynk mobile dashboard
✅ Temperature & humidity monitoring
✅ Audible and visual alerts
✅ Low-latency decision making

🌱 Future Scope
Integration of additional environmental sensors
Advanced anomaly detection using TinyML
Camera-based fire detection
Improved mobile notifications
PCB-based compact hardware implementation
Battery/solar-powered operation
Integration with smart-home platforms

👩‍💻 My Contribution
I worked on the ESP32-based embedded implementation, sensor interfacing, TinyML integration, IoT monitoring, and hardware-software integration of the system.
This project strengthened my practical knowledge of Embedded Systems, IoT, Edge AI, TinyML, and intelligent automation.

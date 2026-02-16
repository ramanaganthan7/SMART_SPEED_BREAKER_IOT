# Automatic Smart Speed Breaker based on Vehicle Speed with IoT

## Project Overview
This project is an **IoT-enabled Smart Speed Breaker system** designed to automate traffic safety. The system uses dual IR sensors to calculate the real-time speed of approaching vehicles. If a vehicle exceeds the permitted speed limit, the **ESP32 NodeMCU** triggers a **Servo Motor** to raise a physical speed breaker. Additionally, the system provides visual feedback via an LCD and LEDs, and can transmit speed data to an IoT platform for remote monitoring.

---

## Tools and Components Used

### Core Hardware
* **ESP32 NodeMCU:** The central microcontroller with Wi-Fi capabilities for IoT integration.
* **IR Sensor Modules (x2):** Used as a speed trap to detect vehicle entry and exit points.
* **Servo Motor:** High-torque motor used to physically actuate the speed breaker mechanism.
* **16x2 LCD Display:** Provides real-time speed readings and status alerts to the driver.
* **Traffic LED Indicators:** Red, Yellow, and Green LEDs for visual speed warnings.

### Software & Protocols
* **Arduino IDE:** For programming the ESP32.
* **IoT Protocols:** (e.g., MQTT or HTTP) for data logging to the cloud.
* **C++ / Arduino Language:** Logic for time-distance speed calculation.

---

<h1>Circuit Diagram</h1>
<img src="preview/circuit.png" />
<br />

<h1>Project Glimpse</h1>
<div align="center">
  <img src="preview/gim1.jpeg" width="30%" />
  <img src="preview/gim2.jpeg" width="30%" />
  <img src="preview/gim3.jpeg" width="30%" />
</div>

---

### Designed by
**RAMANA GANTHAN S.**

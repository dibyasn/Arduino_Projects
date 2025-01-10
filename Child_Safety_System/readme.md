# 🚸 Child Safety Washroom System with SOS Button and Timer

## 📖 Overview

The **Child Safety Washroom System** is designed to enhance safety in washrooms by monitoring presence, timing activity, and providing emergency (SOS) alerts when necessary. This system uses an ultrasonic sensor to detect presence, an OLED display to show status updates, and a buzzer and LED for alerts. An SOS button is included for emergencies, and the system tracks time to ensure no prolonged occupancy.

---

## 📝 Table of Contents

- [🚸 Child Safety Washroom System with SOS Button and Timer](#-child-safety-washroom-system-with-sos-button-and-timer)
  - [📖 Overview](#-overview)
  - [📝 Table of Contents](#-table-of-contents)
  - [✨ Features](#-features)
  - [🛠️ Components Required](#️-components-required)
  - [⚙️ Hardware Setup](#️-hardware-setup)
    - [Wiring Diagram](#wiring-diagram)
  - [📜 Code Explanation](#-code-explanation)
    - [Key Features in Code:](#key-features-in-code)
  - [📚 Required Libraries](#-required-libraries)
  - [🚀 Setup Instructions](#-setup-instructions)
    - [1. Clone the Repository](#1-clone-the-repository)
    - [2. Install Required Libraries](#2-install-required-libraries)
    - [3. Assemble the Circuit](#3-assemble-the-circuit)
    - [4. Upload the Code](#4-upload-the-code)
  - [🚀 Usage Instructions](#-usage-instructions)
  - [🔧 Troubleshooting](#-troubleshooting)
  - [📦 Future Improvements](#-future-improvements)
  - [🙌 Acknowledgments](#-acknowledgments)
  - [📁 Project Files](#-project-files)

---

## ✨ Features

1. **Presence Detection**:
   - Uses an ultrasonic sensor to monitor the presence of a person within a predefined distance.
2. **Timer Monitoring**:
   - Tracks the time of presence and triggers an alert if the occupancy exceeds the set time limit.
3. **SOS Button**:
   - An emergency button that triggers an instant alert when pressed.
4. **Visual and Audio Alerts**:
   - Includes a buzzer and LED for alarms.
5. **OLED Display**:
   - Provides real-time updates about the system status and elapsed time.

---

## 🛠️ Components Required

- **ESP32** 
- **Ultrasonic Sensor** (HC-SR04)
- **OLED Display** (SSD1306, 128x64 resolution)
- **Buzzer**
- **LED**
- **SOS Button**
- **Resistors**
- Jumper wires and breadboard

---

## ⚙️ Hardware Setup

1. **Ultrasonic Sensor**:
   - **TRIG_PIN**: GPIO 15
   - **ECHO_PIN**: GPIO 13
2. **Buzzer**:
   - Connected to GPIO 26
3. **LED**:
   - Connected to GPIO 12
4. **SOS Button**:
   - Connected to GPIO 32 with a pull-down resistor.
5. **OLED Display**:
   - **SDA**: GPIO 21
   - **SCL**: GPIO 22

### Wiring Diagram
Refer to the following pin connections:

| Component         | Arduino Pin |
|-------------------|-------------|
| Ultrasonic TRIG   | GPIO 15     |
| Ultrasonic ECHO   | GPIO 13     |
| Buzzer            | GPIO 26     |
| LED               | GPIO 12     |
| SOS Button        | GPIO 32     |
| OLED SDA          | GPIO 21     |
| OLED SCL          | GPIO 22     |

---

## 📜 Code Explanation

### Key Features in Code:

1. **Presence Detection**:
   - Monitors the distance using an ultrasonic sensor.
   - If the distance is below the threshold, presence is detected.

2. **Timer Management**:
   - Starts timing when a person is detected.
   - Triggers an alert if the presence time exceeds the limit.

3. **SOS Alert**:
   - An interrupt-based mechanism detects SOS button presses.
   - Instantly activates the buzzer, LED, and an alert message on the OLED.

4. **Reset Mechanism**:
   - Resets the system when the washroom becomes vacant.

5. **OLED Updates**:
   - Displays system status and elapsed time dynamically.

6. **Blinking Alerts**:
   - Red LED blinks when alerts are active.

7. **Sound Alerts**:
   - Buzzer emits sound during alerts to signal emergencies.

---

## 📚 Required Libraries

Ensure the following libraries are installed in your Arduino IDE:

- **Adafruit SSD1306**: For controlling the OLED display. Install via Arduino Library Manager or from [Adafruit GitHub Repository](https://github.com/adafruit/Adafruit_SSD1306).
- **Adafruit GFX**: A supporting graphics library for OLEDs. Install via Arduino Library Manager or from [Adafruit GitHub Repository](https://github.com/adafruit/Adafruit-GFX-Library).
- **NewPing**: For using the ultrasonic sensor. Install via Arduino Library Manager or from [NewPing GitHub Repository](https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home).

---

## 🚀 Setup Instructions

### 1. Clone the Repository
```bash
git clone https://github.com/dibyasn/Arduino_Projects.git
cd Arduino_Projects/Child_Safety_System
```

### 2. Install Required Libraries
Ensure you have the following libraries installed in your Arduino IDE:
- **Adafruit GFX Library** 🌐
- **Adafruit SSD1306 Library** 🌐
- **NewPing Library** 🌐

### 3. Assemble the Circuit
Use the wiring diagram provided in the **Hardware Setup** section to connect all components.

### 4. Upload the Code
1. Open the Arduino IDE.
2. Select the correct **Board** and **Port**.
3. Navigate to the `Code` folder and upload the `Code.ino` sketch.

---


## 🚀 Usage Instructions

1. **Initial Setup**:
   - Power the system.
   - The OLED will display "System Initialized" and "Waiting for Activity".
2. **During Use**:
   - Presence detection activates when someone enters the range of the ultrasonic sensor.
   - The elapsed time will be shown on the OLED display.
3. **SOS Activation**:
   - Press the SOS button to trigger an immediate alert.
4. **Timeout Alert**:
   - If the time limit is exceeded, an alert will activate, requiring manual reset.

---

## 🔧 Troubleshooting

1. **OLED Display Issues**:
   - Ensure proper I2C connections (SDA and SCL).
   - Verify the I2C address (default is `0x3C`).
   - Ensure the required libraries (`Adafruit SSD1306`, `Adafruit GFX`) are installed.
2. **Ultrasonic Sensor Malfunction**:
   - Check the TRIG and ECHO connections.
   - Ensure the sensor is not obstructed.
3. **SOS Button Not Responding**:
   - Verify the button wiring and pull-down resistor, ensuring the controller (GPIO32) receives VCC when the button is pressed.
   - Ensure the interrupt pin is correctly assigned.
4. **Buzzer or LED Not Working**:
   - Check the wiring and ensure the components are functional.

---

## 📦 Future Improvements

- Adding a network module for remote monitoring and alerts.
- Integration with a mobile app for notifications.
- Enhancing the user interface on the OLED display.

---

## 🙌 Acknowledgments

This project is inspired by the need for enhanced child safety in public and private washrooms. Special thanks to the open-source Arduino community and the creators of libraries used in this project.

---

## 📁 Project Files

- [Source Code](./Code/Code.ino)

---

<p align="center">
    <img src="https://64.media.tumblr.com/tumblr_lp0f2fIhnF1qa2ip8o1_1280.gif" alt="Thank You">
</p>

---

For any questions or suggestions, feel free to open an issue or contact us directly.

<p align="center">
    <a href="https://github.com/dibyasn"><img src="https://img.icons8.com/color/48/000000/github.png" alt="Contribute Icon"></a>
</p>
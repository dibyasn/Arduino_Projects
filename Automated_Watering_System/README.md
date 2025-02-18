# Automated Watering System 🌱💧

Welcome to the Automated Watering System project! This system leverages a soil moisture sensor and pumps to automate plant watering while providing visual and audio feedback.

## Table of Contents
- [Automated Watering System 🌱💧](#automated-watering-system-)
  - [Table of Contents](#table-of-contents)
  - [📖 Introduction](#-introduction)
  - [🔧 Components](#-components)
  - [🔌 Circuit Diagram](#-circuit-diagram)
    - [Connections:](#connections)
      - [OLED Display:](#oled-display)
      - [Soil Moisture Sensor:](#soil-moisture-sensor)
      - [DFPlayer Mini:](#dfplayer-mini)
      - [Motor Driver:](#motor-driver)
  - [🚀 Setup Instructions](#-setup-instructions)
    - [1. Clone the Repository](#1-clone-the-repository)
    - [2. Install Required Libraries](#2-install-required-libraries)
    - [3. Assemble the Circuit](#3-assemble-the-circuit)
    - [4. Upload the Code](#4-upload-the-code)
  - [💡 Code Explanation](#-code-explanation)
    - [Key Features of the Code:](#key-features-of-the-code)
    - [Example Code Snippet:](#example-code-snippet)
      - [Soil Moisture Logic](#soil-moisture-logic)
  - [📜 Additional Documentation](#-additional-documentation)
  - [🖥️ Usage](#️-usage)
  - [🎉 Acknowledgments](#-acknowledgments)

## 📖 Introduction
This project automates the task of watering plants by monitoring soil moisture levels. It activates pumps when the moisture level falls below a threshold and provides:
- Visual feedback on an OLED display (sad/smiley faces for low/adequate moisture).
- Audio notifications using a DFPlayer Mini module.

## 🔧 Components
- **ESP32**
- **Soil Moisture Sensor**
- **0.96" OLED Display** (SSD1306)
- **DFPlayer Mini** (for audio)
- **L293D Motor Driver**
- **Pump**
- **Jumper Wires**
- **Breadboard**

## 🔌 Circuit Diagram

### Connections:
#### OLED Display:
```plaintext
  OLED Display       ESP32
  ------------       ----
  VCC  ------------> 3.3V
  GND  ------------> GND
  SDA  ------------> GPIO21
  SCL  ------------> GPIO22
```

#### Soil Moisture Sensor:
```plaintext
  Soil Moisture Sensor ESP32
  -------------------- ----
  VCC ----------------> 3.3V
  GND ----------------> GND
  AO  ----------------> GPIO34
```

#### DFPlayer Mini:
```plaintext
  DFPlayer Mini       ESP32
  -------------       ----
  TX  ---------------> GPIO16
  RX  ---------------> GPIO17
  VCC ---------------> 3.3V
  GND ---------------> GND
```

#### Motor Driver:
```plaintext
  Motor Driver        ESP32
  -----               ----
  EN1 ------------> GPIO5
  IN1 ------------> GPIO25
  IN2 ------------> GPIO26
```

## 🚀 Setup Instructions

### 1. Clone the Repository
```bash
git clone https://github.com/dibyasn/Arduino_Projects.git
cd Arduino_Projects/Automated_Watering_System
```

### 2. Install Required Libraries
Ensure you have the following libraries installed in your Arduino IDE:
- **Adafruit GFX Library** 🌐
- **Adafruit SSD1306 Library** 🌐
- **DFPlayerMini_Fast Library** 🌐

### 3. Assemble the Circuit
Use the circuit diagram above to connect the components to the ESP32.

### 4. Upload the Code
1. Open the Arduino IDE.
2. Select the correct **Board** and **Port**.
3. Navigate to the `Code` folder and upload the `Code.ino` sketch.

## 💡 Code Explanation

### Key Features of the Code:
- **Soil Moisture Monitoring**: Reads analog values from the soil moisture sensor to determine moisture levels.
- **Pump Activation**: Turns pumps on or off based on soil moisture levels.
- **Visual Feedback**: Displays animations on an OLED screen.
- **Audio Alerts**: Plays an audio file using the DFPlayer Mini module.

### Example Code Snippet:
#### Soil Moisture Logic
```cpp
if (soilMoistureValue > 2000) {
    digitalWrite(EN1, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    display.drawBitmap(40, 8, frames1[frame], FRAME_WIDTH, FRAME_HEIGHT, 1);
} else {
    digitalWrite(EN1, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    display.drawBitmap(40, 8, frames2[frame], FRAME_WIDTH, FRAME_HEIGHT, 1);
}
```

## 📜 Additional Documentation
- [Project Details](./Assets/Soil%20Moisture.docx)
- [Source Code](./Code/Code.ino)

## 🖥️ Usage
1. Power on the ESP32.
2. Monitor soil moisture levels in real-time:
   - If the moisture is low, the system activates pumps and displays a sad face.
   - When the moisture level is sufficient, pumps turn off, and a smiley face is displayed.
3. Listen for audio alerts for pump activity.

## 🎉 Acknowledgments
This project combines the power of automation and user-friendly interfaces to simplify plant care. A big thank you to the open-source community for their amazing libraries and resources.

---

<p align="center">
    <img src="https://64.media.tumblr.com/tumblr_lp0f2fIhnF1qa2ip8o1_1280.gif" alt="Thank You">
</p>

---

For any questions or suggestions, feel free to open an issue or contact us directly.

<p align="center">
    <a href="https://github.com/dibyasn"><img src="https://img.icons8.com/color/48/000000/github.png" alt="Contribute Icon"></a>
</p>
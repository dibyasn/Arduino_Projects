# 🚸 Child Safety Washroom System with Telegram Alert, SOS Button and Timer

## 📖 Overview

The **Child Safety Washroom System** is an IoT-based safety solution designed to ensure the well-being of children in washrooms. It uses sensors to monitor occupancy, track the duration of stay, and respond to emergencies via an SOS button. The system includes visual and audio alerts and now features Telegram integration to notify caregivers in real-time if help is needed.

---

## 📝 Table of Contents

- [🚸 Child Safety Washroom System with Telegram Alert, SOS Button and Timer](#-child-safety-washroom-system-with-telegram-alert-sos-button-and-timer)
  - [📖 Overview](#-overview)
  - [📝 Table of Contents](#-table-of-contents)
  - [✨ Features](#-features)
  - [🛠️ Components Required](#️-components-required)
  - [⚙️ Hardware Setup](#️-hardware-setup)
    - [Pin Mapping](#pin-mapping)
  - [📜 Code Explanation](#-code-explanation)
    - [Key Highlights:](#key-highlights)
  - [📚 Required Libraries](#-required-libraries)
  - [🚀 Setup Instructions](#-setup-instructions)
    - [1. Clone the Repository](#1-clone-the-repository)
    - [2. Configure Wi-Fi and Telegram](#2-configure-wi-fi-and-telegram)
    - [3. Wiring](#3-wiring)
    - [4. Upload Code](#4-upload-code)
  - [🚀 Usage Instructions](#-usage-instructions)
    - [1. **System Initialization**](#1-system-initialization)
    - [2. **Presence Detection**](#2-presence-detection)
    - [3. **Timeout Alert**](#3-timeout-alert)
    - [4. **SOS Button**](#4-sos-button)
    - [5. **Reset**](#5-reset)
    - [6. 📟 OLED Screens](#6--oled-screens)
    - [7. 📤 Telegram Message Triggers](#7--telegram-message-triggers)
  - [🔧 Troubleshooting](#-troubleshooting)
  - [📦 Future Improvements](#-future-improvements)
  - [🙌 Acknowledgments](#-acknowledgments)
  - [📁 Project Files](#-project-files)

---

## ✨ Features

* ✅ **Presence Detection**: Using Ultrasonic Sensor
* ⏱ **Time Monitoring**: Triggers alert if user stays too long
* 🆘 **SOS Button**: Allows user to manually request help
* 🔒 **Reset with Long-Press** 
* 📲 **Telegram Notifications**:  Sends alert messages to caregiver when an SOS or timeout occurs.
* 💡 **Visual Indicators**: RED/GREEN LEDs to show occupancy.
* 🔊 **Buzzer Alert**: indicate safety or emergency states.
* 🖥 **OLED Display**: Shows real-time status and occupancy time.

---

## 🛠️ Components Required

* **ESP32**
* **Ultrasonic Sensor (HC-SR04)**
* **OLED Display (SSD1306)**
* **Buzzer (Active-Low)**
* **LEDs (Red and Green, Active-Low)**
* **SOS Button**
* **Resistors (for button pull-down)**
* **Jumper wires and breadboard**

---

## ⚙️ Hardware Setup

### Pin Mapping

| Component       | ESP32 Pin |
| --------------- | --------- |
| Ultrasonic TRIG | GPIO 15   |
| Ultrasonic ECHO | GPIO 13   |
| Buzzer          | GPIO 15   |
| Red LED         | GPIO 12   |
| SOS Button      | GPIO 32    |
| OLED SDA        | GPIO 21   |
| OLED SCL        | GPIO 22   |

> 🔧 **Notes**:
>
> * RED & GREEN LEDs and the buzzer are **Active-Low** (LOW = ON).
> * SOS Button is **pulled down** and connected to **Vcc** to trigger interrupt.

---

## 📜 Code Explanation

### Key Highlights:

* **Interrupt on SOS**: Button press instantly calls alert routine and sends Telegram message.
* **Presence Logic**: If a person stays beyond the safe time limit, triggers blinking LED and buzzer.
* **OLED Feedback**: Shows elapsed time and system messages.
* **Reset Routine**: Auto resets once the person exits.
* **Telegram Integration**: Uses `api.telegram.org` to send alerts via HTTP GET request.

---

## 📚 Required Libraries

* [NewPing](https://github.com/dnickless/NewPing) - For ultrasonic sensor
* [Adafruit\_SSD1306](https://github.com/adafruit/Adafruit_SSD1306) - For OLED
* [Ticker](https://github.com/espressif/arduino-esp32) - For non-blocking blinking
* WiFi & HTTPClient - Built-in ESP32 libraries for Wi-Fi and HTTP requests

Install libraries via **Arduino Library Manager**.

---

## 🚀 Setup Instructions

### 1. Clone the Repository

```bash
git clone https://github.com/dibyasn/Arduino_Projects.git
cd Arduino_Projects/Child_Safety_System/Child_Safety
```

### 2. Configure Wi-Fi and Telegram

* Wi-Fi SSID: **YOUR_SSID**
* Password: **PASSWORD**
* To get `botToken` and `chatID`:

  1. Create a bot via [@BotFather](https://t.me/botfather)
  2. Start chat with your bot
  3. Visit:

     ```
     https://api.telegram.org/bot<YOUR_BOT_TOKEN>/getUpdates
     ```

     Look for `"chat":{"id":...}` in the response.

---

### 3. Wiring

Refer to the **Hardware Setup** section for pin connections.

### 4. Upload Code

* Use Arduino IDE
* Board: **DOIT ESP32 DEVKIT V1**
* Upload the `.ino` file

---

## 🚀 Usage Instructions

### 1. **System Initialization**

* Connects to Wi-Fi
* Initializes OLED and peripherals
* Displays "Available" if system is ready

### 2. **Presence Detection**

* Uses ultrasonic sensor
* If distance ≤ `12cm`, person is considered present. Adjust distance (in cm) to detect presence (default: 12).
* Occupancy time is shown on OLED

### 3. **Timeout Alert**

* If person remains for more than `10 seconds`, alert is triggered:

  * OLED shows "Time Limit Exceeded"
  * RED LED blinks
  * Telegram alert is sent

### 4. **SOS Button**

* Triggered by pressing SOS button anytime
* Sends **repeating** Telegram messages every 4 seconds:

  * `🚨 SOS Button Pressed in Washroom!`
* OLED: `"SOS Activated"`
* RED LED blinks & buzzer makes danger sound

### 5. **Reset**

* When washroom is empty (no person detected):

  * System resets
  * Telegram message indicates vacancy
* Long press SOS button (5 sec) = reset
  * System resets
  * Telegram message: `✅ SOS Deactivated`

### 6. 📟 OLED Screens

| Situation           | OLED Output                         |
| ------------------- | ----------------------------------- |
| Connecting to Wi-Fi | `Connecting to WiFi`                |
| Wi-Fi Connected     | `WiFi Connected`                    |
| No Occupancy        | `Available`                         |
| Person Detected     | `Occupied from MM:SS` (live update) |
| Timeout             | `Time Limit Exceeded`               |
| SOS Pressed         | `SOS Activated`                     |

---

### 7. 📤 Telegram Message Triggers

| Event              | Message Sent                        |
| ------------------ | ----------------------------------- |
| SOS Button Pressed | 🚨 SOS Button Pressed in Washroom!  |
| Timeout Triggered  | ⚠️ Time Limit Exceeded in Washroom! |
| Vacant After Alert | ✅ Washroom is now vacant. All okay. |

---

## 🔧 Troubleshooting

| Issue                    | Solution                                                               |
| ------------------------ | ---------------------------------------------------------------------- |
| OLED not showing         | Check I2C address `0x3C`, SDA/SCL wiring                               |
| Telegram not sending     | Ensure ESP32 is connected to Wi-Fi and Chat ID is correct              |
| No detection from sensor | Check distance threshold and sensor pins                               |
| SOS button not working   | Ensure it connects to Vcc when pressed and is on correct interrupt pin |

---

## 📦 Future Improvements

* Add real-time monitoring on mobile app
* Use battery backup module for portability
* Store alert logs to SD card or cloud
* Add voice prompt using DFPlayer Mini

---

## 🙌 Acknowledgments

This project is inspired by the need for enhanced child safety in public and private washrooms. Thanks to the open-source Arduino community and Telegram Bot API for enabling smart alert features in DIY projects.

---

## 📁 Project Files

- [Source Code](./Child_Safety.ino)

---

<p align="center">
    <img src="https://64.media.tumblr.com/tumblr_lp0f2fIhnF1qa2ip8o1_1280.gif" alt="Thank You">
</p>

---

For any questions or suggestions, feel free to open an issue or contact us directly.

<p align="center">
    <a href="https://github.com/dibyasn"><img src="https://img.icons8.com/color/48/000000/github.png" alt="Contribute Icon"></a>
</p>
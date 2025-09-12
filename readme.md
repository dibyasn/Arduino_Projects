---

# 🚸 Child Safety Washroom System with Telegram Alerts, SOS & Timer

## 📖 Overview

The **Child Safety Washroom System** is a smart safety solution designed to protect children using washrooms. It monitors how long someone stays inside, sends alerts if they exceed a safe time limit, and offers an emergency SOS button for instant help. The system uses LEDs, a buzzer, an OLED screen, and even sends **Telegram notifications** in real time to alert caregivers, ensuring no emergency goes unnoticed.

---

## 📝 Table of Contents

* [✨ Features](#-features)
* [🛠️ Components Required](#️-components-required)
* [⚙️ Hardware Setup](#️-hardware-setup)

  * [Pin Mapping](#pin-mapping)
* [📜 Code Explanation](#-code-explanation)

  * [Key Highlights](#key-highlights)
* [📚 Required Libraries](#-required-libraries)
* [🚀 Setup Instructions](#-setup-instructions)

  * [1. Clone the Repository](#1-clone-the-repository)
  * [2. Configure Wi-Fi and Telegram](#2-configure-wi-fi-and-telegram)
  * [3. Wiring](#3-wiring)
  * [4. Upload Code](#4-upload-code)
* [🚀 Usage Instructions](#-usage-instructions)

  * [1. System Initialization](#1-system-initialization)
  * [2. Presence Detection](#2-presence-detection)
  * [3. Timeout Alert](#3-timeout-alert)
  * [4. SOS Mode](#4-sos-mode)
  * [5. Reset System](#5-reset-system)
  * [6. OLED Displays](#6-oled-displays)
  * [7. Telegram Notifications](#7-telegram-notifications)
* [🔧 Troubleshooting](#-troubleshooting)
* [📦 Future Improvements](#-future-improvements)
* [🙌 Acknowledgments](#-acknowledgments)
* [📁 Project Files](#-project-files)

---

## ✨ Features

✅ **Person Detection** via ultrasonic sensor
⏳ **Timer-based Safety Alert** (e.g. after 10 mins)
🆘 **Emergency SOS Button** (Interrupt-based)
🚨 **Buzzer & LED Alarms** with blinking danger signals
📲 **Telegram Alerts** for SOS and timeout
📟 **OLED Display** for live feedback
🔁 **Spam-Free Messaging** and repeat interval
🔒 **Reset with Long-Press** (5 seconds)

---

## 🛠️ Components Required

* ESP32
* Ultrasonic Sensor (HC-SR04)
* OLED Display (SSD1306)
* Buzzer (Active-Low)
* Red LED (Active-Low)
* Green LED (Active-Low)
* SOS Push Button (pull-down config)
* Jumper wires and breadboard

---

## ⚙️ Hardware Setup

### Pin Mapping

| Component       | ESP32 Pin |
| --------------- | --------- |
| Ultrasonic TRIG | GPIO 15   |
| Ultrasonic ECHO | GPIO 13   |
| Red LED         | GPIO 12   |
| Green LED       | GPIO 14   |
| Buzzer          | GPIO 27   |
| SOS Button      | GPIO 3    |
| OLED SDA        | GPIO 21   |
| OLED SCL        | GPIO 22   |

> 🔧 **Notes**:
>
> * RED & GREEN LEDs and the buzzer are **Active-Low** (LOW = ON).
> * SOS Button is **pulled down** and connected to **Vcc** to trigger interrupt.

---

## 📜 Code Explanation

### Key Highlights

* **Non-blocking architecture** using `Ticker` for blink & repeat logic.
* **Interrupt-based SOS activation** with long-press detection for system reset.
* **Prevention of re-triggering** and spam via `debounce` and state flags.
* **Timer starts** only when a person is detected.
* **OLED feedback** showing time elapsed.
* **SOS disables all sensors** and only resumes after reset.
* **Repeat Telegram alert every 4 seconds** (configurable).

---

## 📚 Required Libraries

* [`NewPing`](https://github.com/dnickless/NewPing)
* [`Adafruit_SSD1306`](https://github.com/adafruit/Adafruit_SSD1306)
* [`Ticker`](https://github.com/espressif/arduino-esp32)
* Built-in: `WiFi.h`, `HTTPClient.h`, `Wire.h`

---

## 🚀 Setup Instructions

### 1. Clone the Repository

```bash
git clone https://github.com/dibyasn/Arduino_Projects.git
cd Arduino_Projects/Child_Safety_System/
```

### 2. Configure Wi-Fi and Telegram

| Setting   | Value                                                                      |
| --------- | -------------------------------------------------------------------------- |
| SSID      | `Hotspot`                                                                  |
| Password  | `12345678`                                                                 |
| Bot Token | From [@BotFather](https://t.me/botfather)                                  |
| Chat ID   | From [`getUpdates`](https://api.telegram.org/bot<YourBotToken>/getUpdates) |

> 💡 Test your bot using:
> `https://api.telegram.org/bot<YourToken>/sendMessage?chat_id=<YourID>&text=Hello`

### 3. Wiring

Connect all modules as per the **Pin Mapping** above.

### 4. Upload Code

* Open the `.ino` file in **Arduino IDE**
* Board: `ESP32 Dev Module`
* COM Port: Detected ESP32 port
* Hit **Upload**

---

## 🚀 Usage Instructions

### 1. System Initialization

* Connects to Wi-Fi
* Initializes OLED and all components
* Displays: `"Available"` once ready

### 2. Presence Detection

* Uses Ultrasonic sensor to detect entry (`≤ 12 cm`)
* Starts timer
* OLED shows `"Occupied from MM:SS"`

### 3. Timeout Alert

* If presence time exceeds set limit (e.g., `10 seconds`), system:

  * Sends **Telegram alert**
  * OLED: `"Time Limit Exceeded"`
  * Blinks **RED LED**
  * Triggers **buzzer pattern**

### 4. SOS Mode

* Triggered by pressing SOS button anytime
* Sends **repeating** Telegram messages every 4 seconds:

  * `🚨 SOS Button Pressed in Washroom!`
* OLED: `"SOS Activated"`
* **Disables ultrasonic checks**
* RED LED blinks & buzzer makes danger sound
* Ends only after **5-second long press**

### 5. Reset System

* Long press SOS button (5 sec) = reset
* Turns on GREEN LED
* Turns off RED LED and buzzer
* Sends: `✅ SOS Deactivated. Washroom Reset.`

### 6. OLED Displays

| Situation       | OLED Text                  |
| --------------- | -------------------------- |
| Wi-Fi Setup     | `Connecting to WiFi...`    |
| Wi-Fi OK        | `WiFi Connected`           |
| No one inside   | `Available`                |
| Person inside   | `Occupied from MM:SS`      |
| Timeout Alert   | `Time Limit Exceeded`      |
| SOS Active      | `SOS Activated`            |
| Reset Triggered | `System Reset. Available.` |

### 7. Telegram Notifications

| Event         | Message                                        |
| ------------- | ---------------------------------------------- |
| SOS Triggered | `🚨 SOS Button Pressed in Washroom!` (repeats) |
| Timeout Alert | `⚠️ Time Limit Exceeded in Washroom!`          |
| Reset Done    | `✅ SOS Deactivated. Washroom Reset.`           |

---

## 🔧 Troubleshooting

| Problem                     | Solution                              |
| --------------------------- | ------------------------------------- |
| OLED not working            | Check I2C wiring and address `0x3C`   |
| No Wi-Fi                    | Ensure SSID/password match            |
| Telegram message not sent   | Check bot token, chat ID and internet |
| SOS triggers too many times | Confirm debounce and long-press logic |
| Person not detected         | Adjust `distanceThreshold` in code    |

---

## 📦 Future Improvements

* Add motion-based entry detection
* Use real-time cloud monitoring
* Voice alarm using DFPlayer Mini
* Battery-powered with backup alerts

---

## 🙌 Acknowledgments

Gratitude to the open-source Arduino and Telegram communities for enabling real-time IoT safety solutions. Inspired by child safety needs in schools and homes.

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
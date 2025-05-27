# 📂 Arduino Projects

---

Welcome to the **Arduino Projects** repository! This repository contains a collection of Arduino-based projects, each designed to demonstrate various functionalities and applications of Arduino, ranging from games to automated systems. Each project folder includes source code, hardware setup instructions, and documentation to help you replicate, modify, or build upon the projects.

## 📝 Table of Contents

Here’s a list of the projects available in this repository:

- [📂 Arduino Projects](#-arduino-projects)
  - [📝 Table of Contents](#-table-of-contents)
  - [✨ Features](#-features)
  - [🚀 Getting Started](#-getting-started)
    - [Prerequisites](#prerequisites)
    - [Clone the Repository](#clone-the-repository)
  - [📦 Projects Overview](#-projects-overview)
    - [1. 🐍 Snake Game](#1--snake-game)
    - [2. Automated Watering System](#2-automated-watering-system)
    - [3. 🔧 Magic Switchboard](#3--magic-switchboard)
    - [4. Child Safety System](#4-child-safety-system)
    - [5. 7x5 NeoPixel Custom Display](#5-7x5-neopixel-custom-display)
  - [✨ Features Across Projects](#-features-across-projects)
  - [🔧 Troubleshooting](#-troubleshooting)
  - [🙌 Acknowledgments](#-acknowledgments)

> 📌 **Note**: Each project folder contains a `README.md` file with detailed instructions and explanations specific to that project.

## ✨ Features

- A growing repository of Arduino projects showcasing different components and use cases like sensors, automation, and gaming.
- Well-documented instructions for easy setup and replication.
- Regular updates with new projects and improvements to existing ones.

## 🚀 Getting Started

To start working with any of the projects, navigate to the respective project folder in the table of contents. Each project contains detailed hardware connections, code, and setup instructions.

### Prerequisites

To work on these projects, ensure you have the following:

- **Arduino Uno or any compatible Arduino board**
- **Arduino IDE**: [Download here](https://www.arduino.cc/en/software)
- Required hardware components specific to each project (listed in the respective project folders).

### Clone the Repository

You can clone this repository to your local machine by running the following commands in your terminal:

```bash
git clone https://github.com/dibyasn/Arduino_Projects.git
cd Arduino_Projects
```

## 📦 Projects Overview

### 1. 🐍 Snake Game

- **Description**: A classic Snake Game implemented using an OLED display and a joystick. Control the snake to collect food while avoiding collisions with the walls or itself.
- **Features**:
  - Joystick control for game navigation
  - OLED display (0.96") for game visuals
  - Incremental difficulty as the snake grows
- [View Project Files](./🐍Snake_Game/README.md)

### 2. Automated Watering System

- **Description**: A smart irrigation system that automatically waters plants based on soil moisture levels. This project uses sensors to monitor soil moisture and controls a water pump via a relay to water plants when necessary.

- **Features**:
  - Soil moisture sensor for monitoring water levels
  - Water pump controlled via a relay module
  - Audio feedback using DFPlayer Mini for notifications
  - OLED display animations for visual feedback (crying face for dry soil, smiling face for well-watered plants)
- [View Project Files](./Automated_Watering_System/README.md)

### 3. 🔧 Magic Switchboard

- **Description**: A fascinating switchboard puzzle that involves swapping positions of switches and light caps while maintaining the rule that a switch always controls its corresponding light.
- **Features**:
  - Dynamic assignment of switches to LEDs
  - Visual feedback with LEDs
  - A fun and interactive puzzle experience
- [View Project Files](./Magic_Switchboard/README.MD)

### 4. Child Safety System

- **Description**: A system designed to enhance child safety in washrooms using an SOS button, timer-based alerts, and an ultrasonic sensor for monitoring occupancy.
- **Features**:
  - SOS button for emergency alerts
  - Timer to detect prolonged occupancy
  - Ultrasonic sensor for real-time presence detection
  - Visual and audio alerts for notifications
- [View Project Files](./Child_Safety_System/readme.md)
  
### 5. 7x5 NeoPixel Custom Display

- **Description**: Web-controlled 35-LED matrix display (7x5 grid) powered by ESP32, offering interactive visualization and pattern creation capabilities.
- **Features**:
  - Web-based control interface
  - Digital number display (0-9)
  - Alphabet display (A-Z)
  - Interactive drawing mode
  - Real-time color and brightness control
- [View Project Files](./7x5_NeoPixel_CustomDisplay/readme.md)

## ✨ Features Across Projects

Each project is designed with clear code structure and easy-to-understand instructions. Common features include:

- **Interactive Controls**: 
  - Joystick controls for gaming applications
  - Web-based interfaces for remote control
  - Push-button interactions for user input

- **Display Technologies**:
  - OLED displays for visual feedback and gaming
  - LED matrices and NeoPixel arrays
  - Custom 7x5 display configurations

- **Sensing & Automation**:
  - Soil moisture monitoring
  - Ultrasonic distance sensing
  - Timer-based monitoring systems

- **Feedback Mechanisms**:
  - Audio feedback using DFPlayer Mini
  - Visual feedback through LEDs and displays
  - Real-time status indicators

- **Safety Features**:
  - Emergency SOS systems
  - Automated monitoring
  - Alert mechanisms for critical situations

- **Connectivity**:
  - ESP32-based web connectivity
  - Real-time control interfaces
  - Remote monitoring capabilities

## 🔧 Troubleshooting

If you encounter any issues while replicating the projects, you can refer to the troubleshooting sections in the individual project folders. Additionally, feel free to open an issue in this repository for support.

## 🙌 Acknowledgments

This repository is a result of continuous learning and experimentation with Arduino and its vast ecosystem of sensors, modules, and controllers. I would like to express my gratitude to the incredible Arduino community, whose shared knowledge and open-source contributions have been an invaluable resource. A special thanks to the creators of the libraries and tools used across the projects, making innovation accessible to everyone.

---

<p align="center">
    <img src="https://64.media.tumblr.com/tumblr_lp0f2fIhnF1qa2ip8o1_1280.gif" alt="Thank You">
</p>

---

For any questions or suggestions, feel free to open an issue or contact us directly.

<p align="center">
    <a href="https://github.com/dibyasn"><img src="https://img.icons8.com/color/48/000000/github.png" alt="Contribute Icon"></a>
</p>
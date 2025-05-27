# 7x5 NeoPixel Custom Display

<p align="center">
    <img src="./assets/display_demo.gif" alt="NeoPixel Display Demo" style="width:40%; max-width:600px;">
</p>

An elegant web-controlled LED matrix display that brings your pixels to life with customizable text, numbers, and interactive drawing capabilities.

## Table of Contents

- [7x5 NeoPixel Custom Display](#7x5-neopixel-custom-display)
  - [Table of Contents](#table-of-contents)
  - [📖 Introduction](#-introduction)
  - [🔧 Components](#-components)
  - [🔌 Circuit Diagram](#-circuit-diagram)
  - [🚀 Setup Instructions](#-setup-instructions)
  - [💡 Code Explanation](#-code-explanation)
    - [Key Features:](#key-features)
    - [Font System:](#font-system)
  - [📜 Additional Documentation](#-additional-documentation)
  - [🖥️ Usage](#️-usage)
    - [Web Interface Overview](#web-interface-overview)
    - [Interface Modes](#interface-modes)
    - [Interactive Drawing Mode](#interactive-drawing-mode)
    - [Color and Brightness Controls](#color-and-brightness-controls)
  - [🎉 Acknowledgments](#-acknowledgments)

## 📖 Introduction

The ESP32 7x5 NeoPixel Custom Display project creates a versatile LED matrix display powered by an ESP32 microcontroller. It features a responsive web interface for real-time control and supports multiple display modes including letters, numbers, and interactive drawing.

## 🔧 Components

- **ESP32 Development Board**
- **5x NeoPixel LED Strips** (7 LEDs each)
- **5V Power Supply**
- **Jumper Wires**
- **Optional Components:**
  - 330-470Ω resistor
  - 1000µF capacitor (6.3V or higher)

## 🔌 Circuit Diagram

<p align="center">
    <img src="./assets/circuit_diagram.png" alt="Circuit Diagram" style="max-width:60%;">
</p>

| Strip (Column) | GPIO Pin | Description |
|---------------|----------|-------------|
| 1 (Right)     | GPIO 22  | Rightmost column |
| 2             | GPIO 17  | Second column |
| 3             | GPIO 23  | Middle column |
| 4             | GPIO 19  | Fourth column |
| 5 (Left)      | GPIO 26  | Leftmost column |

## 🚀 Setup Instructions

1. **Install Required Libraries**
   ```bash
   # In Arduino IDE, install:
   - Adafruit NeoPixel
   - ESP32 Board Package
   ```

2. **Configure WiFi Settings**
   ```cpp
   const char* ssid = "NeoPixel_Display";
   const char* password = "12345678";
   ```

3. **Hardware Assembly**
   - Connect NeoPixel strips to corresponding GPIO pins
   - Ensure proper power distribution
   - Add optional resistor on data lines
   - Include capacitor across power lines if needed

4. **Upload Code**
   - Select ESP32 board in Arduino IDE
   - Choose correct port
   - Upload sketch

## 💡 Code Explanation

### Key Features:

```cpp
// Display Modes
enum DisplayMode {
    OFF,        // All LEDs off
    DIGITS,     // Cycle through 0-9
    LETTERS,    // Cycle through A-Z
    DRAW        // Interactive drawing
};
```

### Font System:
```cpp
// 5x7 Font Pattern Example
const uint8_t font5x7[][5] = {
    {0x7C,0x12,0x11,0x12,0x7C}, // A
    {0x7F,0x49,0x49,0x49,0x36}, // B
    // ...other letters
};
```

## 📜 Additional Documentation

- [Source Code](./ESP32_7x5_NeoPixel_CustomDisplay/ESP32_7x5_NeoPixel_CustomDisplay.ino)

- **Web Interface Features:**
  - Mode selection
  - Color picker
  - Brightness control
  - Interactive grid
  - Clear function

- **Technical Specifications:**
  - Resolution: 5x7 pixels
  - Communication: WiFi (AP mode)
  - Protocol: WS2812B
  - Server: ESP32 built-in
  - Interface: HTML/CSS/JS

## 🖥️ Usage

### Web Interface Overview

<p align="center">
    <img src="./assets/ui_overview.png" alt="Web Interface Overview" style="width:60%; max-width:600px;">
</p>

1. **Power up the ESP32**
2. **Connect to WiFi:**
   - Network: `NeoPixel_Display`
   - Password: `12345678`

### Interface Modes

<p align="center">
    <img src="./assets/display_modes.png" alt="Display Modes" style="width:60%; max-width:600px;">
</p>

3. **Access Interface:**
   - Open browser
   - Navigate to ESP32's IP
4. **Control Display:**
   - Select display mode
   - Choose colors
   - Adjust brightness
   - Create patterns

### Interactive Drawing Mode

<p align="center">
    <img src="./assets/drawing_mode.png" alt="Drawing Mode Interface" style="width:60%; max-width:600px;">
</p>

### Color and Brightness Controls

<p align="center">
    <img src="./assets/controls.png" alt="Color and Brightness Controls" style="width:60%; max-width:600px;">
</p>

## 🎉 Acknowledgments

This project beautifully merges web technology with LED display capabilities, creating an interactive platform for learning and creativity. It serves as a bridge between software and hardware, making it an excellent educational tool for understanding:

- Digital display systems
- Web-based device control
- LED matrix programming
- Interactive user interfaces

---

<p align="center">
    <img src="https://64.media.tumblr.com/tumblr_lp0f2fIhnF1qa2ip8o1_1280.gif" alt="Thank You">
</p>

---

Feel free to contribute, report issues, or suggest enhancements. Happy coding! 🚀

<p align="center">
    <a href="https://github.com/dibyasn"><img src="https://img.icons8.com/color/48/000000/github.png" alt="Contribute Icon"></a>
</p>
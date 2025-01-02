# Snake Game on OLED Display with Arduino 🎮

Welcome to the Snake Game project! This project brings the classic Snake game to life using an Arduino microcontroller and an OLED display.

## Table of Contents
- [Snake Game on OLED Display with Arduino 🎮](#snake-game-on-oled-display-with-arduino-)
  - [Table of Contents](#table-of-contents)
  - [📖 Introduction](#-introduction)
  - [🔧 Components](#-components)
  - [🔌 Circuit Diagram](#-circuit-diagram)
    - [Connections:](#connections)
      - [OLED Display:](#oled-display)
      - [Joystick:](#joystick)
      - [Buzzer:](#buzzer)
  - [🚀 Setup Instructions](#-setup-instructions)
    - [1. Clone the Repository](#1-clone-the-repository)
    - [2. Install Required Libraries](#2-install-required-libraries)
    - [3. Assemble the Circuit](#3-assemble-the-circuit)
    - [4. Upload the Code](#4-upload-the-code)
  - [💡 Code Explanation](#-code-explanation)
    - [Key Features of the Code:](#key-features-of-the-code)
    - [Example Code Snippet:](#example-code-snippet)
      - [Snake Movement Logic](#snake-movement-logic)
      - [Joystick Input Handling](#joystick-input-handling)
  - [🖥️ Usage](#️-usage)
  - [🎉 Acknowledgments](#-acknowledgments)

## 📖 Introduction
The Snake Game is a timeless classic that challenges players to navigate a growing snake while avoiding collisions. In this project, the snake moves across an OLED display, and its direction is controlled using a joystick module.

## 🔧 Components
- **Arduino Uno/Nano/ESP32**
- **0.96" OLED Display** (SSD1306)
- **Joystick Module**
- **Buzzer**
- **Jumper Wires**
- **Breadboard**

## 🔌 Circuit Diagram

### Connections:
#### OLED Display:
```plaintext
  OLED Display       Arduino
  ------------       -------
  VCC  ------------> 5V
  GND  ------------> GND
  SDA  ------------> A4 (ESP32: GPIO21)
  SCL  ------------> A5 (ESP32: GPIO22)
```

#### Joystick:
```plaintext
  Joystick           Arduino
  -----------        -------
  VRX  ------------> A0 (ESP32: GPIO33)
  VRY  ------------> A1 (ESP32: GPIO32)
  SW   ------------> D2
  VCC  ------------> 5V
  GND  ------------> GND
```

#### Buzzer:
```plaintext
  Buzzer             Arduino
  --------           -------
  +     ------------> D3
  -     ------------> GND
```

## 🚀 Setup Instructions

### 1. Clone the Repository
```bash
git clone https://github.com/dibyasn/Arduino_Projects.git
cd Arduino_Projects/🐍Snake_Game
```

### 2. Install Required Libraries
Ensure you have the following libraries installed in your Arduino IDE:
- **Adafruit GFX Library** 🌐
- **Adafruit SSD1306 Library** 🌐

### 3. Assemble the Circuit
Use the circuit diagram above to connect the OLED display, joystick module, and buzzer to the Arduino.

### 4. Upload the Code
1. Open the Arduino IDE.
2. Select the correct **Board** and **Port**.
3. Upload the provided Snake Game sketch from the repository.

## 💡 Code Explanation

### Key Features of the Code:
- **Game Logic**: The snake grows when it "eats" food, and the game ends if the snake collides with itself.
- **Joystick Control**: The snake's direction is updated based on joystick inputs.
- **OLED Display Animation**: The SSD1306 driver manages the display updates for smooth game visuals.

### Example Code Snippet:
#### Snake Movement Logic
```cpp
for (int i = snake_length - 1; i > 0; i--) {
  snake_x[i] = snake_x[i - 1];
  snake_y[i] = snake_y[i - 1];
}
switch (snake_dir) {
  case 0: snake_x[0]++; break; // Right
  case 1: snake_y[0]--; break; // Up
  case 2: snake_x[0]--; break; // Left
  case 3: snake_y[0]++; break; // Down
}
```

#### Joystick Input Handling
```cpp
int xVal = analogRead(JOYSTICK_X);
int yVal = analogRead(JOYSTICK_Y);
if (snake_dir == 0 || snake_dir == 2) {
  if (yVal < (1850 - deadZone) && snake_dir != 3) snake_dir = 1; // Up
  else if (yVal > (1850 + deadZone) && snake_dir != 1) snake_dir = 3; // Down
} else if (snake_dir == 1 || snake_dir == 3) {
  if (xVal < (1850 - deadZone) && snake_dir != 0) snake_dir = 2; // Left
  else if (xVal > (2150 + deadZone) && snake_dir != 2) snake_dir = 0; // Right
}
```

## 🖥️ Usage
1. Power on the Arduino.
2. Use the joystick to control the snake:
   - Move the joystick up, down, left, or right to navigate the snake.
3. Try to "eat" the food dots that appear on the OLED display.
4. Avoid colliding with the snake's body to keep playing.

## 🎉 Acknowledgments
This project is inspired by the classic Snake Game and utilizes the Arduino platform's versatility. Special thanks to the Arduino and open-source communities for their amazing contributions.

<p align="center">
    <img src="https://64.media.tumblr.com/tumblr_lp0f2fIhnF1qa2ip8o1_1280.gif" alt="Thank You">
</p>

---

Feel free to contribute, report issues, or suggest enhancements. Happy coding! 🚀

<p align="center">
    <a href="https://github.com/dibyasn/Analog_clock"><img src="https://img.icons8.com/color/48/000000/github.png" alt="Contribute Icon"></a>
</p>
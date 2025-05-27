/*
  Project: ESP32 7x5 NeoPixel Custom Display (v1.4)
  Author: [Your Name or GitHub Username]
  Version: 1.4
  Features: Web-controlled LED matrix with font and custom draw support

  ------------------------ About Project ------------------------
  This project uses an ESP32 microcontroller to control a 5-column by 7-row NeoPixel matrix. 
  It allows users to display letters, digits, or create custom patterns on a 7x5 LED display.
  The ESP32 serves a web interface over Wi-Fi in Access Point mode, allowing users to control 
  the LED matrix from a browser on any connected device.

  ------------------------ Hardware Used ------------------------
  - ESP32 development board
  - 5 NeoPixel LED strips (1 per column), each with 7 LEDs
  - Power supply (5V capable of handling all NeoPixels)
  - Optional: resistor (330–470 ohm) between ESP32 and data line
  - Optional: capacitor (1000 µF, 6.3V or higher) across power lines

  ------------------------ Connections ------------------------
  - NeoPixel Data Pins:
      Strip 1 (rightmost column): GPIO 22
      Strip 2: GPIO 17
      Strip 3: GPIO 23
      Strip 4: GPIO 19
      Strip 5 (leftmost column): GPIO 26
  - All NeoPixel power (5V) and ground lines connected appropriately
  - Make sure NeoPixels share ground with ESP32

  ------------------------ Working / Modes ------------------------
  - OFF: Turns off all LEDs
  - DIGITS: Displays numeric digits (0–9)
  - LETTERS: Displays predefined 5x7 font letters (A–Z)
  - DRAW: Enables interactive pixel grid where users can toggle LEDs manually

  ------------------------ Web Interface ------------------------
  - Hosted by ESP32 in AP mode ("NeoPixel_Display", password "12345678")    
  - Accessible from any mobile or desktop browser
  - Allows mode switching, color selection, brightness adjustment, and custom drawing
  - Intuitive UI with CSS-styled layout and grid interaction

  ------------------------ Version 1.4 Updates ------------------------
  - Added font support for 5x7 letters (A-Z)
  - Enhanced draw mode with interactive toggling
*/
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_NeoPixel.h>

//------------------------- Hardware Configuration -------------------------
#define NUM_LEDS   7  // Rows per strip
#define NUM_STRIPS 5  // Number of columns
const int dataPins[NUM_STRIPS] = {22, 17, 23, 19, 26};

// Reverse-mapped for correct display orientation
Adafruit_NeoPixel strips[NUM_STRIPS] = {
  Adafruit_NeoPixel(NUM_LEDS, dataPins[4], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_LEDS, dataPins[3], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_LEDS, dataPins[2], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_LEDS, dataPins[1], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_LEDS, dataPins[0], NEO_GRB + NEO_KHZ800)
};

// ------------------------- Access Point Configuration -------------------------
const char* ssid = "NeoPixel_Display";
const char* password = "12345678";

WebServer server(80);

// ------------------------- State Variables -------------------------
String mode = "OFF";  // OFF / DIGITS / DRAW / LETTERS
uint32_t drawColor = Adafruit_NeoPixel::Color(255, 100, 0);
uint8_t brightness = 50;
bool gridState[NUM_LEDS][NUM_STRIPS] = {false};

// ------------------------- Font Pattern (5x7) -------------------------
// Each letter is represented as 5 columns (bytes), 7 bits each
const uint8_t font5x7[][5] = {
  {0x7C,0x12,0x11,0x12,0x7C}, // A
  {0x7F,0x49,0x49,0x49,0x36}, // B
  {0x3E,0x41,0x41,0x41,0x22}, // C
  {0x7F,0x41,0x41,0x22,0x1C}, // D
  {0x7F,0x49,0x49,0x49,0x41}, // E
  {0x7F,0x09,0x09,0x09,0x01}, // F
  {0x3E,0x41,0x49,0x49,0x7A}, // G
  {0x7F,0x08,0x08,0x08,0x7F}, // H
  {0x00,0x41,0x7F,0x41,0x00}, // I
  {0x20,0x40,0x41,0x3F,0x01}, // J
  {0x7F,0x08,0x14,0x22,0x41}, // K
  {0x7F,0x40,0x40,0x40,0x40}, // L
  {0x7F,0x02,0x0C,0x02,0x7F}, // M
  {0x7F,0x04,0x08,0x10,0x7F}, // N
  {0x3E,0x41,0x41,0x41,0x3E}, // O
  {0x7F,0x09,0x09,0x09,0x06}, // P
  {0x3E,0x41,0x51,0x21,0x5E}, // Q
  {0x7F,0x09,0x19,0x29,0x46}, // R
  {0x46,0x49,0x49,0x49,0x31}, // S
  {0x01,0x01,0x7F,0x01,0x01}, // T
  {0x3F,0x40,0x40,0x40,0x3F}, // U
  {0x1F,0x20,0x40,0x20,0x1F}, // V
  {0x7F,0x20,0x18,0x20,0x7F}, // W
  {0x63,0x14,0x08,0x14,0x63}, // X
  {0x07,0x08,0x70,0x08,0x07}, // Y
  {0x61,0x51,0x49,0x45,0x43}  // Z
};

// ------------------------- Digit Pattern -------------------------
// Each number is stored as a 7-row character using '.' and '#' for off/on
const char* digits[10][NUM_LEDS] = {
  {
    ".###.",
    "#...#",
    "#..##",
    "#.#.#",
    "##..#",
    "#...#",
    ".###."
  },
  {
    "..#..",
    ".##..",
    "#.#..",
    "..#..",
    "..#..",
    "..#..",
    "#####"
  },
  {
    ".###.",
    "#...#",
    "...#.",
    "..#..",
    ".#...",
    "#....",
    "#####"
  },
  {
    "####.",
    "....#",
    "....#",
    ".###.",
    "....#",
    "....#",
    "####."
  },
  {
    "...#.",
    "..##.",
    ".#.#.",
    "#..#.",
    "#####",
    "...#.",
    "...#."
  },
  {
    "#####",
    "#....",
    "#....",
    ".###.",
    "....#",
    "....#",
    "####."
  },
  {
    ".###.",
    "#....",
    "#....",
    "#####",
    "#...#",
    "#...#",
    ".###."
  },
  {
    "#####",
    "....#",
    "...#.",
    "..#..",
    ".#...",
    ".#...",
    ".#..."
  },
  {
    ".###.",
    "#...#",
    "#...#",
    ".###.",
    "#...#",
    "#...#",
    ".###."
  },
  {
    ".###.",
    "#...#",
    "#...#",
    ".####",
    "....#",
    "....#",
    ".###."
  }
};

// ------------------------- Functions -------------------------
void displayDigit(int digit) {
  for (int col = 0; col < NUM_STRIPS; col++) {
    for (int row = 0; row < NUM_LEDS; row++) {
      char pixel = digits[digit][row][col];
      uint32_t color = (pixel == '#') ? drawColor : 0;
      strips[col].setPixelColor(row, color);
    }
    strips[col].setBrightness(brightness);
    strips[col].show();
  }
}

void displayLetter(int letterIndex) {
  for (int col = 0; col < NUM_STRIPS; col++) {
    for (int row = 0; row < NUM_LEDS; row++) {
      uint8_t fontByte = font5x7[letterIndex][col];
      bool pixelOn = (fontByte >> row) & 1;
      uint32_t color = pixelOn ? drawColor : 0;
      strips[col].setPixelColor(row, color);
    }
    strips[col].setBrightness(brightness);
    strips[col].show();
  }
}

void displayGrid() {
  for (int col = 0; col < NUM_STRIPS; col++) {
    for (int row = 0; row < NUM_LEDS; row++) {
      uint32_t color = gridState[row][col] ? drawColor : 0;
      strips[col].setPixelColor(row, color);
    }
    strips[col].setBrightness(brightness);
    strips[col].show();
  }
}


// ------------------------- Web Page -------------------------
const char* pageHTML = R"rawliteral(
  <!DOCTYPE html>
<html>
<head>
  <title>NeoPixel LED Controller</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body {
      font-family: Arial, sans-serif;
      margin: 0; padding: 0;
      background-color: #f4f4f4;
      text-align: center;
    }
    header {
      background-color: #333;
      color: white;
      padding: 12px 0;
      position: sticky;
      top: 0;
      z-index: 1000;
    }
    header h2 {
      margin: 0;
      font-weight: normal;
      font-size: 1.5em;
    }
    .controls {
      background: white;
      padding: 15px 10px;
      box-shadow: 0 2px 5px rgba(0,0,0,0.1);
      max-width: 480px;
      margin: 10px auto;
      border-radius: 8px;
    }
    .control-row {
      display: flex;
      align-items: center;
      justify-content: center;
      flex-wrap: wrap;
      margin: 10px 0;
      gap: 15px;
    }
    label {
      font-size: 1em;
      margin-right: 8px;
      min-width: 60px;
      text-align: right;
    }
    select, input[type=color], input[type=range], button {
      font-size: 1em;
      padding: 8px 10px;
      border-radius: 5px;
      border: 1px solid #ccc;
      outline: none;
      cursor: pointer;
      flex-shrink: 0;
    }
    select {
      min-width: 120px;
    }
    input[type=color] {
      width: 50px;
      height: 40px;
      padding: 0;
      border: none;
      cursor: pointer;
    }
    input[type=range] {
      width: 180px;
      cursor: pointer;
      -webkit-appearance: none;
      appearance: none;
      height: 8px;
      background: #ddd;
      border-radius: 4px;
      padding: 0;
    }
    
    /* Webkit browsers (Chrome, Safari, Edge) */
    input[type=range]::-webkit-slider-thumb {
      -webkit-appearance: none;
      appearance: none;
      width: 20px;
      height: 20px;
      background: #ff6400;
      border-radius: 50%;
      cursor: pointer;
      border: 2px solid white;
      box-shadow: 0 2px 4px rgba(0,0,0,0.2);
    }
    
    input[type=range]::-webkit-slider-thumb:hover {
      background: #e05500;
    }
    
    /* Firefox */
    input[type=range]::-moz-range-thumb {
      width: 20px;
      height: 20px;
      background: #ff6400;
      border-radius: 50%;
      cursor: pointer;
      border: 2px solid white;
      box-shadow: 0 2px 4px rgba(0,0,0,0.2);
    }
    
    input[type=range]::-moz-range-thumb:hover {
      background: #e05500;
    }
    
    input[type=range]::-moz-range-track {
      height: 8px;
      background: #ddd;
      border-radius: 4px;
      border: none;
    }
    
    .brightness-container {
      display: flex;
      align-items: center;
      gap: 10px;
    }
    
    .brightness-value {
      min-width: 35px;
      font-weight: bold;
      color: #333;
    }
    
    button {
      background-color: #ff6400;
      color: white;
      border: none;
      min-width: 100px;
      transition: background-color 0.3s;
    }
    button:hover {
      background-color: #e05500;
    }
    .grid-container {
      max-width: 320px;
      margin: 0 auto 20px auto;
      padding: 10px;
      background: white;
      border-radius: 8px;
      box-shadow: 0 2px 5px rgba(0,0,0,0.1);
      display: none;
    }
    .letter-container {
      max-width: 320px;
      margin: 0 auto 20px auto;
      padding: 10px;
      background: white;
      border-radius: 8px;
      box-shadow: 0 2px 5px rgba(0,0,0,0.1);
      display: none;
    }
    .grid {
      display: grid;
      grid-template-columns: repeat(5, 1fr);
      gap: 6px;
    }
    .cell {
      position: relative;
      width: 100%;
      padding-top: 100%; /* square */
      background-color: #222;
      border-radius: 5px;
      border: 1.5px solid #444;
      cursor: pointer;
      transition: background-color 0.3s;
    }
    .cell.active {
      background-color: var(--active-color, #ff6400);
      border-color: var(--active-color, #ff6400);
    }
    .cell-inner {
      position: absolute;
      top: 0; left: 0; right: 0; bottom: 0;
    }
    @media (max-width: 480px) {
      .controls {
        max-width: 95vw;
        padding: 10px;
        margin: 5px auto;
      }
      .control-row {
        margin: 8px 0;
        gap: 10px;
      }
      .control-row:first-child {
        flex-direction: row;
        justify-content: center;
      }
      .control-row:nth-child(2) {
        flex-direction: column;
        gap: 15px;
      }
      .control-row:nth-child(2) > div {
        display: flex;
        align-items: center;
        justify-content: space-between;
        gap: 10px;
      }
      label {
        text-align: left;
        min-width: auto;
        margin-right: 10px;
        flex-shrink: 0;
      }
      select {
        min-width: 100px;
        flex: 1;
      }
      input[type=color] {
        width: 40px;
        height: 35px;
        flex-shrink: 0;
      }
      .brightness-container {
        flex: 1;
      }
      input[type=range] {
        flex: 1;
        min-width: 120px;
      }
      .brightness-value {
        min-width: 30px;
        font-size: 0.9em;
      }
      button {
        width: 100%;
        padding: 12px;
        font-size: 1.1em;
      }
      .grid-container, .letter-container {
        max-width: 280px;
        padding: 8px;
        margin: 10px auto;
      }
      .grid {
        gap: 4px;
      }
      .cell {
        border-radius: 3px;
        border-width: 1px;
      }
    }
  </style>
</head>
<body>
  <header>
    <h2>NeoPixel LED Controller</h2>
  </header>
  <div class="controls">
    <div class="control-row">
      <label for="mode">Mode:</label>
      <select id="mode" onchange="setMode(this.value)">
        <option>OFF</option>
        <option>DIGITS</option>
        <option>DRAW</option>
        <option>LETTERS</option>
      </select>
    </div>
    <div class="control-row" style="justify-content:center; gap:20px;">
      <div style="display:flex; align-items:center; gap:10px;">
        <label for="colorPicker">Color:</label>
        <input type="color" id="colorPicker" value="#ff6400" onchange="updateColor()">
      </div>
      <div class="brightness-container">
        <label for="brightness">Brightness:</label>
        <input type="range" id="brightness" min="0" max="255" step="1" value="50" oninput="updateBrightness()">
        <span class="brightness-value" id="brightnessValue">50</span>
      </div>
    </div>
    <div class="control-row">
      <button onclick="clearGrid()">Clear Grid</button>
    </div>
  </div>
  
  <div id="gridContainer" class="grid-container">
    <div class="grid" id="grid"></div>
  </div>
  
  <div id="digitContainer" class="letter-container">
  <p style="margin: 10px 0; color: #666; font-size: 0.9em;">
    Digits will cycle automatically 0 -> 1 -> 2 -> ... -> 9
  </p>
  </div>

  <div id="letterContainer" class="letter-container">
    <p style="margin: 10px 0; color: #666; font-size: 0.9em;">
      Letters will cycle automatically A -> B -> C -> ... -> Z
    </p>
  </div>

  <script>
    const gridEl = document.getElementById("grid");
    const gridContainer = document.getElementById("gridContainer");
    const letterContainer = document.getElementById("letterContainer");
    const gridState = Array.from({length: 7}, () => Array(5).fill(false));
    let currentColor = "#ff6400";

    function createGrid() {
      gridEl.innerHTML = "";
      for (let row = 0; row < 7; row++) {
        for (let col = 0; col < 5; col++) {
          const cell = document.createElement("div");
          cell.className = "cell";
          cell.dataset.row = row;
          cell.dataset.col = col;
          cell.onclick = () => toggleCell(cell, row, col);
          const inner = document.createElement("div");
          inner.className = "cell-inner";
          cell.appendChild(inner);
          gridEl.appendChild(cell);
        }
      }
    }

    function toggleCell(cell, row, col) {
      gridState[row][col] = !gridState[row][col];
      cell.classList.toggle("active");
      cell.style.setProperty("--active-color", currentColor);
      sendGrid();
    }

    function setMode(val) {
      fetch(`/mode?value=${val}`);
      if (val === "DRAW") {
        gridContainer.style.display = "block";
        letterContainer.style.display = "none";
        digitContainer.style.display = "none";
      } else if (val === "DIGITS") {
        gridContainer.style.display = "none";
        letterContainer.style.display = "none";
        digitContainer.style.display = "block";
      } else if (val === "LETTERS") {
        gridContainer.style.display = "none";
        digitContainer.style.display = "none";
        letterContainer.style.display = "block";
      } else {
        gridContainer.style.display = "none";
        letterContainer.style.display = "none";
        digitContainer.style.display = "none";
      }
    }

    function setLetter(val) {
      fetch(`/letter?value=${val}`);
    }

    function updateColor() {
      currentColor = document.getElementById("colorPicker").value;
      document.querySelectorAll(".cell.active").forEach(c => {
        c.style.setProperty("--active-color", currentColor);
      });
      fetch(`/color?value=${currentColor.substring(1)}`);
      sendGrid();
    }

    function updateBrightness() {
      const val = document.getElementById("brightness").value;
      document.getElementById("brightnessValue").textContent = val;
      fetch(`/brightness?value=${val}`);
    }

    function clearGrid() {
      document.querySelectorAll(".cell").forEach(c => c.classList.remove("active"));
      for (let row = 0; row < 7; row++) {
        for (let col = 0; col < 5; col++) {
          gridState[row][col] = false;
        }
      }
      sendGrid();
    }

    function sendGrid() {
      const flat = gridState.flat().map(v => v ? 1 : 0).join("");
      fetch(`/grid?value=${flat}`);
    }

    // Initialize
    createGrid();
    setMode('OFF'); // default to OFF mode
  </script>
</body>
</html>
)rawliteral";

// ------------------------- Server Handlers -------------------------

void handleRoot() {
  server.send(200, "text/html", pageHTML);
}

void handleMode() {
  if (server.hasArg("value")) {
    mode = server.arg("value");
    if (mode == "OFF") {
      for (int i = 0; i < NUM_STRIPS; i++) {
        strips[i].clear();
        strips[i].show();
      }
    }
  }
  server.send(200, "text/plain", "OK");
}

void handleColor() {
  if (server.hasArg("value")) {
    String hex = server.arg("value");
    if (hex.length() == 6) {
      long number = strtol(hex.c_str(), NULL, 16);
      uint8_t r = (number >> 16) & 0xFF;
      uint8_t g = (number >> 8) & 0xFF;
      uint8_t b = number & 0xFF;
      drawColor = Adafruit_NeoPixel::Color(r, g, b);
    }
  }
  server.send(200, "text/plain", "OK");
}

void handleBrightness() {
  if (server.hasArg("value")) {
    int val = server.arg("value").toInt();
    brightness = constrain(val, 0, 255);
    for (int i = 0; i < NUM_STRIPS; i++) {
      strips[i].setBrightness(brightness);
      strips[i].show();
    }
  }
  server.send(200, "text/plain", "OK");
}

void handleGrid() {
  if (server.hasArg("value")) {
    String bits = server.arg("value");
    if (bits.length() == NUM_LEDS * NUM_STRIPS) {
      int idx = 0;
      for (int row = 0; row < NUM_LEDS; row++) {
        for (int col = 0; col < NUM_STRIPS; col++) {
          gridState[row][col] = (bits[idx++] == '1');
        }
      }
      displayGrid();
    }
  }
  server.send(200, "text/plain", "OK");
}

void handleLetter() {
  if (server.hasArg("value")) {
    String val = server.arg("value");
    if (val.length() == 1 && val[0] >= 'A' && val[0] <= 'Z') {
      int letterIndex = val[0] - 'A';
      displayLetter(letterIndex);
    }
  }
  server.send(200, "text/plain", "OK");
}

// ------------------------- Setup & Loop -------------------------
void setup() {
  Serial.begin(115200);

  for (int i = 0; i < NUM_STRIPS; i++) {
    strips[i].begin();
    strips[i].setBrightness(brightness);
    strips[i].clear();
    strips[i].show();
  }

  WiFi.softAP(ssid, password);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/mode", handleMode);
  server.on("/color", handleColor);
  server.on("/brightness", handleBrightness);
  server.on("/grid", handleGrid);
  server.on("/letter", handleLetter);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  if (mode == "DIGITS") {
    static unsigned long lastUpdate = 0;
    static int digit = 0;
    if (millis() - lastUpdate > 1000) {
      lastUpdate = millis();
      displayDigit(digit);
      digit = (digit + 1) % 10;
    }
  } else if (mode == "LETTERS") {
    static unsigned long lastUpdate = 0;
    static int letter = 0;
    if (millis() - lastUpdate > 1000) {
      lastUpdate = millis();
      displayLetter(letter);
      letter = (letter + 1) % 26;
    }
  } else if (mode == "DRAW") {
    displayGrid();
  }
}
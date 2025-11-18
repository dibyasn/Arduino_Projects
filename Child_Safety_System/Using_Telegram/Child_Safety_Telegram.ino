/*

  Author : Dibyaranjan
  Date: 31-July-2025

 Project Name: Child Safety Washroom System with SOS Button, Timer, and Telegram Alert
  -The Child Safety Washroom System is an IoT-based safety solution designed to ensure the well-being of children in washrooms.
  -It uses sensors to monitor occupancy, track the duration of stay, and respond to emergencies via an SOS button. 
  -The system includes visual and audio alerts and now features Telegram integration to notify caregivers in real-time if help is needed.

  Features
  ✅ Presence Detection: Using Ultrasonic Sensor
  ⏱ Time Monitoring: Triggers alert if user stays too long
  🆘 SOS Button: Allows user to manually request help
  🔒 Reset with Long-Press
  📲 Telegram Notifications: Sends alert messages to caregiver when an SOS or timeout occurs.
  💡 Visual Indicators: RED/GREEN LEDs to show occupancy.
  🔊 Buzzer Alert: indicate safety or emergency states.
  🖥 OLED Display: Shows real-time status and occupancy time.

*/

#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Ticker.h>
#include <WiFi.h>
#include <HTTPClient.h>

// === Pin Definitions ===
#define TRIG_PIN 15
#define ECHO_PIN 13
#define BUZZER_PIN 26
#define RED_LED_PIN 12
#define GREEN_LED_PIN 14
#define SOS_BUTTON_PIN 32
#define OLED_SDA 21
#define OLED_SCL 22

// === States ===
#define ACTIVE_STATE LOW
#define INACTIVE_STATE HIGH

// === Parameters ===
#define MAX_DISTANCE 200           // cm
#define DETECTION_THRESHOLD 12     // cm
#define TIME_LIMIT 10              // seconds
#define BLINK_INTERVAL 0.5         // seconds
#define SOS_REPEAT_INTERVAL_SEC 4  // ⏲️ Telegram repeat delay (in sec)
#define SOS_HOLD_TIME_MS 5000      // ⏲️ Button hold time to reset (in ms)

// === WiFi Credentials ===
const char *ssid = "SSID";          // Replace with your SSID
const char *password = "PASSWORD";  // Replace with Password

/*

 Steps to create a Telegram Bot
  1.Open Telegram app

  Search for @BotFather and start chat

  Send /newbot

  Give your bot a name and username (e.g. SafeKidBot)

  You'll get a Bot Token like:
  123456789:ABCDefGhIjklMnOpQRsTUVwxYz12345678

  2. Get Your Chat ID
  Start chat with your bot (send any message)

  Visit this URL in browser (replace YOUR_BOT_TOKEN):

  https://api.telegram.org/bot<YOUR_BOT_TOKEN>/getUpdates
  Look for "chat":{"id":...} — that's your chat ID
  e.g., "id": 987654321

*/

// === Telegram Bot Info ===
String botToken = "YOUR_BOT_TOKEN";  // Replace with your bot token
String chatID = "CHAT_ID";           // Replace with your chat ID

// === Global Variables ===
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
Adafruit_SSD1306 display(128, 64, &Wire, -1);
Ticker redLEDBlinker;
Ticker buzzerBeepTicker;
Ticker sosMessageTicker;

unsigned long startTime = 0;
bool isPersonDetected = false;
bool isInAlertMode = false;
bool isInSOSMode = false;
bool sosTriggered = false;
unsigned long sosHoldStart = 0;


void IRAM_ATTR handleSOS() {
  if (!isInSOSMode) {  // Only allow trigger if not already in SOS mode
    sosTriggered = true;
  }
}


void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(SOS_BUTTON_PIN, INPUT_PULLDOWN);

  digitalWrite(BUZZER_PIN, INACTIVE_STATE);
  digitalWrite(RED_LED_PIN, INACTIVE_STATE);
  digitalWrite(GREEN_LED_PIN, INACTIVE_STATE);

  attachInterrupt(digitalPinToInterrupt(SOS_BUTTON_PIN), handleSOS, RISING);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true)
      ;
  }

  display.clearDisplay();
  display.display();

  WiFi.begin(ssid, password);
  displayMessage("Connecting", "to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  displayMessage("WiFi", "Connected");
  delay(1000);

  resetSystem();
}

void loop() {
  unsigned long currentTime = millis();

  // === SOS HOLD RESET ===
  if (isInSOSMode) {
    if (digitalRead(SOS_BUTTON_PIN) == HIGH) {
      if (sosHoldStart == 0) sosHoldStart = currentTime;
      if (currentTime - sosHoldStart >= SOS_HOLD_TIME_MS) {
        Serial.println("SOS RESET");
        exitSOSMode();
      }
    } else {
      sosHoldStart = 0;
    }
    return;  // Skip ultrasonic detection during SOS
  }

  int distance = sonar.ping_cm();

  // === Normal Occupancy Check ===
  if (isInAlertMode) {
    if (distance == 0 || distance > DETECTION_THRESHOLD) {
      redLEDBlinker.detach();
      buzzerBeepTicker.detach();
      resetSystem();
      isInAlertMode = false;
      sendTelegramMessage("✅ Washroom is now vacant. All okay.");
    }
  }

  if (distance > 0 && distance <= DETECTION_THRESHOLD) {
    if (!isPersonDetected) {
      isPersonDetected = true;
      startTime = currentTime;
    }
    displayElapsedTime(currentTime - startTime);
    indicateOccupied();
  } else {
    isPersonDetected = false;
    resetSystem();
  }

  // === SOS Activation ===
  if (sosTriggered) {
    sosTriggered = false;
    enterSOSMode();  // enter SOS and start periodic alerts
  }

  // === Timer Alert ===
  if (isPersonDetected && (currentTime - startTime) / 1000 >= TIME_LIMIT) {
    triggerAlert("Time Limit Exceeded");
    sendTelegramMessage("⚠️ Time Limit Exceeded in Washroom!");
  }

  delay(100);
}

// === Ticker Callbacks ===
void toggleRedLED() {
  static bool state = false;
  digitalWrite(RED_LED_PIN, state ? ACTIVE_STATE : INACTIVE_STATE);
  state = !state;
}

void toggleBuzzer() {
  static bool state = false;
  digitalWrite(BUZZER_PIN, state ? ACTIVE_STATE : INACTIVE_STATE);
  state = !state;
}

void sendRepeatedSOS() {
  sendTelegramMessage("🚨 SOS Button Pressed in Washroom!");
}

// === Mode Management ===
void enterSOSMode() {
  if (isInSOSMode) return;  // Don't allow re-entry

  isInSOSMode = true;
  isInAlertMode = true;
  sosTriggered = false;  // Clear trigger immediately
  sosHoldStart = 0;

  digitalWrite(GREEN_LED_PIN, INACTIVE_STATE);
  redLEDBlinker.attach(BLINK_INTERVAL, toggleRedLED);
  buzzerBeepTicker.attach(BLINK_INTERVAL, toggleBuzzer);
  sosMessageTicker.attach(SOS_REPEAT_INTERVAL_SEC, sendRepeatedSOS);

  displayMessage(" ", "SOS Activated");
  sendTelegramMessage("🚨 SOS Button Pressed in Washroom!");
}


void exitSOSMode() {
  isInSOSMode = false;
  isInAlertMode = false;
  sosTriggered = false;
  sosHoldStart = 0;

  redLEDBlinker.detach();
  buzzerBeepTicker.detach();
  sosMessageTicker.detach();

  resetSystem();
  sendTelegramMessage("✅ SOS Deactivated");
}


void triggerAlert(const char *message) {
  isInAlertMode = true;
  digitalWrite(GREEN_LED_PIN, INACTIVE_STATE);
  redLEDBlinker.attach(BLINK_INTERVAL, toggleRedLED);
  buzzerBeepTicker.attach(BLINK_INTERVAL, toggleBuzzer);
  displayMessage(" ", message);
}

void resetSystem() {
  redLEDBlinker.detach();
  buzzerBeepTicker.detach();
  sosMessageTicker.detach();

  digitalWrite(BUZZER_PIN, INACTIVE_STATE);
  digitalWrite(RED_LED_PIN, INACTIVE_STATE);
  digitalWrite(GREEN_LED_PIN, ACTIVE_STATE);

  displayMessage(" ", " Available");
}

void indicateOccupied() {
  digitalWrite(RED_LED_PIN, ACTIVE_STATE);
  digitalWrite(GREEN_LED_PIN, INACTIVE_STATE);
}

// === Display Functions ===
void displayMessage(const char *line1, const String &line2) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(line1);
  display.println(line2);
  display.display();
}

void displayElapsedTime(unsigned long elapsedMillis) {
  int seconds = (elapsedMillis / 1000) % 60;
  int minutes = (elapsedMillis / 60000) % 60;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 10);
  display.println("Occupied from");
  display.setTextSize(2);
  display.setCursor(40, 20);
  display.printf("%02d:%02d", minutes, seconds);
  display.display();
}

// === Telegram Function ===
void sendTelegramMessage(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://api.telegram.org/bot" + botToken + "/sendMessage?chat_id=" + chatID + "&text=" + message;
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.println("Telegram Message Sent");
    } else {
      Serial.println("Failed to send message");
    }
    http.end();
  }
}
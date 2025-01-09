// Child Safety Washroom System with SOS Button and Timer
#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// Pin Definitions
#define TRIG_PIN 15
#define ECHO_PIN 13
#define BUZZER_PIN 26
#define LED_PIN 12
#define SOS_BUTTON_PIN 32
#define OLED_SDA 21
#define OLED_SCL 22

// Active State Definitions
#define ACTIVE_STATE LOW
#define INACTIVE_STATE HIGH

// Parameters
#define MAX_DISTANCE 200 // Maximum distance for the ultrasonic sensor in cm
#define DETECTION_THRESHOLD 10 // Distance threshold to detect presence (in cm)
#define TIME_LIMIT 1200 // Time limit in seconds (20 minutes)

// Global Variables
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
Adafruit_SSD1306 display(128, 64, &Wire, -1);
unsigned long startTime = 0;
bool isPersonDetected = false;
bool sosTriggered = false;

void IRAM_ATTR handleSOS() {
    sosTriggered = true;
}

void setup() {
    // Initialize serial communication
    Serial.begin(115200);

    // Initialize pins
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(SOS_BUTTON_PIN, INPUT_PULLDOWN);

    // Attach interrupt for SOS button
    attachInterrupt(digitalPinToInterrupt(SOS_BUTTON_PIN), handleSOS, RISING);

    // Initialize OLED display
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;); // Don't proceed, loop forever
    }
    resetSystem();
    display.clearDisplay();
    display.display();

    // Startup message
    displayMessage("System Initialized", "Waiting for Activity");
    delay(2000);
}

void loop() {
    unsigned long currentTime = millis();

    // Check for presence
    int distance = sonar.ping_cm();
    if (distance > 0 && distance <= DETECTION_THRESHOLD) {
        if (!isPersonDetected) {
            isPersonDetected = true;
            startTime = currentTime;
        }
        displayElapsedTime(currentTime - startTime);
    } else {
        isPersonDetected = false;
        resetSystem();
    }

    // Check for SOS
    if (sosTriggered) {
        sosTriggered = false; // Reset the SOS flag
        triggerAlert("SOS Activated");
    }

    // Check for timeout
    if (isPersonDetected && (currentTime - startTime) / 1000 >= TIME_LIMIT) {
        triggerAlert("Time Limit Exceeded");
    }

    delay(500); // Small delay to prevent excessive processing
}

void triggerAlert(const char *message) {
    digitalWrite(BUZZER_PIN, ACTIVE_STATE);
    digitalWrite(LED_PIN, ACTIVE_STATE);
    displayMessage("ALERT!", message);
    while (true) {
        // Remain in alert state until manually reset
    }
}

void resetSystem() {
    digitalWrite(BUZZER_PIN, INACTIVE_STATE);
    digitalWrite(LED_PIN, INACTIVE_STATE);
    displayMessage("System Reset", "Waiting for Activity");
}

void displayMessage(const char *line1, const String &line2) {
    display.clearDisplay();
    display.setTextSize(1);
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
    display.setCursor(0, 0);
    display.println("Occupied from");
    display.printf("%02d:%02d", minutes, seconds);
    display.display();
}

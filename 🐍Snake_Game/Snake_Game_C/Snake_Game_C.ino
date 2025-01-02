#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

#define JOYSTICK_X 33
#define JOYSTICK_Y 32
#define BUZZER_PIN 2

#define SNAKE_MAX_LENGTH 12
int snake_x[SNAKE_MAX_LENGTH];
int snake_y[SNAKE_MAX_LENGTH];
int snake_length = 2;
int score = 0;
int snake_dir = 0;  // 0 = right, 1 = up, 2 = left, 3 = down
int food_x;
int food_y;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize food position
  food_x = random(0, display.width() / 8);
  food_y = random(0, display.height() / 8);

  // Initialize snake position
  snake_x[0] = 0;
  snake_y[0] = 0;
  snake_x[1] = 1;
  snake_y[1] = 0;

  drawSnake();
  drawFood();
}

void loop() {
  delay(80);

  // Read joystick values
  int xVal = analogRead(JOYSTICK_X);
  int yVal = analogRead(JOYSTICK_Y);

  // Dead zone for joystick
  int deadZone = 150;

  // Joystick control logic: Only allow valid direction changes
  if (snake_dir == 0 || snake_dir == 2) {
    // If moving horizontally, allow up or down commands
    if (yVal < (1850 - deadZone) && snake_dir != 3) {  // Move Up
      snake_dir = 1;
    } else if (yVal > (1850 + deadZone) && snake_dir != 1) {  // Move Down
      snake_dir = 3;
    }
  } else if (snake_dir == 1 || snake_dir == 3) {
    // If moving vertically, allow left or right commands
    if (xVal < (1850 - deadZone) && snake_dir != 0) {  // Move Left
      snake_dir = 2;
    } else if (xVal > (2150 + deadZone) && snake_dir != 2) {  // Move Right
      snake_dir = 0;
    }
  }

  // Move the snake
  for (int i = snake_length - 1; i > 0; i--) {
    snake_x[i] = snake_x[i - 1];
    snake_y[i] = snake_y[i - 1];
  }

  switch (snake_dir) {
    case 0:
      snake_x[0]++;  // Move right
      break;
    case 1:
      snake_y[0]--;  // Move up
      break;
    case 2:
      snake_x[0]--;  // Move left
      break;
    case 3:
      snake_y[0]++;  // Move down
      break;
  }

  // Wrap around screen edges
  if (snake_x[0] < 0) {
    snake_x[0] = display.width() / 8 - 1;
  } else if (snake_x[0] >= display.width() / 8) {
    snake_x[0] = 0;
  }

  if (snake_y[0] < 0) {
    snake_y[0] = display.height() / 8 - 1;
  } else if (snake_y[0] >= display.height() / 8) {
    snake_y[0] = 0;
  }

  // Check if snake eats the food
  if (snake_x[0] == food_x && snake_y[0] == food_y) {
    if (snake_length < SNAKE_MAX_LENGTH) {
      snake_length++;
    }
    score++;

    // Play a beep on the buzzer
    digitalWrite(BUZZER_PIN, HIGH);
    delay(10);
    digitalWrite(BUZZER_PIN, LOW);

    // Generate new food position
    food_x = random(0, display.width() / 8);
    food_y = random(0, display.height() / 8);
  }

  // Check if snake collides with itself
  for (int i = 1; i < snake_length; i++) {
    if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i]) {
      gameOver();
      Reset();
    }
  }

  // Refresh display
  display.clearDisplay();
  drawSnake();
  drawFood();
  display.display();
}

void drawSnake() {
  for (int i = 0; i < snake_length; i++) {
    display.fillRect(snake_x[i] * 8, snake_y[i] * 8, 8, 8, WHITE);
  }
}

void drawFood() {
  display.fillRect(food_x * 8, food_y * 8, 8, 8, WHITE);
}

void gameOver() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(5, 20);
  display.println("Game Over!");
  display.setCursor(15, 40);
  display.print("Score: ");
  display.println(score);
  display.display();
  delay(3000);
}

void Reset() {
  score = 0;
  snake_length = 2;
  snake_dir = 0;  // Start by moving right
  snake_x[0] = 0;
  snake_y[0] = 0;
  snake_x[1] = 1;
  snake_y[1] = 0;

  // Randomize new food position
  food_x = random(0, display.width() / 8);
  food_y = random(0, display.height() / 8);
}

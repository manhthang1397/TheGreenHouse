#include <AccelStepper.h>

// ----- Stepper motor (A4988) -----
#define STEP_PIN 3
#define DIR_PIN  2

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

// ----- Buttons -----
#define BUTTON_UP    4
#define BUTTON_DOWN  5

// ----- Blink LED -----
#define LED_PIN 6

// ----- Speed Levels -----
const float maxSpeed = 500;
const int totalLevels = 21;
const float speedStep = maxSpeed / (totalLevels - 1);
int currentLevel = 0;

// ----- Blink Timing -----
unsigned long lastBlinkTime = 0;
bool ledState = LOW;

void setup() {
  Serial.begin(9600);

  // Stepper setup
  stepper.setMaxSpeed(maxSpeed);
  stepper.setAcceleration(500);
  stepper.setSpeed(0);

  // Button setup
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);

  // LED setup
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Handle button press
  if (digitalRead(BUTTON_UP) == LOW) {
    if (currentLevel < totalLevels - 1) {
      currentLevel++;
      stepper.setSpeed(currentLevel * speedStep);
      Serial.print("Speed: ");
      Serial.println(currentLevel * speedStep);
    }
    delay(200); // debounce
  }

  if (digitalRead(BUTTON_DOWN) == LOW) {
    if (currentLevel > 0) {
      currentLevel--;
      stepper.setSpeed(currentLevel * speedStep);
      Serial.print("Speed: ");
      Serial.println(currentLevel * speedStep);
    }
    delay(200); // debounce
  }

  // Run stepper
  stepper.runSpeed();

  // Blink LED based on current speed
  blinkSpeedLED(currentLevel);
}

// ----- Blink LED Function -----
void blinkSpeedLED(int level) {
  if (level == 0) {
    digitalWrite(LED_PIN, LOW); // stay off at level 0
    return;
  }

  // Map level to blink rate: level 1 = slow, level 20 = fast
  int blinkInterval = map(level, 1, totalLevels - 1, 1000, 100); // in ms

  unsigned long currentMillis = millis();
  if (currentMillis - lastBlinkTime >= blinkInterval) {
    lastBlinkTime = currentMillis;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
}

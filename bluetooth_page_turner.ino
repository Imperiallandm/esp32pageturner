#include <BleKeyboard.h>

BleKeyboard bleKeyboard("ESP32 Page Turner", "DIY Music", 100);

const int leftPedalPin = 14;
const int rightPedalPin = 27;

bool lastLeftState = HIGH;
bool lastRightState = HIGH;

void setup() {
  pinMode(leftPedalPin, INPUT_PULLUP);
  pinMode(rightPedalPin, INPUT_PULLUP);
  bleKeyboard.begin();
}

void loop() {
  if (!bleKeyboard.isConnected()) return;

  bool leftState = digitalRead(leftPedalPin);
  bool rightState = digitalRead(rightPedalPin);

  // LEFT PEDAL (Previous Page)
  if (leftState == LOW && lastLeftState == HIGH) {
    bleKeyboard.write(KEY_LEFT_ARROW);
    delay(200);   // simple debounce
  }

  // RIGHT PEDAL (Next Page)
  if (rightState == LOW && lastRightState == HIGH) {
    bleKeyboard.write(KEY_RIGHT_ARROW);
    delay(200);   // simple debounce
  }

  lastLeftState = leftState;
  lastRightState = rightState;
}

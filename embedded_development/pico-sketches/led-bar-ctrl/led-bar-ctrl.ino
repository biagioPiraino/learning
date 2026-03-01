#define PIN_BTN 15
// byte: This is a data type used in Arduino that represents an 8-bit unsigned integer (values from 0 to 255). 
// If you are using standard C, you would typically use unsigned char instead.
byte ledPins[] = {16, 17, 18, 19, 20, 21, 22, 23, 26, 27, 28};
int ledCounts;

void setup() {
  pinMode(PIN_BTN, INPUT);
  ledCounts = sizeof(ledPins);
  for (int i = 0; i < ledCounts; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  if (btnPressed()){
    delay(20); // bounce effect
    if (btnPressed()) { // stable status
      startAnimation();
    }
    while(btnPressed());
  }
}

bool btnPressed() {
  return digitalRead(PIN_BTN) == LOW;
}

void startAnimation() {
  for (int i = 0; i < ledCounts; i++) {
    blinkLed(ledPins[i]);
  }
  for (int i = ledCounts - 1; i > -1; i--) {
    blinkLed(ledPins[i]);
  }
}

void blinkLed(int pin) {
  digitalWrite(pin, HIGH);
  delay(100);
  digitalWrite(pin, LOW);
}
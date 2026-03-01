const byte ledPins[] = {13, 12, 11}; // red == 13, green == 12, blue == 11 
int red, green, blue;
int ledCount;

void setup() {
  ledCount = sizeof(ledPins);
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // random rbg color generator
  red = random(0, 255);
  blue = random(0, 255);
  green = random(0, 255);
  setColor(red, green, blue);
  delay(5000);

  // the following set the color to sand (76, 70, 50)
  red = 76;
  blue = 50;
  green = 70;
  setColor(red, green, blue);
  delay(5000);
}

void setColor(byte red, byte green, byte blue) {
  analogWrite(ledPins[0], 255 - red);
  analogWrite(ledPins[1], 255 - green);
  analogWrite(ledPins[2], 255 - blue);
}

#define PIN_RED_LED 15

void setup() {
  pinMode(PIN_RED_LED, OUTPUT);
}

void loop() {
  // the range of 0-255 represents the duty cycle from 0-100%
  for (int i = 0; i < 255; i++) {
    analogWrite(PIN_RED_LED, i); // gradulaly turn on the led
    delay(1); // the higher the value, the slower the duty cycle and viceversa
  }
  for (int i = 255; i > -1; i--) {
    analogWrite(PIN_RED_LED, i); // gradulaly turn off the led
    delay(1);
  }
}

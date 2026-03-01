#define PIN_RED_LED 15
#define PIN_BTN 13

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_RED_LED, OUTPUT);
  pinMode(PIN_BTN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(PIN_BTN) == LOW) {
    digitalWrite(PIN_RED_LED, HIGH); // turn on led when btn pressed
  } else {
    digitalWrite(PIN_RED_LED, LOW);
  }
}

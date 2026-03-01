#define LED_OUTPUT 15

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_OUTPUT, OUTPUT);  // pin 15 to be an output
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_OUTPUT, HIGH); // output high voltage to turn on the led
  delay(1000);
  digitalWrite(LED_OUTPUT, LOW); // output low voltage to turn off the led
  delay(1000);
}

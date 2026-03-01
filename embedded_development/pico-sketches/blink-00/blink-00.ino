void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH); // turn led on high voltage
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW); // turn led off low voltage
  delay(1000);
}

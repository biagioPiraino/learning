#define PIN_RED_LED 15
#define PIN_BTN 13
bool ledState = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_RED_LED, OUTPUT);
  pinMode(PIN_BTN, INPUT);
}

// the following code take into consideration 
//  the bounce effect that happen when pressing a btn
// the passage from state HIGH - LOW is not immediate, 
//  a short period of buffering (bounce) it is present before the new state is reached
void loop() {
  if (btnPressed()) {   // listen for the button to be pressed
    delay(20);          // consider bounce effect and check for stable status
    if (btnPressed()) { // when status LOW is stable, change led status
      reverseGPIO(PIN_RED_LED);
    }
    while(btnPressed()); // waiting the button to be released
  }
}

bool btnPressed() {
  return digitalRead(PIN_BTN) == LOW;
}

void reverseGPIO(int pin) {
  ledState = !ledState;
  digitalWrite(pin, ledState);
}

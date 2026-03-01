#define PIN_BUZZER 15
#define PIN_BUTTON 16 

void setup() {
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  digitalWrite(PIN_BUZZER, LOW);
}

// The software part is actually quite simple and can be summarised
// as emit a 3.3v signal from pin 15 when the button is clicked (pin 15)

// The circuit tho is the interesting part, consider it as divided in 2 parts

// The first one used to intercept the click of the button
// and the second one to emit a 3.3v signal, amplified it with a transistor to 5v
// in order to make the buzzer sound, and reintroduce the 5v into the board via the VBUS

// Fascinating!
void loop() {
  if (digitalRead(PIN_BUTTON) == LOW) {
    digitalWrite(PIN_BUZZER, HIGH);
  } else {
    digitalWrite(PIN_BUZZER, LOW);
  }
}

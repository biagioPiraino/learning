#define PIN_BUZ 15
#define PIN_BTN 16

// A little bit of theory before reading the following

// A frequency means how many times something repeats per second 
// in the case of the buzzer it represents how many time we turn it on-off per second

// The formula explaining the relationship between frequency, cycles and time is: freq = N / T 
// - freq is the frequency expressed in Hertz (Hz)
// - N number of cycles, 
// - T time duration in seconds

// If you want to calculate many second a full cycle last, you need to rearrange for the times T = 1 / freq
// example: if frequency is 1000Hz, time will be 1 / 1000 seconds
void setup() {
  pinMode(PIN_BUZ, OUTPUT);
  pinMode(PIN_BTN, INPUT);
}

void loop() {
  if (digitalRead(PIN_BTN) == LOW) {
    alert();
  } else {
    freq(PIN_BUZ, 0, 10);
  }
}

void alert() {
  float sinValue;  // sine value
  int frequency;   // sound frequency
  // we loop from 0 to 360 degree, like a circle
  for (int x = 0; x < 360; x += 10) {
    // we calculate the sin value of x 
    // (x is converted to radians because the C sin() function accept radians)
    sinValue = sin(x * (PI / 180));
    
    // we use the sin value to modulate the sound frequency 
    // to create a smooth wave-like change in pitch as you move around the sine curve:
    // - whit sin == -1 -> frequency 1500 Hz
    // - whit sin == 0  -> frequency 2000 Hz
    // - whit sin == +1 -> frequency 2500 Hz
    frequency = 2000 + sinValue * 500;
    freq(PIN_BUZ, frequency, 10);
  }
}

// the following is manual Pulse Width Modulation (PWM) used to drive the passive buzzer
// a sound wave type is made by turning the buzzer on and off really fast
void freq(int PIN, int frequency, int times) {
  if (frequency == 0) {
    digitalWrite(PIN, LOW);
  }
  else {
    // the upper limit is derived from the formula N = f * T 
    // and it represents how many cycles fit in times millisecond considering a constant frequency received
    // since times is expressed in millisecond and the frequency used is in second, 
    // we need to equalise the unit of measure by expressing the frequency in milliseconds (/ 1000)
    for (int i = 0; i < times * frequency / 1000; i++) {
      // full cycle represented by half of it staying on HIGH and the other half stay low
      // the separation point is set by the delayMicroseconds function
      digitalWrite(PIN, HIGH);
      delayMicroseconds(1000000 / frequency / 2);
      digitalWrite(PIN, LOW);
      delayMicroseconds(1000000 / frequency / 2);
    }
  }
}

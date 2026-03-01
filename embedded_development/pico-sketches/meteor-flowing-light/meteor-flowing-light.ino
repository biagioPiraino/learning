const byte ledPins[] = {16, 17, 18, 19, 20, 21, 22, 26, 27, 28};
int ledCounts;
int delayTimes = 50; // flowing speed, the smaller the faster

// The choice of progression suggests the system is using a 12-bit resolution for PWM where max value is 2^12 -1 = 4095.
// This allow for finer control over the outpoute compared to an 8-bit system which would have a max value of 255.
// So ultimely the choice has been made to have futher and more grained control to the smoothness of the transition,
// knowing that the later map function will map the value to a compatible 8bit range
const int dutys[] = {0,0,0,0,0,0,0,0,0,0,                   // initial state of progression, no power is sent to led (delay)
                     4095,2047,1023,512,256,128,64,32,16,8, // progression defined in 2 exps  
                     0,0,0,0,0,0,0,0,0,0};                  // final state of progression, no power is sent to led (delay)

void setup() {
  // setting up output pin of the ledbar
  ledCounts = sizeof(ledPins);
  for (int i = 0; i < ledCounts; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

// this still need to be understood fully, however on high level, 
// the outer loop is used to smooth the transition from status off 
// to a desired state, the greater the range the smoother the transition.
void loop() {
  for (int i = 0; i < 20; i++){
   for(int j = 0; j < ledCounts; j++) {
    // the map function takes a value and remaps it from one range to another.
    // the general syntax is map(value, fromLow, fromHigh, toLow, toHigh)
    // fromLow/High is the range of the input value found in dutys
    // toLow/High is the range to which you want to map the input value
    // the mapping range target 0-255 usually because the analogWrite method expect values in that range
    analogWrite(ledPins[j],map(dutys[i+j], 0, 4095, 0, 255)); // map conversion used to make the write compatible with analogWrite
   }
   delay(delayTimes);
  }

  for (int i = 0; i < 20; i++){
   for(int j = 0; j < ledCounts; j++) {
    analogWrite(ledPins[ledCounts-j-1],map(dutys[i+j], 0, 4095, 0, 255));
   }
   delay(delayTimes);
  }
}

// The baud rate is how fast data is sent over a communication channel (like cable between two devices).
// In digital communication a baud is one signal change per second
// so the below 115200 means that 115200 signal changes per second
// Not specifying the same baud rate into the serial monitor window may give connectivity issues

// This rate differs from a bit rate (# of bits sent per second), 
// that is the actual measure used to understand how much data is moved per second

// In Pico, the pins associated with serial communication are named UART
// UART stands for Universal Asynchronous Receiver-Transmitter protocol
// This protocol has two commuincation lines, one responsible for sending data (TX) and one for receiving data (RX)
// So in Pico:
//  - UART TX is the sender
//  - UART RX is the receiver

// If you find difficulties in using the serial monitor in arduino, it's probably due to permissions
// Check the group owner of the dev associated to the board (at this stage is dialout), 
// and add yourself (or the user running the ide) in the group using the following command
// sudo usermod -a -G dialout biagio
void setup() {
  // initialise serial port with a 115200 baud rate
  Serial.begin(115200);
  delay(2000);
  Serial.println("initialisation completed...");
}

void loop() {
  // millis retrieve the number of millisecond since current boot
  Serial.println( millis() / 1000 % 60 ); // modulus guarantee number of second always range from 0-59
  delay(1000);
}

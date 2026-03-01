const byte ledPins[] = {13, 12, 11}; // red == 13, green == 12, blue == 11 
int red, green, blue;
int ledCount;

void setup() {
  ledCount = sizeof(ledPins);
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

// the following code generate a smooth rgb rgadient using pulse-width modulation on three led pins
// the loop function cycles throught the uint spectrum (0-256) updating the color of the led at each step
void loop() {
  for (int i = 0; i < 256; i++){ // 0-255 spectrum from red to blue
    // wheel compute the rgb color
    // setColor applies the color to the led
    setColor(wheel(i));
    delay(100);
  }
}

// Brightness adjustment:
// extracts the red, green, blue component and applies them using an analog write
void setColor(long rgb){
  // a 24-bit color value consists of three 8-bit (1 byte) components:
  // red (Most significant byte, MSB)
  // green (middle byte)
  // blue (least significant byte, LSB)

  // each component can have value from 0-255 (0x00 to 0xFF in hexadecimal).
  // standard format is 0xRRGGBB so that:
  // red -> 0xFF0000 (red = 255, green = 0, blue = 0)
  // green -> 0x00FF00 (red = 0, green = 255, blue = 0)
  // blue -> 0x0000FF (red = 0, green = 0, blue = 255)
  // yellow -> 0xFFFF00 (red = 255, green = 255, blue = 0)

  // rgb is a single 24 but integer so we need to extract the red value performing right shift and bitwise operations
  // rgb >> 16 -> move the red component to the lowest 8bit
  // & 0xFF    -> applies a bitwise AND with 0xff (11111111 in binary) to extract only the lowest 8 bits
  // example:

  // Binary:   10101010 10111011 11001100   (0xAABBCC)
  
  // Shifted:       00000000 00000000 10101010   (>> 16, red)
  // AND 0xFF:      00000000 00000000 11111111   ==
  // ----------------------------------------------
  //                00000000 00000000 10101010   (Extract red: 0xAA)

  // Shifted:       00000000 10101010 10111011   (>> 8, green)
  // AND 0xFF:      00000000 00000000 11111111   ==
  // ----------------------------------------------
  //                00000000 00000000 10111011   (Extract green: 0xBB)

  // Shifted:       10101010 10111011 11001100   (>> 0, blue)
  // AND 0xFF:      00000000 00000000 11111111   ==
  // ----------------------------------------------
  //                00000000 00000000 11001100   (Extract blue: 0xCC)
  analogWrite(ledPins[0], 255 - (rgb >> 16) & 0xFF);  // extract red
  analogWrite(ledPins[1], 255 - (rgb >> 8) & 0xFF);   // extract green  
  analogWrite(ledPins[2], 255 - (rgb >> 0) & 0xFF);   // extract blue
}

// Color mapping:
// the wheel function generatges an rgb color based on the position of the in the uint spectrum
// smoothly transitioning between red, green and blue

// the transiction cycle followed is the following:
// red to green   -> 0 - 84
// green to blue  -> 85 - 169
// blue to red    -> 170 - 255

// each phase span 85 steps (255 / 3 ~ 85) ensuring smooth transitions
long wheel(int position) {
  // this ensures that wheel position will always stays in the range of [0-254)
  // even if the value of 'position' exceed 255 (or 0xff in hexadecimal)
  // % is the modulus operator (reminder after the division, 240 % 255 == 240, 0 with 244 remainder)
  long wheelPosition = position % 0xff;

  if (wheelPosition < 85) {  // red to green position
    // (255 - wheelPosition * 3) << 16) -> control the red portion, shift left to the MSB
    //      - start at max 255
    //      - decrease by 3 each step till reaching 0 at 85

    // (wheelPosition * 3) << 8         -> control the green portion, shift left to middle byte
    //      - start at min 0
    //      - increase by 3 each step till reaching max 255 at 85
    
    // | (bitwise OR operation), combines the red and green value into a single 24bit integer 
    return ((255 - wheelPosition * 3) << 16) | ((wheelPosition * 3) << 8);
  } else if (wheelPosition < 170) { // green to blue position
    // convert the wheel position value to its relative phase of 0-84 steps (85-169 range)
    wheelPosition -= 85;
    // same as above in terms of step and fading, however lef shift is different and applies to green-blue spectrum
    return (((255 - wheelPosition * 3) << 8) | (wheelPosition * 3));
  } else {                          // blue to red position
    wheelPosition -= 170;
    // increasing red color (see left byte shift) and decrease blue color (no byte shift)
    return ((wheelPosition * 3) << 16 | (255 - wheelPosition *3));
  }
}

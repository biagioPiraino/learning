# include <Adafruit_NeoPixel.h>
# define PIN        16  // gpio
# define NUM_PIXELS 8   // number of pixel presents on the board
int setColor[5][3] = {{255,0,0}, {0,255,0}, {0,0,255}, {225,225,225}, {0,0,0}}; // color transitions red -> green -> blue -> white -> none

Adafruit_NeoPixel pixels(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
  pixels.setBrightness(50);
}

void loop() {
  // upper range is number of color set on setColour[a] == 5
  // it basically means for every color transition
  for (int j = 0; j < 5; j++) { 
    // control the display of numbered pixel and the color setting
    for (int i = 0; i < NUM_PIXELS; i++) {
      pixels.setPixelColor(i, setColor[j][0], setColor[j][1], setColor[j][2]);
      pixels.show();
      delay(100);
    }
    delay(500);
  }
}

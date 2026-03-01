# include <Adafruit_NeoPixel.h>
# define PIN 16
# define NUM_PIXELS 8
int red = 0;
int blue = 0;
int green = 0;
Adafruit_NeoPixel strip(NUM_PIXELS, PIN, NEO_RGB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(20);
}

void loop() {
  for (int j = 0; j < 256 * 5; j++) {
    for (int i = 0; i < NUM_PIXELS; i++) {
      wheel(((i * 256 / 8) + j)%255);
      strip.setPixelColor(i, strip.Color(red, green, blue));
    }
    strip.show();
    delay(10);
  }
}

void wheel(byte position) {
  position = 255 - position;
  if (position < 85) {
    red = 255 - position * 3;
    blue = position * 3;
    green = 0;
  }
  else if (position < 170) {
    position -= 85;  // convert position to its relative phase 0-84 steps
    red = 0;
    blue = 255 - position * 3;
    green = position * 3;
  }
  else {
    position -= 170;
    red = position * 3;
    blue = 0;
    green = 255 - position * 3;
  }
}

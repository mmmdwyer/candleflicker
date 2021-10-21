// Simple Candle Flicker
//
// A super-simple single-NeoPixel candle simulator
// Intended for the Digispark ATTINY85-based boards,
// with a single Neopixel attached to P0, 5v and GND.

// Board: Digispark 8MHz No USB

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, 0, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
}


void loop() {
  //  Base Color: Purple
  int r = 128, g = 0, b = 128;

  //  Flicker, based on our initial RGB values
  int flicker = random(0, 55);
  int r1 = r - flicker;
  int g1 = g - flicker;
  int b1 = b - flicker;
  if (g1 < 0) g1 = 0;
  if (r1 < 0) r1 = 0;
  if (b1 < 0) b1 = 0;

  pixels.setPixelColor(0, r1, g1, b1);

  pixels.show();

  //  Wait a random period before looping back.
  delay(random(10, 113));
}

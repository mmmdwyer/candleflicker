// Based on Simple Candle Flicker
//
// Random-flicker a number of pixels for a yellow fire-effect
// plus glowing red eyes.
//
// Intended for the Digispark ATTINY85-based boards,
// with a single Neopixel attached to P0, 5v and GND.

// Board: Digispark 8MHz No USB

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(6, 0, NEO_GRB + NEO_KHZ800);

unsigned long nextthink[6] = {0, 0, 0, 0, 0};
int eyedir = 0;
int eyelev = 0;

void setup() {
  pixels.begin();
}


void loop() {
  for (int i = 2 ; i < 6 ; i++) {
    if (millis() > nextthink[i]) {
      pixels.setPixelColor(i, random(64, 128), random(0, 128), 0);
      nextthink[i] = millis() + random(10, 120);
    }
  }

  if ( millis() > nextthink[0]) {
    if ( eyedir ) {
      eyelev++;
      if (eyelev > 128) {
        eyedir = 0;
      }
    }  else {
      eyelev--;
      if (eyelev < 8 ) {
        eyedir = 1;
      }
    }
    pixels.setPixelColor(0, eyelev, 0, 0);
    pixels.setPixelColor(1, eyelev, 0, 0);
    nextthink[0] = millis() + 10;
  }
  pixels.show();
}

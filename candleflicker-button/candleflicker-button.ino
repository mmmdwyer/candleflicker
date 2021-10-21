// Candleflicker - button
//
// A super-simple single-NeoPixel candle simulator
// Intended for the Digispark ATTINY85-based boards,
// with a single Neopixel attached to P0, 5v and GND.
// This version also includes a momentary button between
// the 5v and P2 pins, and a 10k resistor between GND and P2.
// When you hold this button, it will quickly spin through
// the colors. Release it when it gets to the color you like.
// After a brief delay, the selected color is then stored in
// EEPORM so that the candle starts at that color at the next
// powerup.

// Board: Digispark 8MHz No USB

#include <Adafruit_NeoPixel.h>
#include "EEPROM.h"


#define LEDPIN 0 // Which pin is connected to the NeoPixel data line
#define INDPIN 1 // Pin 1 is built-in LED. Uses PWM in DEBUG mode
#define BUTTONPIN 2 // This is a button held low with a 10k resistor.
#define EEPROMLOC 0 // The eeprom offset of the stored hue
// Avoid pins 3 and 4 -- they're on the USB port
// PWM on 0, 1 and 4

#undef DEBUG  // Debug is off
// #define DEBUG 1  // Debug is on

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, LEDPIN, NEO_GRB + NEO_KHZ800);

int basehue = 54612;    // Hue; 0-65535 degrees around the colorwheel. 0=red
//  basesat=255;        // Saturation; is always set to max
int baseval = 128;      // Value; the upper brightness of the candle, 0-255.
int delaytimer = 10;    // How long is a flicker
int eepromtimer = 65535;// How long to wait before saving color to EEPROM
int eepromhue = basehue;// The color saved in the EEPROM

void setup() {
  pinMode(BUTTONPIN, INPUT);

#ifdef DEBUG
  pinMode(INDPIN, OUTPUT);
  digitalWrite(INDPIN, LOW);
#endif

  pixels.begin();

  // Load the last saved hue from eeprom
  eepromhue = EEPROM.get(EEPROMLOC, eepromhue);
  basehue = eepromhue;

#ifdef DEBUG
  // This is a test sequence that will ensure you have you NEO_GRB set right.
  pixels.setPixelColor(0, pixels.ColorHSV(0, 255, baseval)); // 0deg Red
  pixels.show();
  delay(200);

  pixels.setPixelColor(0, pixels.ColorHSV(21845, 255, baseval)); // 120deg Green
  pixels.show();
  delay(200);

  pixels.setPixelColor(0, pixels.ColorHSV(43690, 255, baseval)); // 240deg Blue
  pixels.show();
  delay(200);

  pixels.setPixelColor(0, pixels.ColorHSV(32768, 255, baseval)); // 180deg Cyan
  pixels.show();
  delay(200);

  pixels.setPixelColor(0, pixels.ColorHSV(54613, 255, baseval)); // 300deg Magenta
  pixels.show();
  delay(200);

  pixels.setPixelColor(0, pixels.ColorHSV(10922, 255, baseval)); // 60deg Yellow
  pixels.show();
  delay(200);
#endif
}


void loop() {
  // Check if the button is down
  int button = digitalRead(BUTTONPIN);
  if (button == HIGH) {
    basehue++; // This will rollover on its own.
    eepromtimer = 65535;
  }

#ifdef DEBUG
  // Display the hue using the brightness of the built-in LED.
  // Primarily used for debugging, and causes light-contamination in normal use.
  analogWrite(INDPIN, (basehue / 256)); // Sets the brightness of the indicator
#endif

  // Until the eepromtimer expires, you can keep changing the hue without burning an eeprom
  // write cycle.
  if ((!eepromtimer--) && (eepromhue != basehue)) {
    eepromhue = basehue;
    EEPROM.put(EEPROMLOC, eepromhue);

#ifdef DEBUG
    //  This inserts a flash so you can tell when the timer has expired and your config is saved
    pixels.setPixelColor(0, pixels.ColorHSV(10922, 255, baseval)); pixels.show(); // Yellow
    delay(200);
    pixels.setPixelColor(0, pixels.ColorHSV(0, 255, baseval)); pixels.show(); // Red
    delay(200);
    pixels.setPixelColor(0, pixels.ColorHSV(0, 0, 0)); pixels.show(); // Off
    delay(200);
#endif

  }

  // Decrement the delaytimer, and if it reached zero...
  if (!delaytimer--) {
    int vd;
    if (basehue == eepromhue) {
      // Flicker, by ducking the Value a random value
      // Larger numbers make a more flashy, strobe-y experience;
      // smaller numbers for a more gentle flame.
      int flicker = random(0, 50);
      vd = baseval - flicker;
      if (vd < 0) vd = 0;
    }
    else {
      // Don't flicker while spinning the colorwheel
      vd = baseval;
    }

    // Push the selected color out to the LED
    pixels.setPixelColor(0, pixels.ColorHSV(basehue, 255, vd));
    pixels.show();


    // A flicker lasts a random duration
    // Larger numbers make for a more laid-back candle; smaller
    // numbers make it more frenetic.
    delaytimer = random(1000, 3000);
  }
}

# Candle Flicker

## Hardware
The core hardware is a Digispark Mini clone -- the typically-blue, six pin ATTINY85-based Arduino-like development platform with a microusb socket. You could probably run this on almost any AVR Arduino-like platform, though.

A single NeoPixel RGB LED is connected to the board at +5V, P0, and GND. 

A NO momentary switch is optionally placed between 5V and P2, with a 10k resistor going from P2 to GND.

## Software
Two Arduino sketches are provided.

**simplecandleflicker** is a super-simple version that doesn't use the button. The base color is hard-coded.

**candleflicker-button** allows you to change the color by holding down the button until it is the desired color. That's saved to EEPROM so that the candle will remain that color even if the power is interrupted.

### Theory of operation
The candle sits in a tight loop, with a base color -- typically at 50% brightness. At the top of every loop, three random values from 0 to 50 are subtracted from each of the red, green, and blue channels. The candle then sleeps for a random internval before going back to the top of the loop.

Adjusting the range of the flicker value changes how strong the flame is.

Adjusting the range of the delaytimer value changes how frantic the flame is. 


## Compiling
These are assuming you are using the Digispark or its clone. Full details can be found at the [Digistump Github](https://github.com/digistump/DigistumpArduino) or at the [Digispark Wiki](http://digistump.com/wiki/digispark).

 * Board Package: [http://digistump.com/package_digistump_index.json](http://digistump.com/package_digistump_index.json)
 * Board: Digispark (8mhz - No USB)
 * Programmer: Micronucleus

You might also use other ATTINY85 boards, like the Adafruit Gemma or Trinket, which use their own board package.

Note that all of these devices generally use a bitbang USB method that does not play well with more modern USB3 controllers. If you have problems with programming your board, try using a USB2 port (usually black instead of blue) or get a cheap USB2 hub and plug into that.  Even then, programming these chips very often just randomly fails. Keep trying, and it should work within two or three tries.


## Thank you

### Limor "Ladyada" Fried - [Adafruit](https://adafruit.com)
It is undeniable that the WS2812 that makes this project so incredibly simple would not have been nearly as easy and accessible if not for the work, both technical and commercial, that Adafruit has done for the community. Although this project uses no Adafruit products and no Adafruit code, I greatly appreciate their contributions. Also, consider running this on their 5V Trinket or make something wearable with a Gemma!

### Erik Kettenburg - [DigiStump](http://digistump.com)
Although Digistump seems to have abandoned the original Digispark design for their newer ATTINY87-based PRO model, they released the original design that would plug directly into a USB port. Indeed, it doesn't appear they ever released a MicroUSB+TINY85 model. It seems that's strictly from the realm of clone importers. Regardless, I am grateful for Digistump's work at making the ATTINY85 so approachable for silly throw-away blinky projects.

### [WorldSemi](http://www.world-semi.com/)
Designed and marketed the WS2812 and other RGB LED controller chips that straight-up revolutionized RGB LEDs. I tried to do this project with a pile of shift registed and a single-color LED, and the price and easy-of-use made that whole experiment silly. Yes, you could do this effect with nothing more than 7400 logic... but your time and money isn't worth it.

### Atmel, now [Microchip](http://www.microchip.com/)
I don't know what's special about the AVR chips, but they're unavoidable in the hobbyist space, and drew me into their ecosystem.

### [Arduino](https://www.arduino.cc/)
I love/hate this environment, but it has undeniably unlocked the great power of these little chips, and for that I'm grateful.





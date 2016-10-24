// Simple NeoPixel test.  Lights just a few pixels at a time so a
// 1m strip can safely be powered from Arduino 5V pin.  Arduino
// may nonetheless hiccup when LEDs are first connected and not
// accept code.  So upload code first, unplug USB, connect pixels
// to GND FIRST, then +5V and digital pin 6, then re-plug USB.
// A working strip will show a few pixels moving down the line,
// cycling between red, green and blue.  If you get no response,
// might be connected to wrong end of strip (the end wires, if
// any, are no indication -- look instead for the data direction
// arrows printed on the strip).

#include <Adafruit_NeoPixel.h>

#define PIN       6
#define N_LEDS    46
#define POT_PIN   A0

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  strip.begin();
  pinMode(POT_PIN, INPUT);
}

// cycle rgb
void loop() {
  unsigned int color = 0;
  const unsigned int color_step = 20;
  unsigned int delay_time = 30;
  for(unsigned int offset = 0; offset < strip.numPixels(); ++offset) {
    delay_time = pot_select(POT_PIN, 100, 1);
    set_roygbiv(strip, offset);
    strip.show();
    delay(delay_time);
  }
}

//void loop() {
//  unsigned int color = 0;
//  const unsigned int color_step = 20;
//  unsigned int delay_time = 30;
//  unsigned int train_length = 5;
//  unsigned int start_time = 0;
//  const unsigned int cycle_time = 15000;
//
//  // cycle rgb
//  start_time = millis();
//  while(millis() - start_time < cycle_time) {
//    for(unsigned int offset = 0; offset < strip.numPixels(); ++offset) {
//      delay_time = pot_select(POT_PIN, 100, 1);
//      set_roygbiv(strip, offset);
//      strip.show();
//      delay(delay_time);
//    }
//  }
//  
//  // explode
//  start_time = millis();
//  while(millis() - start_time < cycle_time) {
//    while(color < 256) {
//      for(unsigned int pixel = 0; pixel < strip.numPixels() / 2; ++pixel) {
//        delay_time = pot_select(POT_PIN, 100, 1);
//        strip.setPixelColor(pixel + 23, wheel(color));
//        strip.setPixelColor(23 - pixel, wheel(color));
//        strip.show();
//        delay(delay_time);
//      }
//      for(unsigned int pixel = 0; pixel < strip.numPixels() / 2; ++pixel) {
//        delay_time = pot_select(POT_PIN, 100, 1);
//        strip.setPixelColor(pixel, 0);
//        strip.setPixelColor(strip.numPixels() - pixel, 0);
//        strip.show();
//        delay(delay_time);
//      }
//      color += color_step;
//    }
//  }
//
//  // train
//  start_time = millis();
//  while(millis() - start_time < cycle_time) {
//    while(color < 256) {
//      for(unsigned int pixel = train_length - 1; pixel < strip.numPixels(); ++pixel) {
//        delay_time = pot_select(POT_PIN, 200, 1);
//        train_length = pot_select(POT_PIN, 10, 1);
//        strip.setPixelColor(pixel, wheel(color));
//        strip.setPixelColor(pixel - train_length, 0);
//        strip.setPixelColor(strip.numPixels() - pixel, wheel(color));
//        strip.setPixelColor(strip.numPixels() - pixel + train_length, 0);
//        strip.show();
//  //      delay(delay_time);
//        delay(0.15 * (800 - pixel * (strip.numPixels() - pixel)));
//      }
//      color += color_step;
//    }
//  }
//}

//// explode from middle
//void loop() {
//  unsigned int color = 0;
//  const unsigned int color_step = 15;
//  unsigned int delay_time = 30;
//  while(color < 256) {
//    for(unsigned int pixel = 0; pixel < strip.numPixels() / 2; ++pixel) {
//      delay_time = pot_select(POT_PIN, 100, 1);
//      strip.setPixelColor(pixel + 23, wheel(color));
//      strip.setPixelColor(23 - pixel, wheel(color));
//      strip.show();
//      delay(delay_time);
//    }
//    for(unsigned int pixel = 0; pixel < strip.numPixels() / 2; ++pixel) {
//      delay_time = pot_select(POT_PIN, 100, 1);
//      strip.setPixelColor(pixel, 0);
//      strip.setPixelColor(strip.numPixels() - pixel, 0);
//      strip.show();
//      delay(delay_time);
//    }
//    color += color_step;
//  }
//}

///// Trains
//void loop() {
//  unsigned int color = 0;
//  const unsigned int color_step = 20;
//  unsigned int delay_time = 30;
//  unsigned int train_length = 5;
//  while(color < 256) {
//    for(unsigned int pixel = train_length - 1; pixel < strip.numPixels(); ++pixel) {
//      delay_time = pot_select(POT_PIN, 200, 1);
//      train_length = pot_select(POT_PIN, 10, 1);
//      strip.setPixelColor(pixel, wheel(color));
//      strip.setPixelColor(pixel - train_length, 0);
//      strip.setPixelColor(strip.numPixels() - pixel, wheel(color));
//      strip.setPixelColor(strip.numPixels() - pixel + train_length, 0);
//      strip.show();
////      delay(delay_time);
//      delay(0.15 * (800 - pixel * (strip.numPixels() - pixel)));
//    }
//    color += color_step;
//  }
//}

static void set_roygbiv(Adafruit_NeoPixel& strip, unsigned int offset) {
  const unsigned int multiplier = (255 / strip.numPixels());
  for(unsigned int pixel = 0; pixel < strip.numPixels(); ++pixel) {
    strip.setPixelColor(pixel, wheel(((pixel + offset) % 46) * multiplier));
  }
}

static void roygbiv_cycle(Adafruit_NeoPixel& strip, unsigned int delay_time) {
  // Add green
  for (unsigned int green = 0; green < 256; ++green) {
    const uint32_t color = strip.Color(green, 255, 0);
    set_all(strip, color);
    strip.show();
    delay(delay_time);
  }
  // Remove red
  for (unsigned int red = 0; red < 256; ++red) {
    const uint32_t color = strip.Color(255, 255 - red, 0);
    set_all(strip, color);
    strip.show();
    delay(delay_time);
  }
  // Add blue
  for (unsigned int blue = 0; blue < 256; ++blue) {
    const uint32_t color = strip.Color(255, 0, blue);
    set_all(strip, color);
    strip.show();
    delay(delay_time);
  }
  // Remove green
  for (unsigned int green = 0; green < 256; ++green) {
    const uint32_t color = strip.Color(255 - green, 0, 255);
    set_all(strip, color);
    strip.show();
    delay(delay_time);
  }
  // Add red
  for (unsigned int red = 0; red < 256; ++red) {
    const uint32_t color = strip.Color(0, red, 255);
    set_all(strip, color);
    strip.show();
    delay(delay_time);
  }
  // Remove blue
  for (unsigned int blue = 0; blue < 256; ++blue) {
    const uint32_t color = strip.Color(0, 255, 255 - blue);
    set_all(strip, color);
    strip.show();
    delay(delay_time);
  }
}

uint32_t wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}

static void set_all(Adafruit_NeoPixel& strip, const uint32_t color) {
  for(unsigned int pixel; pixel < strip.numPixels(); ++pixel) {
    strip.setPixelColor(pixel, color);
  }
}

static void light_pot_chosen(Adafruit_NeoPixel& strip,
                             const unsigned int pot_pin) {
  // Turn off all pixels
  for (unsigned int i; i < strip.numPixels(); ++i) {
    strip.setPixelColor(i, 0);
  }
  
  // Find pixel pot is selecting
  const unsigned int num_readings = 10;
  unsigned int sum_pot_readings = 0;
  for (unsigned int i = 0; i < num_readings ; ++i) {
    sum_pot_readings += analogRead(pot_pin);
  }
  const unsigned int new_pixel = (sum_pot_readings / num_readings)
                                 / (667. / strip.numPixels() - 1);
  Serial.println(new_pixel);

  // Light new pixel
  strip.setPixelColor(new_pixel, 255, 0, 0);
  strip.show();
}

unsigned int pot_select(const unsigned int pot_pin,
                        const unsigned int maximum,
                        const unsigned int minimum) {
  const unsigned max_pot = 694;
  const unsigned int num_readings = 10;
  
  // Read pot
  unsigned int sum_pot_readings = 0;
  for (unsigned int i = 0; i < num_readings ; ++i) {
    sum_pot_readings += analogRead(pot_pin);
  }
  const float pot = sum_pot_readings / num_readings;

  return (pot / (float) max_pot) * (maximum - minimum) + minimum;
}

static void test_chase() {
  chase(strip.Color(255, 0, 0)); // Red
  chase(strip.Color(0, 255, 0)); // Green
  chase(strip.Color(0, 0, 255)); // Blue
}

static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      delay(25);
  }
}

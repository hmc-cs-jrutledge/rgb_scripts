#include "pond.h"

#define LED_PIN 6
#define NUM_LEDS 46
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define UPDATES_PER_SECOND 2

CRGB leds[NUM_LEDS];
Pond pond(leds, NUM_LEDS);

void setup() {
  delay(3000); // power-up safety delay
  
  randomSeed(analogRead(0));
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(
      TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  
  Serial.begin(9600);
}

void loop() {
  pond.step_animation();
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

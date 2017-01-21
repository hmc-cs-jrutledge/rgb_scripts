#include "FastLED.h"

#define POT_PIN A0

#define LED_PIN 6
#define NUM_LEDS 46
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 200

extern CRGBPalette16 halloween_palette;
extern const TProgmemPalette16 halloween_palette_p PROGMEM;

const CRGB purple = CHSV(HUE_PURPLE, 255, 255);
const TProgmemPalette16 halloween_palette_p PROGMEM = {
    CRGB::DarkOrchid,
    CRGB::Black,
    CRGB::DarkOrange,
    CRGB::Black,
    CRGB::DarkOrchid,
    CRGB::Black,
    CRGB::DarkOrange,
    CRGB::Black,
    CRGB::DarkOrchid,
    CRGB::Black,
    CRGB::DarkOrange,
    CRGB::Black,
    CRGB::DarkOrchid,
    CRGB::Black,
    CRGB::DarkOrange,
    CRGB::Black
};


const CRGB green = CHSV(HUE_PURPLE, 255, 255);
const CRGB red = CHSV(HUE_PURPLE, 255, 255);
const TProgmemPalette16 christmas_palette_p PROGMEM = {
    CRGB::Green,
    CRGB::Red,
    CRGB::Green,
    CRGB::Red,
    CRGB::Green,
    CRGB::Red,
    CRGB::Green,
    CRGB::Red,
    CRGB::Green,
    CRGB::Red,
    CRGB::Green,
    CRGB::Red,
    CRGB::Green,
    CRGB::Red,
    CRGB::Green,
    CRGB::Red
};

void setup() {
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(
      TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  CRGB purple = CHSV(HUE_PURPLE, 255, 255);
  CRGB orange = CRGB::DarkOrange;
}

void loop() {
  static uint8_t start_index = 0;
  ++start_index;
  
  static const uint8_t DotsPerUpdate = 8;
  fadeToBlackBy(leds, NUM_LEDS, 1);
  EVERY_N_MILLISECONDS(200) {
    for(uint8_t i; i < DotsPerUpdate; ++i) {
      confetti(christmas_palette_p, NOBLEND, start_index);
    }
    addGlitter(80);
  } 
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

// Double Swing
//void loop() {
//  static uint8_t start_index = 0;
//  ++start_index;
//  
//  fadeToBlackBy(leds, NUM_LEDS, 20);
//  int pos = beatsin8(13, 0, NUM_LEDS - 1);
//  leds[pos] = CHSV(HUE_PURPLE, 255, 255);
//  leds[NUM_LEDS - pos - 1] = CRGB::DarkOrange;
//  FastLED.show();
//  FastLED.delay(1000 / UPDATES_PER_SECOND);
//}

void confetti(
      const CRGBPalette16& palette, const TBlendType& blending, uint8_t color_index){
  uint8_t brightness = 255;
  fadeToBlackBy(leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] = ColorFromPalette(palette, random8(), brightness, blending);
}

void addGlitter(fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] = CRGB(56, 228, 255);
  }
}

void fillLEDsFromPaletteColors(
      const CRGBPalette16& palette, const TBlendType& blending, uint8_t color_index){
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette(palette, color_index, brightness, blending);
        color_index += 3;
    }
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

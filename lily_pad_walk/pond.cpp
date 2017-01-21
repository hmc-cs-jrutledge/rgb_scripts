/**
 * \file pond.h
 *
 * \author Jeffrey Rutledge jeff_rutledge@icloud.com
 *
 * \brief For a string of singly addressable RGB LEDS.
 * Simulates a frog jumping back and forth in a pond.
 *
 * \detail The frog starts on the first of eleven lily pads.
 * If the frog makes it to the tenth lily pad then it escapes the pond.
 * If the frog makes it to the zeroth lily pad then it is eaten by a snake.
 * The probability the frog jumps backward is the number of the lily pad it is
 * on divided by ten.
 * If the frog doesn't jump backwards, then it jumps forward.
 */

#include "pond.h"

Pond::Pond(CRGB* led_strip, const size_t num_leds)
    : NUM_LEDS_(num_leds), PAD_SIZE_(NUM_LEDS_ / 11), led_strip_(led_strip),
      frog_position_(1), times_escaped_(0), times_died_(0) {}

void Pond::step_animation() {
  if (frog_position_ == 0) {                // Frog died
    ++times_died_;
    show_death();
    frog_position_ = 1; // reset position
  } else if (frog_position_ == 10) {        // Frog escaped
    ++times_escaped_;
    show_escape();
    frog_position_ = 1; // reset position
  } else { // Frog trapped
    jump();
    draw_pond();
  }
}

double Pond::percent_of_deaths() const {
  return times_died_ / (double) (times_escaped_ + times_died_);
}

void Pond::jump() {
  // Check frog hasn't already died or escaped
  // assert(frog_position_ != 0 && frog_position_ != 10)

  // Decide if the frog jumps forward
  if (random(1, 11) > frog_position_) {
    ++frog_position_;
  } else {
    --frog_position_;
  }
}

void Pond::draw_pond() {
  clear_strip();
  // draw death pad, pad 0
  color_pad(0, CRGB::Red);
  // draw surviving pad, pad 10
  color_pad(10, CRGB::Blue);
  // draw frog
  color_pad(frog_position_, CRGB::Green);
}

void Pond::show_death() {
  // fill with red from death pad
  for (size_t led = 0; led < num_pond_leds(); ++led) {
    led_strip_[led] = CRGB::Red;
    FastLED.show();
    FastLED.delay(SWEEP_DELAY);
  }
  // fill with blue to score from escape pad
  double percentage_escaped = times_escaped_ / (double) (times_escaped_ + times_died_);
  size_t num_escaped_leds = percentage_escaped * num_pond_leds();
  for (size_t led = 0; led < num_escaped_leds; ++led) {
    led_strip_[num_pond_leds() - led] = CRGB::Blue;
    FastLED.show();
    FastLED.delay(SWEEP_DELAY);
  }
  FastLED.delay(2000);
}

void Pond::show_escape() {
  // fill with blue from escape pad
  for (size_t led = 0; led < num_pond_leds(); ++led) {
    led_strip_[num_pond_leds() - led] = CRGB::Blue;
    FastLED.show();
    FastLED.delay(SWEEP_DELAY);
  }
  // fill with blue to score from escape pad
  double percentage_died = times_died_ / (double) (times_escaped_ + times_died_);
  size_t num_death_leds = percentage_died * num_pond_leds();
  for (size_t led = 0; led < num_death_leds; ++led) {
    led_strip_[led] = CRGB::Red;
    FastLED.show();
    FastLED.delay(SWEEP_DELAY);
  }
  FastLED.delay(2000);
}
  
size_t Pond::num_leds() const {
  return NUM_LEDS_;
}

void Pond::clear_strip() {
  for (size_t led = 0; led < NUM_LEDS_; ++led) {
    led_strip_[led] = CRGB::Black;
  }
}

void Pond::color_pad(const size_t pad, const CRGB& color) {
  for (size_t pad_led = 0; pad_led < PAD_SIZE_; ++pad_led) {
    led_strip_[pad * PAD_SIZE_ + pad_led] = color;
  }
}

size_t Pond::num_pond_leds() {
  return PAD_SIZE_ * 11;
}

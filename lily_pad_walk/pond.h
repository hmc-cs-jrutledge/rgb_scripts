/**
 * \file pond.h
 *
 * \author Jeffrey Rutledge jeff_rutledge@icloud.com
 *
 * \brief For a string of singly addressable RGB LEDs.
 * Simulates a frog jumping back and forth in a pond.
 *
 * \detail The frog starts on the first of eleven lily pads.
 * If the frog makes it to the tenth lily pad then it escapes the pond.
 * If the frog makes it to the zeroth lily pad then it is eaten by a snake.
 * The probability the frog jumps backward is the number of the lily pad it is
 * on divided by ten.
 * If the frog doesn't jump backwards, then it jumps forward.
 */

#ifndef POND_H
#define POND_H

#include <stddef.h>

#include "FastLED.h"

#define SWEEP_DELAY 100
class Pond {
 public:
  /**
   * \brief Parameterized constructor of a pond.
   * \param num_leds number of LEDs in the strip.
   */
  Pond(CRGB* led_strip, const size_t num_leds);
  void step_animation();
  size_t num_leds() const;
  double percent_of_deaths() const;

 private:
  void jump();
  void draw_pond();
  void show_death();
  void show_escape();
  void color_pad(const size_t pad_number, const CRGB& color);
  void clear_strip();
  size_t num_pond_leds();

  const size_t NUM_LEDS_;
  const size_t PAD_SIZE_;
  CRGB* led_strip_;
  size_t frog_position_;
  size_t times_escaped_;
  size_t times_died_;
};

#endif // POND_H

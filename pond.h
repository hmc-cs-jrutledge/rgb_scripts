/**
 * \file pond.h
 *
 * \author Jeffrey Rutledge jeff_rutledge@icloud.com
 *
 * \brief For a string of singly addressable RGB LEDS.
 * Simulates a frog jumping back and forth in a pond.
 *
 * \detail The frog starts on the middle of eleven lily pads.
 * If the frog makes it to the tenth lily pad then it escapes the pond.
 * If the frog makes it to the zeroth lily pad then it is eaten by a snake.
 * The probability the frog jumps backward is the number of the lily pad it is
 * on divided by ten.
 * If the frog doesn't jump backwards, then it jumps forward.
 */

#ifndef POND_H
#define POND_H

int add_one(int number) {
  return number + 1;
}

#endif // POND_H

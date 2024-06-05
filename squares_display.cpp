#include "config.h"
#include "squares_display.h"
#include "squares.h"
#include "Arduino.h"

/**
* Sets up the squares
*/
void sqrs_display_setup() {
  sqrs_setup();
}

/**
* Lights a specified square in a specified color
*
* @param sqr_idx specifies which square to light
* @param color specifies what color to light the square with
*/
void light_sqr(uint8_t sqr_idx, sw_colors color) {
  light_sqr_leds(sqr_idx, color);
}

/**
* Tests is all the squares are working
*/
void test_sqrs() {
  shut_all_sqrs();
  for (int i = 0; i < 9; i++) {
    light_sqr_leds(i, Blue);
    delay(1000);
    shut_sqr(i);
  }
}

/**
* Lights a square in the color of player 1
*
* @param sqr_idx specifies which square to light
*/
void light_player_1_sqr(uint8_t sqr_idx) {
  light_sqr_leds(sqr_idx, PLAYER_1_COLOR);
}

/**
* Lights a square in the color of player 2
*
* @param sqr_idx specifies which square to light
*/
void light_player_2_sqr(uint8_t sqr_idx) {
  light_sqr_leds(sqr_idx, PLAYER_2_COLOR);
}

/**
* Shuts off a specified square
*
* @param sqr_idx specifies which square to shut off
*/
void shut_sqr(uint8_t sqr_idx) {
  light_sqr(sqr_idx, Black);
}

/**
* Lights all squars in a specified color
*
* @param color specifies what color
*/
void light_all_sqrs(sw_colors color) {
  uint8_t i;
  for (i = 0; i < NUM_OF_SQUARES; i++) {
    light_sqr(i, color);
  }
}

/**
* Shuts off all squares
*/
void shut_all_sqrs() {
  light_all_sqrs(Black);
}
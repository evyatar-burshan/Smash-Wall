#include "config.h"
#include "squares.h"
#include "leds_ctrl.h"
#include "Arduino.h"

/**
* Sets up the squares
*/
void sqrs_setup() {
  sqrs_leds_setup();
}

/**
* Lights all leds in a specified square in a specified color
*
* @param sqr_idx specifies which square to light
* @param color specifies what color to light the square with
*/
void light_sqr_leds(uint8_t sqr_idx, sw_colors color) {
  fill_sqr_leds(sqr_idx, color);
  refesh_sqr_leds(sqr_idx);
}

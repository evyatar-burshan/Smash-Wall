#include <FastLED.h>
#include "config.h"
#include "leds_ctrl.h"

CRGB digits_raw_leds[TOTAL_DIGITS_LEDS_NUM];
CRGBSet digits_leds(digits_raw_leds, TOTAL_DIGITS_LEDS_NUM);
struct CRGB *digits[NUM_OF_DIGITS];
CLEDController *digits_leds_ctrl;

CRGB sqrs_raw_leds[TOTAL_SQUARES_LEDS_NUM];
CRGBSet sqrs_leds(sqrs_raw_leds, TOTAL_DIGITS_LEDS_NUM);
struct CRGB *sqrs[NUM_OF_SQUARES];
CLEDController *sqrs_leds_ctrl[NUM_OF_SQRS_COLS];

uint8_t gBrightness = 128;

/**
* Sets up the leds in all 3 columns of squares
*/
void sqrs_leds_setup() {
  uint8_t i;

  sqrs_leds_ctrl[0] = &FastLED.addLeds<WS2812, SQRS_COL_0_PIN>(sqrs_raw_leds, 0, NUM_OF_LEDS_IN_SQUARES_COLUMN);
  sqrs_leds_ctrl[1] = &FastLED.addLeds<WS2812, SQRS_COL_1_PIN>(sqrs_raw_leds, NUM_OF_LEDS_IN_SQUARES_COLUMN, NUM_OF_LEDS_IN_SQUARES_COLUMN);
  sqrs_leds_ctrl[2] = &FastLED.addLeds<WS2812, SQRS_COL_2_PIN>(sqrs_raw_leds, 2 * NUM_OF_LEDS_IN_SQUARES_COLUMN, NUM_OF_LEDS_IN_SQUARES_COLUMN);


  for (i = 0; i < NUM_OF_SQUARES; i++) {
    sqrs[i] = CRGBSet(sqrs_leds(i * NUM_OF_LEDS_IN_SQUARE, (i + 1) * NUM_OF_LEDS_IN_SQUARE - 1));
  }
  FastLED.setMaxPowerInVoltsAndMilliamps(5, LEDS_MAX_CURRENT_IN_mA_UNITS);
}

/**
* Sets up the leds in the info display's digit
*/
void digits_leds_setup() {
  uint8_t i;

  digits_leds_ctrl = &FastLED.addLeds<WS2812, DIGITS_PIN, GRB>(digits_raw_leds, TOTAL_DIGITS_LEDS_NUM);
  for (i = 0; i < NUM_OF_DIGITS; i++) {
    digits[i] = CRGBSet(digits_leds(i * NUM_OF_LEDS_IN_DIGIT, (i + 1) * NUM_OF_LEDS_IN_DIGIT - 1));
  }

  FastLED.setMaxPowerInVoltsAndMilliamps(5, LEDS_MAX_CURRENT_IN_mA_UNITS);
}

/**
* Fills (lights) the leds in a specified digit in a specified length in a specified color
*
* @param digit_idx Specifies what digit the leds are in
* @param start Specifies how much leds to skip of that specified digit
* @param len Specifies how many leds to light
* @param color Specifies what color to light the leds with
*/
void fill_digit_leds(uint8_t digit_idx, uint8_t start, uint8_t len, sw_colors color) {
  fill_solid(digits[digit_idx] + start, len, color);
}

/**
* Erez Help
*/
void refresh_digits_leds() {
  digits_leds_ctrl->showLeds(gBrightness);
}

/**
* Fills (lights) the leds of a specifies square in a specified color
*
* @param sqr_idx Specifies which square's leds to light
* @param color Spcifies what color to light the leds with
*/
void fill_sqr_leds(uint8_t sqr_idx, sw_colors color) {
  fill_solid(sqrs[sqr_idx], NUM_OF_LEDS_IN_SQUARE, color);
}

/**
* Erez Help
*
* @param sqr_idx
*/
void refesh_sqr_leds(uint8_t sqr_idx) {
  uint8_t col = sqr_idx / NUM_OF_SQRS_COLS;
  sqrs_leds_ctrl[col]->showLeds(gBrightness);
}

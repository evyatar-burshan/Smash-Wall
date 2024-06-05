#ifndef LEDS_CTRL_H
#define LEDS_CTRL_H

void digits_leds_setup();
void sqrs_leds_setup();

void fill_digit_leds(uint8_t digit_idx, uint8_t start, uint8_t len, sw_colors color);
void leds_setup();
void refresh_digits_leds();

void fill_sqr_leds(uint8_t sqr_idx, sw_colors color);
void refesh_sqr_leds(uint8_t sqr_idx);

#endif

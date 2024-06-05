#include "config.h"
#include "digits.h"
#include "leds_ctrl.h"
#include "ctype.h"
#include "arduino.h"

#define ON 1
#define OFF 0

// Defines the order of which the reverse welded digits are welded
int const reverse_digit_segments[7] = { 4, 5, 6, 3, 0, 1, 2 };
int const reverse_digit_half_segments[14] = { 8, 9, 10, 11, 12, 13, 6, 7, 0, 1, 2, 3, 4, 5 };

//Defines which segments to light for each English letter
bool const letters_segment_config[26][NUM_OF_SEGMENTS] = {
  { ON, OFF, ON, ON, ON, ON, ON },      //A
  { ON, ON, ON, ON, OFF, OFF, ON },     //b
  { ON, ON, OFF, OFF, ON, ON, OFF },    //C
  { ON, ON, ON, ON, OFF, OFF, ON },     //d
  { ON, ON, OFF, ON, ON, ON, OFF },     //E
  { ON, OFF, OFF, ON, ON, ON, OFF },    //F
  { ON, ON, ON, OFF, ON, ON, OFF },     //G
  { ON, OFF, ON, ON, ON, OFF, ON },     //H
  { ON, OFF, OFF, OFF, ON, OFF, OFF },  //I
  { OFF, ON, ON, OFF, OFF, OFF, ON },   //J
  { ON, OFF, ON, ON, ON, ON, OFF },     //K
  { ON, ON, OFF, OFF, ON, OFF, OFF },   //L
  { OFF, ON, OFF, OFF, ON, ON, ON },    //m
  { ON, OFF, ON, ON, OFF, OFF, OFF },   //n
  { ON, ON, ON, ON, OFF, OFF, OFF },    //o
  { ON, OFF, OFF, ON, ON, ON, ON },     //P
  { OFF, OFF, ON, ON, ON, ON, ON },     //q
  { ON, OFF, OFF, ON, OFF, OFF, OFF },  //r
  { OFF, ON, ON, ON, ON, ON, OFF },     //S
  { ON, ON, OFF, ON, ON, OFF, OFF },    //t
  { ON, ON, ON, OFF, ON, OFF, ON },     //U
  { ON, ON, ON, OFF, OFF, OFF, OFF },   //v
  { ON, ON, ON, ON, ON, OFF, ON },      //w
  { OFF, ON, OFF, ON, OFF, ON, OFF },   //X
  { OFF, ON, ON, ON, ON, OFF, ON },     //y
  { ON, ON, OFF, ON, OFF, ON, ON }      //Z
};

//Defines which half-segments to light for each Hebrew letter
bool const hebrew_segment_config[27][NUM_OF_SEGMENTS * 2] = {
  { ON, OFF, OFF, OFF, ON, ON, ON, ON, ON, ON, OFF, OFF, OFF, ON },        //א0
  { OFF, OFF, ON, ON, ON, ON, OFF, OFF, OFF, OFF, ON, ON, ON, ON },        //ב1
  { ON, ON, OFF, OFF, ON, ON, ON, ON, OFF, OFF, ON, ON, ON, ON },          //ג2
  { OFF, OFF, OFF, OFF, ON, ON, ON, ON, OFF, OFF, OFF, OFF, OFF, ON },     //ד3
  { OFF, ON, OFF, OFF, ON, ON, ON, ON, OFF, OFF, OFF, OFF, OFF, OFF },     //ה4
  { OFF, OFF, OFF, OFF, ON, ON, ON, OFF, OFF, OFF, OFF, OFF, OFF, OFF },   //ו5
  { OFF, OFF, OFF, OFF, ON, ON, ON, OFF, OFF, OFF, OFF, OFF, OFF, ON },    //ז6
  { ON, ON, OFF, OFF, ON, ON, ON, ON, OFF, OFF, OFF, OFF, OFF, OFF },      //ח7
  { ON, ON, ON, ON, ON, ON, OFF, OFF, ON, ON, OFF, ON, ON, ON },           //ט8
  { OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, ON, ON, OFF },  //9'
  { OFF, OFF, OFF, OFF, ON, ON, OFF, OFF, OFF, OFF, ON, ON, ON, ON },      //ך10
  { OFF, OFF, ON, ON, ON, ON, ON, ON, OFF, OFF, OFF, OFF, OFF, OFF },      //כ11
  { OFF, OFF, ON, ON, ON, ON, ON, ON, ON, ON, OFF, OFF, OFF, OFF },        //ל12
  { ON, ON, ON, ON, ON, ON, ON, ON, ON, OFF, OFF, OFF, OFF, OFF },         //ם13
  { ON, ON, OFF, ON, ON, ON, ON, ON, ON, OFF, OFF, OFF, OFF, OFF },        //מ14
  { OFF, OFF, OFF, OFF, ON, ON, OFF, OFF, OFF, OFF, OFF, ON, ON, ON },     //ן15
  { OFF, OFF, ON, ON, ON, ON, OFF, OFF, OFF, OFF, OFF, ON, ON, ON },       //נ16
  { ON, ON, ON, ON, ON, ON, ON, ON, OFF, OFF, OFF, OFF, OFF, OFF },        //ס17
  { OFF, OFF, ON, ON, ON, ON, ON, ON, OFF, OFF, OFF, OFF, ON, ON },        //ע18
  { OFF, OFF, OFF, OFF, ON, ON, OFF, ON, ON, ON, ON, ON, ON, ON },         //ף19
  { OFF, OFF, ON, ON, ON, ON, OFF, ON, ON, ON, ON, ON, ON, ON },           //פ20
  { ON, ON, OFF, OFF, OFF, OFF, ON, ON, ON, ON, OFF, OFF, ON, ON },        //ץ21
  { OFF, OFF, ON, ON, ON, ON, ON, ON, ON, ON, OFF, OFF, ON, ON },          //צ22
  { ON, ON, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, ON, ON, ON, ON },      //ק23
  { OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, ON, ON, ON, ON },    //ר24
  { ON, ON, ON, ON, ON, ON, OFF, OFF, ON, ON, OFF, OFF, ON, ON },          //ש25
  { ON, ON, OFF, OFF, ON, ON, OFF, OFF, ON, ON, ON, ON, ON, ON },          //ת26
};

/*
#define a   0 // bottom left |
#define b   1 // bottom _
#define c   2 // bottom right |
#define d   3 // middle _
#define e   4 // top left |
#define f   5 // top _
#define g   6 // top right |
*/

//Defines which segments to light for each number
bool const number_segment_config[10][NUM_OF_SEGMENTS] = {
  { ON, ON, ON, OFF, ON, ON, ON },      //0
  { OFF, OFF, ON, OFF, OFF, OFF, ON },  //1
  { ON, ON, OFF, ON, OFF, ON, ON },     //2
  { OFF, ON, ON, ON, OFF, ON, ON },     //3
  { OFF, OFF, ON, ON, ON, OFF, ON },    //4
  { OFF, ON, ON, ON, ON, ON, OFF },     //5
  { ON, ON, ON, ON, ON, ON, OFF },      //6
  { OFF, OFF, ON, OFF, OFF, ON, ON },   //7
  { ON, ON, ON, ON, ON, ON, ON },       //8
  { OFF, ON, ON, ON, ON, ON, ON }       //9
};

/**
* Sets up the info display's digits
*/
void digits_setup() {
  digits_leds_setup();
}

/**
* Changes a specified segment in a specified digit to a specified state (ON/OFF) and a specified color
*
* @param digit_idx Specifies which digit the segment is in
* @param state Specifies if the segment should be ON or OFF
* @param segment Specifies which segment to change in the specified digit
* @param color Specifies which color to light the segment with
*/
void static set_segment(uint8_t digit_idx, uint8_t state, uint8_t segment, sw_colors color) {
  uint8_t start = segment * NUM_OF_LEDS_IN_SEGMENT;

  if (state == OFF)
    color = Black;
  fill_digit_leds(digit_idx, start, NUM_OF_LEDS_IN_SEGMENT, color);
}

/**
* Lights a specified digit with a specified English letter in a specified color
*
* @param digit_idx Specifies which digit to light
* @param letter Specifies what Wnglish letter to light the digit with
* @param color Specifies what color to light the letter with
*/
void set_digit_letter(uint8_t digit_idx, uint8_t letter, sw_colors color) {
  uint8_t i;
  for (i = 0; i < 7; i++) {
    int counter = reverse_digit_segments[i];
    if (digit_idx == 2 || digit_idx == 4 || digit_idx == 6) {
      set_segment(digit_idx, letters_segment_config[toupper(letter) - 'A'][i], counter, color);
    } else {
      set_segment(digit_idx, letters_segment_config[toupper(letter) - 'A'][i], i, color);
    }
  }
}

/**
* Changes a specified half segment in a specified digit to a specified state (ON/OFF) and a specified color
*
* @param digit_idx Specifies which digit the half segment is in
* @param state Specifies if the half segment should be ON or OFF
* @param half_segment Specifies which half segment to change in the specified digit
* @param color Specifies which color to light the half segment with
*/
void static set_half_segment(uint8_t digit_idx, uint8_t state, uint8_t half_segment, sw_colors color) {
  uint8_t start = half_segment * (NUM_OF_LEDS_IN_SEGMENT / 2);

  if (state == OFF)
    color = Black;
  fill_digit_leds(digit_idx, start, (NUM_OF_LEDS_IN_SEGMENT / 2), color);
}

/**
* Lights a specified digit with a specified Hebrew letter in a specified color
*
* @param digit_idx Specifies which digit to light
* @param letter Specifies what Hebrew letter to light the digit with
* @param color Specifies what color to light the letter with
*/
void set_digit_hebrew_letter(uint8_t digit_idx, uint8_t letter, sw_colors color) {
  uint8_t i;
  for (i = 0; i < 14; i++) {
    int counter = reverse_digit_half_segments[i];
    if (digit_idx == 2 || digit_idx == 4 || digit_idx == 6) {
      Serial.println((int)letter - 144);
      set_half_segment(digit_idx, hebrew_segment_config[letter][i], counter, color);
    } else {
      set_half_segment(digit_idx, hebrew_segment_config[(int)letter - 144][i], i, color);
    }
  }
}

/**
* Displays a specified number in a specified digit in a specified color
*
* @param digit_idx Specifies which digit to light the number with
* @param num Specifies which number to light the digit with
* @param color Specifies what color to light the digit with
*/
void set_digit_num(uint8_t digit_idx, uint8_t num, sw_colors color) {
  uint8_t i;
  for (i = 0; i < 7; i++) {
    int counter = reverse_digit_segments[i];
    if (digit_idx == 2 || digit_idx == 4 || digit_idx == 6) {
      set_segment(digit_idx, number_segment_config[num][counter], i, color);
    } else {
      set_segment(digit_idx, number_segment_config[num][i], i, color);
    }
  }
}

/**
* Turns off a specified digit
*
* @param digit_idx Specifies which digit to turn off
*/
void turn_off_digit(uint8_t digit_idx) {
  fill_digit_leds(digit_idx, 0, NUM_OF_LEDS_IN_DIGIT, Black);
}

/**
* Refreshes the digits
*/
void refresh_digits() {
  refresh_digits_leds();
}
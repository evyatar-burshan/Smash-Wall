#include "config.h"
#include "sensors.h"
#include "arduino.h"
#include "squares_display.h"

#define NO_HIT 10

uint8_t sensor_pins[] = { 54, 55, 56, 57, 58, 59, 60, 61, 62 };
int sensors_read[NUM_OF_SENSORS];
void test_sensors_light_hited();
void test_sensors_shut_sqr_on_hit();

void sensors_setup() {
  //analogReference(EXTERNAL); // use AREF for reference voltage
}

/**
* Returns the output value of a specified sensor
*
* @param i Specifies which sensor to read
* @return the value of the specified sensor
*/
uint8_t get_sensor_read(int i) {
  delay(10);
  analogRead(sensor_pins[i]);
  delay(10);
  int res = analogRead(sensor_pins[i]);
  return res;
}

/**
* Checks if a specified sensor was hit and returns true or false
*
* @param target_sensor specifies which sensor was hit
* @return if the specified sensor was hit
*/
bool sensor_was_hit(uint8_t target_sensor) {

  int hit_sensor = get_hitted_sensor();
  if (hit_sensor == target_sensor)
    return true;
  return false;
}

/**
* Returns the sensor with the highest output, the one that was hit
*
* @return which sensor was hit
*/
uint8_t get_hitted_sensor() {
  uint8_t i;
  int max_val = 0;
  uint8_t max_idx = 0;
  //loop over sensors and find max value
  for (i = 0; i < NUM_OF_SENSORS; i++) {
    sensors_read[i] = get_sensor_read(i);
    if (sensors_read[i] > max_val) {
      max_val = sensors_read[i];
      max_idx = i;
    }
  }
  //if over the threshold return index
  if (max_val > HIT_SENSE_THRESHOLD_READ) {
    return max_idx;
  } else {
    return NO_HIT;
  }
}

/**
* Reads all the sensors outputs
*/
void read_sensors() {
  uint8_t i;

  //loop over sensors
  for (i = 0; i < NUM_OF_SENSORS; i++) {
    sensors_read[i] = get_sensor_read(i);
  }
}

/**
* Prints all the sensors outputs
*/
void print_sensors() {
  Serial.println();
  //loop over sensors
  for (int i = 0; i < NUM_OF_SENSORS; i++) {
    Serial.print(get_sensor_read(i));
    Serial.print(", ");
  }
  Serial.println();
}

/**
* Tests the sensors by running a speecified sensor test
*
* @param test_type Specifies what test to run on the sensors
*/
void test_sensors(uint8_t test_type) {
  if (test_type == LIGHT_ON_HIT) {
    test_sensors_light_hited();
    return;
  }
  if (test_type == LIGHT_AND_SHUT_ON_HIT) {
    test_sensors_shut_sqr_on_hit();
    return;
  }
  return;
}

/**
* @brief Tests the sensors
* Tests the sensors by checking what sensor the player hit and lighting that square
*/
void test_sensors_light_hited() {
  int hit_sensor_idx;
  for (int i = 0; i < TEST_SENSORS_LIGHT_HIT_CYCLES; i++) {
    hit_sensor_idx = NO_HIT;
    shut_all_sqrs();
    while (hit_sensor_idx == NO_HIT) {
      hit_sensor_idx = get_hitted_sensor();
      delay(10);
    }
    light_sqr(hit_sensor_idx, Blue);
    delay(1500);
  }
}

/**
* @brief Tests the sensors
* Tests the sensors by lighting a square, waiting for the player to hit that square's sensor and moving to the next square
*/
void test_sensors_shut_sqr_on_hit() {
  int hit_sensor_idx;
  shut_all_sqrs();
  for (int i = 0; i < NUM_OF_SENSORS; i++) {
    hit_sensor_idx = NO_HIT;
    light_sqr(i, Blue);
    delay(500);
    while (true) {
      while (hit_sensor_idx == NO_HIT) {
        hit_sensor_idx = get_hitted_sensor();
        delay(10);
      }

      if (hit_sensor_idx == i) {
        shut_sqr(i);
        break;
      }
    }
  }
}
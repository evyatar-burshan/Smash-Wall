#ifndef SENSORS_H
#define SENSORS_H

void sensors_setup();
bool sensor_was_hit(uint8_t target_sensor);
uint8_t get_hitted_sensor();
void read_sensors();
uint8_t get_sensor_read(int i);
void print_sensors();
void light_strongest();
void test_sensors(uint8_t test_type);

#endif
#ifndef FUCTION_H
#define FUNCTION_H

int normalize_throttle(int value);

int16_t convert_throttle_to_pulse(const String &thrust);

void write_motor_speed(Servo &motor, uint16_t pulse, float weight);

void ble_config();

void motors_config();

#endif
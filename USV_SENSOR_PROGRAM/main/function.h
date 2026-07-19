/**
 * @file function.h
 * @brief Implementação dos prótotipos de função.
 *
 * @author Ygor Dassaev
 * @date 18/07/2026
 * @version 1.0
 *
 * @details
 * Este arquivo contém os prótotipos de funções do sistema.
 *
 */


#ifndef FUCTION_H
#define FUCTION_H

uint16_t __read_adc(uint8_t adc_channel);

float read_turbidity_sensor();

float read_ph_sensor();

bool __one_wire_read(OneWire &ds, uint8_t *addr, uint8_t command, uint8_t *buffer, uint8_t size);

float read_temperature_sensor();

void gps_configuration();

void ble_configuration();

void read_gps(Gps_Data_t *gpsData);

void read_sensors(Sensors_Data_t *dados);

void gpios_configuration();

void send_data(Sensors_Data_t *dados);

#endif
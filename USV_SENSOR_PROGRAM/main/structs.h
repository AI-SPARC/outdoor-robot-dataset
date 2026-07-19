/**
* @file structs.h
 * @brief Implementação das estruturas 
 *
 * @author Ygor Dassaev
 * @date 18/07/2026
 * @version 1.0
 *
 * @details
 * Este arquivo contém as estruturas que armazenam dados das operações.
 *
 */


#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum {
	READ_SENSORS = 0,
	SEND_DATA,
	UPDATE_WATCHDOG,

	TOTAL_CASES_STATE_MACHINE
  }state_machice_cases;

typedef struct{
	float latitude;
	float longitude;
}Gps_Data_t;

typedef struct {
	float turbidity;
	float ph;
	float temperature;
	Gps_Data_t gps;

}Sensors_Data_t;

#endif
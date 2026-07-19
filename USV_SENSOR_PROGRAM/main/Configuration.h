/**
 * @file Configuration.ino
 * @brief Criação da macros de configuração do sistema.
 *
 * @author Ygor Dassaev
 * @date 18/07/2026
 * @version 1.0
 *
 * @details
 * Este arquivo contém as macros que abstraem os números mágicos.
 *
 */


#ifndef CONFIGURATION_H
#define CONFIGURATION_H

/**
* @brief Pino de transmissão de dados para o GPS.
*/
#define GPS_TXD 11

/**
* @brief Pino de Recepção de dados do GPS.
*/
#define GPS_RXD 12

/**
* @brief Taxa de transmissão de dados do GPS.
*/
#define GPS_BAUDRATE 9600

/**
* @brief Número de casas decimais dos dados de latitude e longitude.
*/
#define GPS_DATA_NUMBRE_DECIMAL_PLACES 6

/**
* @brief 
*/
#define GPS_TIMEOUT 100

/**
* @brief Pino de transmissão de dados para o bluetooth.
*/
#define BLE_TXD 3

/**
* @brief Pino de recepção de dados para o bluetooth.
*/
#define BLE_RXD 2

/**
* @brief Taxa de transmissão de dados do bluetooth.
*/
#define BLE_BAUDRATE 115200

/**
* @brief
*/
#define BLE_TIMEOUT 50

/**
* @brief Taxa de transmissão da serial.
*/
#define SERIAL_BAUDRATE 9600

/**
* @brief Pino analogico do sensor de temperatura.
*/
#define TEMPERATURE_SENSOR A0

/**
* @brief Pino analogico do sensor de turbidez.
*/
#define TURBIDITY_SENSOR A1

/**
* @brief Pino analogico do sensor de pH.
*/
#define PH_SENSOR A2

/**
* @brief Pino digital do led embarcado do arduino.
*/
#define LED_ONBOARD 13

/**
* @brief Resolução do ADC do arduino.
*/
#define ADC_RESOLUTION 1024.0

/**
* @brief Tensão de referencia do arduino.
*/
#define VREF 5.0

/**
* @brief Representa erro de leitura dos sesnores.
*/
#define SENSOR_VALOR_ERROR -1

/**
* @brief Delay de mil milissegundos.
*/
#define MIL_MILISSEGUNDOS 1000 

/**
* @brief Separador do pacote de dados.
*/
#define SEPARATOR ";"

/**
* @brief Termo quadratico da equação de turbidez.
*/
#define QUADRATIC_TERM -1120.04

/**
* @brief Termo quadratico da equação de turbidez.
*/
#define LINEAR_TERM 5742.3

/**
* @brief Termo constante da equação de turbidez.
*/
#define CONSTANT_TERM 4352.9

#endif
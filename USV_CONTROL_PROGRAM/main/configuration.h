#ifndef CONFIGURATION_H
#define CONFIGURATION_H

/**
* @brief Pino de transmissão dos dados bluetooth.
*/
#define BLE_TXD 3

/**
* @brief Pino de recepção dos dados bluetooth.
*/
#define BLE_RXD 2

/**
* @brief Taxa de transmissão de dados da comunicação bluetooth.
*/
#define BLE_BAUDRATE 9600

/**
* @brief Pino digital que envia sinal para o esc responsavel pelo motor esquerdo.
*/
#define ESC_LEFT_PIN 4

/**
* @brief Pino digital que envia sinal para o esc responsavel pelo motor direito.
*/
#define ESC_RIGHT_PIN 8

/**
* @brief Taxa de transmissão de dados da comunicação serial.
*/
#define SERIAL_BAUDRATE 9600

/**
* @brief Separador dos comandos recebidos.
*/
#define COMMAND_SEPARATOR ';'

/**
* @brief Parametro de calibração do sentido horario.
*/
#define WEIGHT_CW 1.0

/**
* @brief Parametro de calibração do sentido anti-horario.
*/
#define WEIGHT_CCW 1.0

/**
* @brief Pulso minimo do motor.
*/
#define MINIMAL_PULSE_RATE 1000

/**
* @brief Pulso maximo do motor.
*/
#define MAXIMUM_PULSE_RATE 2000

#endif
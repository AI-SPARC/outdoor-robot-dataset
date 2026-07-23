
#include "structs.h"

/**
* @brief Configura os parametros da comunicação bluetooth.
*/
void ble_config()
{
  bluetooth_Serial.begin(BLE_BAUDRATE);
  bluetooth_Serial.setTimeout(50);
}

/**
* @brief Configura os parametros do motor.
*/
void motors_config()
{
  left_motor.attach(ESC_LEFT_PIN, MINIMAL_PULSE_RATE, MAXIMUM_PULSE_RATE);
  right_motor.attach(ESC_RIGHT_PIN, MINIMAL_PULSE_RATE, MAXIMUM_PULSE_RATE);
}

/**
* @brief saturador, protege que os limites do motor sejam ultrapassados.
*
* @param Recebe um valor inteiro.
*/
int normalize_throttle(int value)
{
  if (value == 0 || value < -100)
    return -100;

  if (value > 100)
    return 100;

  return value;
}

/**
* @brief Converte a string recebida para um valor inteiro
*
* @param Valor recebido pela comunicação bluetooth.
*
* @return int16_t.
*/
int16_t convert_throttle_to_pulse(const String &thrust)
{
    int16_t velocity = thrust.toInt();

    velocity = normalize_throttle(velocity);

    return map(velocity, -100, 100, MINIMAL_PULSE_RATE,MAXIMUM_PULSE_RATE);
}

/**
* @brief Controla a velocidade de rotação do motor.
*
* @param Objeto servo, O pulso em microsegundos, Parametro de calibração dos motores.
*/
void write_motor_speed(Servo &motor, uint16_t pulse, float weight)
{
    motor.writeMicroseconds((uint16_t)(pulse * weight));
}

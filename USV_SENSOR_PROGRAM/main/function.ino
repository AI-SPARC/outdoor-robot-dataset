/**
 * @file function.ino
 * @brief Implementação das funções de leitura do conversor Analógico-Digital (ADC).
 *
 * @author Ygor Dassaev
 * @date 18/07/2026
 * @version 1.0
 *
 * @details
 * Este arquivo contém as funções do sistema.
 *
 */


#include "function.h"
#include "structs.h"

/**
 * @brief Realiza a leitura de um canal do conversor Analógico-Digital (ADC).
 *
 * Efetua a conversão analógico-digital no canal especificado e retorna
 * o valor lido.
 *
 * @param adc_channel Canal do ADC a ser lido.
 * @return uint16_t Valor convertido pelo ADC.
 */
uint16_t __read_adc(uint8_t adc_channel)
{
  return analogRead(adc_channel);
}

/**
* @brief Faz a leitura do sensor de turbidez.
*
* @return float valor convertido em NTU pela equação.
*/
float read_turbidity_sensor()
{
  float turbidity_sensor_data = 0;

  turbidity_sensor_data = __read_adc(A1) / ADC_RESOLUTION * VREF;

  if(turbidity_sensor_data >= 2.5)
  {
    //Converting voltage value into NTU value
    //https://www.dfrobot.com/wiki/index.php/File:Relationship_diagram.jpg
    turbidity_sensor_data=((QUADRATIC_TERM * (turbidity_sensor_data * turbidity_sensor_data)) + (LINEAR_TERM * turbidity_sensor_data)) - CONSTANT_TERM;
  }
  else
  {
    turbidity_sensor_data = SENSOR_VALOR_ERROR; // Display error
  }

  return turbidity_sensor_data;

}

/**
* @brief Faz a leitura do sensor de pH.
*
* @return float valor convertido em pH pela equação.
*/
float read_ph_sensor()
{
  float ph_sensor_data = 0;

  ph_sensor_data = __read_adc(A2) / ADC_RESOLUTION * VREF * 3.5;

  return ph_sensor_data;
}

bool __one_wire_read(OneWire &ds, uint8_t *addr, uint8_t command, uint8_t *buffer, uint8_t size)
{
    if (!ds.search(addr)) {
        ds.reset_search();
        return false;
    }

    if (OneWire::crc8(addr, 7) != addr[7]) {
        return false;
    }

    ds.reset();
    ds.select(addr);
    ds.write(command);

    for (uint8_t i = 0; i < size; i++) {
        buffer[i] = ds.read();
    }

    ds.reset_search();

    return true;
}

/**
* @brief Faz a leitura do sensor de temperatura.
*
* @return float valor convertido em Celsius pela equação.
*/
float read_temperature_sensor()
{
  uint8_t data[9];
  uint8_t addr[8];
  int16_t raw = 0;
  float temperatura = 0;

  // Inicia a conversão
  ds.search(addr);
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);
  ds.reset_search();

  // Lê o scratchpad
  if (__one_wire_read(ds, addr, 0xBE, data, 9))
  {
      raw = (data[1] << 8) | data[0];
      temperatura = raw / 16.0f;
  }

  return temperatura;
}

/**
* @brief Configura os parâmetros de operação do GPS.
*/
void gps_configuration()
{
  gps_serial.begin(GPS_BAUDRATE);
  gps_serial.setTimeout(GPS_TIMEOUT);
}

/**
* @brief Configura os parâmetros de operação do Bluetooth.
*/
void ble_configuration()
{
  bluetooth_serial.begin(BLE_BAUDRATE);
  bluetooth_serial.setTimeout(BLE_TIMEOUT);
}

/**
* @brief Realiza a leitura do GPS, coletando a Latitude e Longitude.
*
* @param Estrutura de dados do GPS, GPS_DATA_t.
*/
void read_gps(Gps_Data_t *gpsData)
{
  bool newData = false;
  float flat = 0;
  float flon = 0;
  unsigned long age = 0;
  char caracter_received = 0;

  for (unsigned long start = millis(); millis() - start < MIL_MILISSEGUNDOS;)
  {
    while (gps_serial.available())
    {
        caracter_received = gps_serial.read();

        if (gps.encode(caracter_received))
        {
          newData = true;
          gps.f_get_position(&flat, &flon, &age);
          gpsData->latitude = flat;
          gpsData->longitude = flon;
        }
    }
  }

  if (!newData)
  {
    gpsData->latitude = SENSOR_VALOR_ERROR;
    gpsData->longitude = SENSOR_VALOR_ERROR;
  }

}

/**
* @brief Função principal de leitura dos sensores, encapsula as demais funções.
*
* @param Recebe a estrutura de dados do sensores.
*/
void read_sensors(Sensors_Data_t *dados)
{
  dados->turbidity = read_turbidity_sensor();
  dados->ph = read_ph_sensor();
  dados->temperature = read_temperature_sensor();

  read_gps(&dados->gps);
}

/**
* @brief Configura as GPIO'S do dispositivo.
*/
void gpios_configuration()
{
  pinMode(LED_ONBOARD,OUTPUT);
  pinMode(TEMPERATURE_SENSOR,INPUT);
  pinMode(TURBIDITY_SENSOR,INPUT);
  pinMode(PH_SENSOR,INPUT);
}

/**
* @brief Envia os dados dos sensores através do bluetooth.
*
* @param Recebe a estrutura de dados dos sensores.
*/
void send_data(Sensors_Data_t *dados)
{
  digitalWrite(LED_ONBOARD,true);

  bluetooth_serial.print(dados->gps.longitude, GPS_DATA_NUMBRE_DECIMAL_PLACES); bluetooth_serial.print(F(SEPARATOR)); // GPS_log
  bluetooth_serial.print(dados->gps.latitude, GPS_DATA_NUMBRE_DECIMAL_PLACES); bluetooth_serial.print(F(SEPARATOR)); // GPS_la
  bluetooth_serial.print(dados->temperature); bluetooth_serial.print(F(SEPARATOR)); // Temperature
  bluetooth_serial.print(dados->turbidity); bluetooth_serial.print(F(SEPARATOR)); // Turbidity_data
  bluetooth_serial.print(dados->ph); bluetooth_serial.print(F(SEPARATOR)); // PH_sensor_data

  bluetooth_serial.print(SENSOR_VALOR_ERROR); bluetooth_serial.print(F(SEPARATOR)); // voltage_sensor_data_for_board
  bluetooth_serial.print(SENSOR_VALOR_ERROR); bluetooth_serial.print(F(SEPARATOR)); // ampere_sensor_data_for_boardsensor_data
  bluetooth_serial.print(SENSOR_VALOR_ERROR); bluetooth_serial.print(F(SEPARATOR)); // voltage_sensor_data_for_esc
  bluetooth_serial.print(SENSOR_VALOR_ERROR); bluetooth_serial.print(F(SEPARATOR)); // ampere_sensor_data_for_esc
  bluetooth_serial.print("\n");

  digitalWrite(LED_ONBOARD,false);
}




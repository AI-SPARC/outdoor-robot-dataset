/**
 * @file main.ino
 * @brief Arquivo principal.
 *
 * @author Ygor Dassaev
 * @date 18/07/2026
 * @version 1.0
 *
 * @details
 * Este arquivo implementa a lógica de operação do USV.
 *
 */


#include <MsTimer2.h>
#include <OneWire.h>
#include <Servo.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <avr/wdt.h>
#include "Configuration.h"
#include "structs.h"
#include "function.h"


OneWire ds(A0);  // on digital pin 2

TinyGPS gps;
SoftwareSerial gps_serial(GPS_RXD, GPS_TXD);
SoftwareSerial bluetooth_serial(BLE_RXD, BLE_TXD);

void setup() 
{
  gpios_configuration();
  ble_configuration();
  gps_configuration();

  Serial.begin(SERIAL_BAUDRATE);
  wdt_enable(WDTO_8S);
}

void loop() 
{
  static Sensors_Data_t sensores;
  static unsigned long previousMillis = millis();
  static uint8_t index = READ_SENSORS;

  if ((millis() - previousMillis) >= MIL_MILISSEGUNDOS)
  {
    previousMillis += MIL_MILISSEGUNDOS;

    switch(index)
    {
      case READ_SENSORS:
        read_sensors(&sensores);
        index = SEND_DATA;

      case SEND_DATA:
        send_data(&sensores);
        index = UPDATE_WATCHDOG;

      case UPDATE_WATCHDOG:
        wdt_reset();
        index = READ_SENSORS;
        break;

      default:
        break;
    }
  }
}

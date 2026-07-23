#include <MsTimer2.h>
#include <OneWire.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include "configuration.h"
#include "structs.h"
#include "function.h"

SoftwareSerial bluetooth_Serial(BLE_RXD, BLE_TXD);

Servo left_motor;
Servo right_motor;

void setup()
{
  // Serial monitor
  Serial.begin(SERIAL_BAUDRATE);
  Serial.setTimeout(50);

	ble_config(); 
	motors_config();

  write_motor_speed(left_motor,  MINIMAL_PULSE_RATE,  WEIGHT_CCW);
  write_motor_speed(right_motor, MINIMAL_PULSE_RATE, WEIGHT_CW);

  delay(3000); // tempo para armar ESC
}

void loop()
{
  static motor_control motorControl;
  static motor_command command;
   
  if (bluetooth_Serial.available() > 0)
  {
    command.rawCommand = bluetooth_Serial.readString();
    command.rawCommand.trim();
    command.separatorIndex = command.rawCommand.indexOf(COMMAND_SEPARATOR);
    if (command.separatorIndex > 0)
    {
      command.leftCommand  = command.rawCommand.substring(0, command.separatorIndex);
      command.rightCommand = command.rawCommand.substring(command.separatorIndex + 1);

      motorControl.left_motor_vel  = convert_throttle_to_pulse(command.leftCommand);
      motorControl.right_motor_vel = convert_throttle_to_pulse(command.rightCommand);

      write_motor_speed(left_motor,  motorControl.left_motor_vel,  WEIGHT_CCW);
      write_motor_speed(right_motor, motorControl.right_motor_vel, WEIGHT_CW);
    }
  }
}
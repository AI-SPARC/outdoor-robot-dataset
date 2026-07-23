#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct{
   int left_motor_vel = 0;
   int right_motor_vel = 0;
}motor_control;

typedef struct{ 
    int separatorIndex;
    String rawCommand;
    String leftCommand;
    String rightCommand;
}motor_command;

#endif
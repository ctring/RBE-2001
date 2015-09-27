/**
 * movement.h - Header containing prototypes and macros for movement.c
 * 
 * Created on Sept 26, 2015 by Cuong Nguyen
 */

#ifndef MOVEMENT_H
#define MOVEMENT_H 

// Motors pins 
#define LEFT_MOTOR_PIN
#define RIGHT_MOTOR_PIN

// Motor speeds
#define NORMAL_SPEED_CW 180
#define NORMAL_SPEED_CCW 0
#define STOP_SPEED 90
#define ADJUSTING_SPEED_CW 110
#define ADJUSTING_SPEED_CCW 70

// Options for robot turning left/right
#define TURN_LEFT 0
#define TURN_RIGHT 1

// Options for robot go back a bit or until touch black line
#define A_BIT 0
#define TO_BLACK_LINE 1 

// Encoder limits for different movements
#define BACKWARD_LIMIT 50
#define TURN_180_LIMIT 90
#define TURN_90_LIMIT 30

bool goForward();
bool goBackward(int);
bool turn180();
bool turn90(int);

void runLeftMotor(int);
void runRightMotor(int);
void stopMotors();

void setupMotors();

#endif
/**
 * movement.h - Header containing prototypes and macros for movement.c
 * 
 * Created on Sept 26, 2015 by Cuong Nguyen
 */

#ifndef MOVEMENT_H
#define MOVEMENT_H 

/* 
 * Convention for motor controlling: 
 *
 * ---------------------  
 * | A | B | Direction |
 * ---------------------
 * | 1 | 0 |    CCW    |
 * ---------------------
 * | 0 | 1 |    CW     |
 * ---------------------
 * | 0 | 0 |   Brake   |
 * ---------------------
 * | 1 | 1 |   Brake   |
 * ---------------------
 */

// Left motor pins 
#define LMOTOR_PIN_A
#define LMOTOR_PIN_B

// Right motor pins
#define RMOTOR_PIN_A
#define RMOTOR_PIN_B

// Motor speeds
#define NORMAL_SPEED 255
#define ADJUSTING_SPEED 200

// Options for robot turning left/right
#define TURN_LEFT 0
#define TURN_RIGHT 1

// Options for robot go back a bit or until touch black line
#define A_BIT 0
#define TO_BLACK_LINE 1 

bool goForward();
bool goBackward(int);
bool turn180();
bool turn90(int);

void runLeftMotor(int);
void runRightMotor(int);

void setupMotors();

#endif
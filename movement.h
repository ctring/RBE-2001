/**
 * movement.h - Header containing prototypes and macros for movement.c
 * 
 * Created on Sept 26, 2015 by Cuong Nguyen
 */

#ifndef MOVEMENT_H
#define MOVEMENT_H 

#include <Arduino.h>
#include <Servo.h>

// Motors pins 
#define LEFT_MOTOR_PIN		4
#define RIGHT_MOTOR_PIN		5

// Motor speeds
#define NORMAL_SPEED_CCW  	28
#define NORMAL_SPEED_CW		155
#define STOP_SPEED 			90

// Options for robot turning left/right
#define LEFT 				0
#define RIGHT 				1

// Encoder limits for different movements
#define BACKWARD_ENCODER		50
#define TURN_180_ENCODER 		110
#define TURN_90_ENCODER 		55

void setupMotors();

bool goForward(bool);
bool calcNextLine();
bool switchSide();
bool goForwardAndCount();
bool goBackward();
bool turn180();
bool turn90(int);

void runLeftMotor(int);
void runRightMotor(int);
void stopMotors();

#endif

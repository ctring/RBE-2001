/**
 * movement.cpp - Source code for motors controlling movement
 *
 * Created on Sept 26, 2015 by Cuong Nguyen
 */
#include <Arduino.h>

#include "movement.h"
#include "sensors.h"

/**
 * Setups motors pins mode.
 */
void setupMotors() {
	pinMode(LMOTOR_PIN_A, OUTPUT);
	pinMode(LMOTOR_PIN_B, OUTPUT);
	pinMode(RMOTOR_PIN_A, OUTPUT);
	pinMode(RMOTOR_PIN_B, OUTPUT);
}

/**
 * Runs left motor with given speed.
 *   speed - if speed is larger than 0, motor runs CCW, otherwise motor runs CW.
 */
void runLeftMotor(int speed) {
	if (speed >= 0) {
		analogWrite(LMOTOR_PIN_A, speed);
		analogWrite(LMOTOR_PIN_B, 0);
	}
	else {
		analogWrite(LMOTOR_PIN_A, 0);
		analogWrite(LMOTOR_PIN_B, speed);
	}
}

/**
 * Runs right motor with given speed.
 *   speed - if speed is larger than 0, motor runs CCW, otherwise motor runs CW.
 */
void runRightMotor(int speed) {
	if (speed >= 0) {
		analogWrite(RMOTOR_PIN_A, speed);
		analogWrite(RMOTOR_PIN_B, 0);
	}
	else {
		analogWrite(RMOTOR_PIN_A, 0);
		analogWrite(RMOTOR_PIN_B, speed);
	}
}

/**
 * Stops all motors
 */
void stopMotors() {
	runLeftMotor(0);
	runRightMotor(0);
}

/**
 * Controls robot to go forward.
 *   return true if front limit switch is closed, false otherwise.
 */
bool goForward() {
	if (checkLimitSwitch(LIMIT_FRONT)) {
		stopMotors();
		return true;
	}
	int ltData = 0;
	getLineTrackingVal(ltData);

	if (ltData == 5) {
		runLeftMotor(NORMAL_SPEED);
		runRightMotor(-NORMAL_SPEED);
	}
	else if (ltData == 2 || ltData == 6 || ltData == 9) {
		runLeftMotor(NORMAL_SPEED);
		runRightMotor(-ADJUSTING_SPEED);
	}
	else if (ltData == 3 || ltData == 8 || ltData == 12) {
		runLeftMotor(ADJUSTING_SPEED);
		runRightMotor(-NORMAL_SPEED);
	}
	else {
		runLeftMotor(NORMAL_SPEED);
		runRightMotor(NORMAL_SPEED);
	}
	return false;
}  

/**
 * Controls robot to go backward. 
 * 	 mode - how far the robot go  
 * 		A_BIT go backward for a few slots of encoder. Reset and start encoder 
 * 		counter before using this mode.
 *  	TO_BLACK_LINE go backward until line tracker detects a horizontal line.
 *   return true if the limit specified by mode is reached, false otherwise.
 */
bool goBackward(int mode) {
	startEncoder();
	if (mode == A_BIT && getEncoder() >= BACKWARD_LIMIT) {
		stopMotors();
		stopAndResetEncoder();
		return true;
	}

	int ltData = 0;
	getLineTrackingVal(ltData);
 
	if (mode == TO_BLACK_LINE && ltData == 10) {
		stopMotors();
		return true;
	}

	if (ltData == 5) {
		runLeftMotor(-NORMAL_SPEED);
		runRightMotor(NORMAL_SPEED);
	}
	else if (ltData == 2 || ltData == 6 || ltData == 9) {
		runLeftMotor(-NORMAL_SPEED);
		runRightMotor(ADJUSTING_SPEED);
	}
	else if (ltData == 3 || ltData == 8 || ltData == 12) {
		runLeftMotor(-ADJUSTING_SPEED);
		runRightMotor(NORMAL_SPEED);
	}
	else {
		runLeftMotor(NORMAL_SPEED);
		runRightMotor(NORMAL_SPEED);
	}
	return false;
}

/**
 * Turns robot 180 degrees. Reset and start encoder counter before using this.
 * Encoder is stopped when the limit is reached.
 */
bool turn180() {
	startEncoder();
	if (getEncoder() >= TURN_180_LIMIT) {
		stopMotors();
		stopAndResetEncoder();
		return true;
	}
	runLeftMotor(NORMAL_SPEED);
	runRightMotor(NORMAL_SPEED);
	return false;
}

/**
 * Turns robot 90 degrees. Reset and start encoder counter before using this.
 * Encoder is stopped when the limit is reached.
 *   direction - whether the robot turns left or right 
 *		TURN_LEFT robot turns left.
 *		TURN_RIGHT robot turns right.
 */ 
void turn90(int direction) {
	startEncoder();
	if (getEncoder() >= TURN_90_LIMIT) {
		stopMotors();
		stopAndResetEncoder();
		return true;	
	}
	if (direction == TURN_LEFT) {
		runLeftMotor(-NORMAL_SPEED);
		runRightMotor(NORMAL_SPEED);
	} else {
		runLeftMotor(NORMAL_SPEED);
		runRightMotor(-NORMAL_SPEED);
	}
	return false;
}
/**
 * movement.cpp - Source code for motors controlling movement
 *
 * Created on Sept 26, 2015 by Cuong Nguyen
 */

#include "movement.h"

Servo leftMotor;
Servo rightMotor;

/**
 * Setups motors pins mode.
 */
void setupMotors() {
	leftMotor.attach(LEFT_MOTOR_PIN);
	rightMotor.attach(RIGHT_MOTOR_PIN);
}

/**
 * Stops all motors
 */
void stopMotors() {
	leftMotor.write(STOP_SPEED);
	rightMotor.write(STOP_SPEED);
}

/**
 * Controls robot to go forward.
 *   return true if front limit switch is closed, false otherwise.
 */
bool goForward() {
	if (checkLimitSwitch(LIMIT_FRONT_PIN)) {
		stopMotors();
		return true;
	}
	int ltData = getLineTrackingVal();

	if (ltData == 5) {
		leftMotor.write(NORMAL_SPEED_CCW);
		rightMotor.write(NORMAL_SPEED_CW);
	}
	else if (ltData == 2 || ltData == 6 || ltData == 9) {
		leftMotor.write(NORMAL_SPEED_CCW);
		rightMotor.write(ADJUSTING_SPEED_CW);
	}
	else if (ltData == 3 || ltData == 8 || ltData == 12) {
		leftMotor.write(ADJUSTING_SPEED_CCW);
		rightMotor.write(NORMAL_SPEED_CW);
	}
	else {
		leftMotor.write(NORMAL_SPEED_CW);
		rightMotor.write(NORMAL_SPEED_CCW);
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

	int ltData = getLineTrackingVal();
 
	if (mode == TO_BLACK_LINE && ltData == 10) {
		stopMotors();
		return true;
	}

	if (ltData == 5) {
		leftMotor.write(NORMAL_SPEED_CW);
		rightMotor.write(NORMAL_SPEED_CCW);
	}
	else if (ltData == 2 || ltData == 6 || ltData == 9) {
		leftMotor.write(NORMAL_SPEED_CW);
		rightMotor.write(ADJUSTING_SPEED_CCW);
	}
	else if (ltData == 3 || ltData == 8 || ltData == 12) {
		leftMotor.write(ADJUSTING_SPEED_CW);
		rightMotor.write(NORMAL_SPEED_CCW);
	}
	else {
		leftMotor.write(NORMAL_SPEED_CW);
		rightMotor.write(NORMAL_SPEED_CCW);
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
	leftMotor.write(NORMAL_SPEED_CW);
	rightMotor.write(NORMAL_SPEED_CCW);
	return false;
}

/**
 * Turns robot 90 degrees. Reset and start encoder counter before using this.
 * Encoder is stopped when the limit is reached.
 *   direction - whether the robot turns left or right 
 *		TURN_LEFT robot turns left.
 *		TURN_RIGHT robot turns right.
 */ 
bool turn90(int direction) {
	startEncoder();
	if (getEncoder() >= TURN_90_LIMIT) {
		stopMotors();
		stopAndResetEncoder();
		return true;	
	}
	if (direction == TURN_LEFT) {
		leftMotor.write(NORMAL_SPEED_CW);
		rightMotor.write(NORMAL_SPEED_CCW);
	} else {
		leftMotor.write(NORMAL_SPEED_CCW);
		rightMotor.write(NORMAL_SPEED_CW);
	}
	return false;
}

/**
 * movement.cpp - Source code for motors controlling movement
 *
 * Created on Sept 26, 2015 by Cuong Nguyen
 */
#include "sensors.h"
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
 * Controls robot to go forward until the front limit switch is closed.
 * @param reversed reverse the motion if set to true.
 * @return true if front limit switch is closed, false otherwise.
 */
bool goForward(bool reversed) {
	if (checkLimitSwitch(LIMIT_FRONT_PIN)) {
		stopMotors();
		return true;
	}
	int ltData[5];
	getLineTrackingVal(ltData);

	int count = ltData[0] + ltData[1] + ltData[2] + ltData[3] + ltData[4];

	int sum4 = ltData[0] * (-2) + ltData[1] * (-1)  + ltData[2] + ltData[3] * 2;
	double err = sum4 / count;
	int sp = err * 45;
	if (sp > 0) {
		if (!reversed) {
			leftMotor.write(NORMAL_SPEED_CCW);
			rightMotor.write(NORMAL_SPEED_CW - sp);
		} else {
			leftMotor.write(NORMAL_SPEED_CW);
			rightMotor.write(NORMAL_SPEED_CCW + sp);
		}
	} else {
		if (!reversed) {
			leftMotor.write(NORMAL_SPEED_CCW - sp);
			rightMotor.write(NORMAL_SPEED_CW);
		} else {
			leftMotor.write(NORMAL_SPEED_CW + sp);
			rightMotor.write(NORMAL_SPEED_CCW);
		}
	}
	return false;
}

/**
 * Controls robot to go backward until hitting a horizontal line.
 * @return true if the line is hit, false otherwise.
 */
bool goBackward() {
	if (checkHorizontalLine()) {
		stopMotors();
		return true;
	}
	return goForward(true);
}

int side = 0;
int currentLine = 0;
int targetLineCount = 0;
int lineCounted = 0;
bool lineDetected = false;
/**
 * Controls robot to go forward or backward then stops after counted a number of 
 * lines. 
 * @param  	lines number of lines to count before stopping. If lines is larger than
 *          0 then the robot goes forward, otherwise the robot goes backward.
 * @return	true after counting finishes, false otherwise.
 */
bool goForwardAndCount() {
	if (lineCounted == abs(targetLineCount)) {
		lineCounted = 0;
		lineDetected = false;
		stopMotors();
		return true;
	}
	if (lineDetected) {
		lineDetected = false;
		lineCounted++;
	}
	if (checkHorizontalLine()) {
		lineDetected = true;
	}
	if (goForward(targetLineCount < 0)) {
		stopMotors();
		return true;
	}
}

/**
 * Computes next line based on the current line
 * @return true
 */
bool calcNextLine() {
	return true;	
}

/**
 * Switches side to other reactor.
 * @return true
 */
bool switchSide() {
	
	return true;
}

/**
 * Turns robot 180 degrees. Reset and start encoder counter before using this.
 * Encoder is stopped when the limit is reached.
 */
bool turn180() {
	startEncoder();
	if (getLeftEncoder() >= TURN_180_ENCODER &&
		getRightEncoder() >= TURN_180_ENCODER) {
		stopMotors();
		stopAndResetEncoder();
		return true;
	}
	leftMotor.write(NORMAL_SPEED_CW);
	rightMotor.write(NORMAL_SPEED_CW);
	return false;
}

/**
 * Turns robot 90 degrees. Reset and start encoder counter before using this.
 * Encoder is stopped when the limit is reached.
 * @param direction whether the robot turns left or right 
 *		TURN_LEFT robot turns left.
 *		TURN_RIGHT robot turns right.
 */ 
bool turn90(int direction) {
	startEncoder();
	if (getLeftEncoder() >= TURN_90_ENCODER &&
		getRightEncoder() >= TURN_90_ENCODER) {
		stopMotors();
		stopAndResetEncoder();
		return true;	
	}
	if (direction == LEFT) {
		leftMotor.write(NORMAL_SPEED_CW);
		rightMotor.write(NORMAL_SPEED_CW);
	} else {
		leftMotor.write(NORMAL_SPEED_CCW);
		rightMotor.write(NORMAL_SPEED_CCW);
	}
	return false;
}

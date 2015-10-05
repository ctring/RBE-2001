/**
 * sensors.cpp - Source for reading various sensors of the robot
 *
 * Created on Sept 26, 2015 by Cuong Nguyen
 */

#include "sensors.h"

volatile int encoderLeftCounter = 0;
volatile int encoderRightCounter = 0;
volatile bool counting = false;

/**
 * Sets up mode for sensors pins
 */
void setupSensors() {
	pinMode(LIMIT_FRONT_PIN, 	 INPUT_PULLUP);
	pinMode(LIMIT_CRANE_HOR_PIN,  INPUT_PULLUP);
	pinMode(LIMIT_CRANE_VER_PIN, INPUT_PULLUP);
	pinMode(LIMIT_SLIDE_IN_PIN,  INPUT_PULLUP);
	pinMode(LIMIT_SLIDE_OUT_PIN, INPUT_PULLUP);

	attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_PIN), 
					countLeftEncoderISR, 
					FALLING);
	attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_PIN), 
          			countRightEncoderISR, 
          			FALLING);
}

/**
 * Starts counting slots of the encoder.
 */
void startEncoder() {
	counting = true;
}

/**
 * Stops counting and slots of the encoder and reset the value to 0.
 */
void stopAndResetEncoder() {
	noInterrupts();
	counting = false;
	encoderLeftCounter = 0;
	encoderRightCounter = 0;
	interrupts();
}

/**
 * Increases counter everytime encoder pin triggers interrupt.
 */
void countLeftEncoderISR() {
	if (counting) {
		encoderLeftCounter++;
	}
}

/**
 * Increases counter everytime encoder pin triggers interrupt.
 */
void countRightEncoderISR() {
	if (counting) {
		encoderRightCounter++;
	}
}

/**
 * Gets current count of the encoder
 */
int getLeftEncoder() {
	noInterrupts();
	int ret = encoderLeftCounter;
	interrupts();
	return ret;
}

/**
 * Gets current count of the encoder
 */
int getRightEncoder() {
	noInterrupts();
	int ret = encoderRightCounter;
	interrupts();
	return ret;
}

/**
 * Gets line tracking value.
 * @param dest an array of four values reprensting the four sensors
 */
void getLineTrackingVal(int* result) {
	result[4] = toDigital(analogRead(LT_FRONT_PIN));
	result[0] = toDigital(analogRead(LT_0_PIN));
	result[1] = toDigital(analogRead(LT_1_PIN));
	result[2] = toDigital(analogRead(LT_2_PIN));
	result[3] = toDigital(analogRead(LT_3_PIN));
}

/**
 * Checks whether the robot reaches the a horizontal black line.
 * @param  ltData line tracking data
 * @return        true if robot reaches a horizontal line, false otherwise
 */
bool checkHorizontalLine() {
	int ltData[5];
	getLineTrackingVal(ltData);
	return ltData[0] + ltData[1] + ltData[2] + ltData[3] + ltData[4] >= 4; 
}

/**
 * Checks whether certain limit switch is closed or not.
 * @return true if the switch is closed, false otherwise.
 */
bool checkLimitSwitch(int pin) {
	return digitalRead(pin) == 0;
}

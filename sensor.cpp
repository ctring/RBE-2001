/**
 * sensors.cpp - Source for reading various sensors of the robot
 *
 * Created on Sept 26, 2015 by Cuong Nguyen
 */
#include <Arduino.h>
#include "sensors.h"

volatile int encoderCounter = 0;
volatile bool counting = false;

/**
 * Sets up mode for sensors pins
 */
void setupSensors() {
	pinMode(LIMIT_FRONT_PIN, 	 INPUT_PULLUP);
	pinMode(LIMIT_0_DEGREE_PIN,  INPUT_PULLUP);
	pinMode(LIMIT_90_DEGREE_PIN, INPUT_PULLUP);
	pinMode(LIMIT_SLIDE_IN_PIN,  INPUT_PULLUP);
	pinMode(LIMIT_SLIDE_OUT_PIN, INPUT_PULLUP);

	attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), 
					countEncoderISR, 
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
	encoderCounter = 0;
	Interrupts();
}

/**
 * Increases counter everytime encoder pin triggers interrupt.
 */
void countEncoderISR() {
	if (counting) {
		encoderCounter++;
	}
}

/**
 * Gets current count of the encoder
 */
int getEncoder() {
	noInterrupts();
	int ret = encoderCounter;
	interrupt();
	return ret;
}

/**
 * Gets line tracking value
 *   dest - an array of four values reprensting the four sensors
 */
void getLineTrackingVal(int* dest) {
	return toDigital(analogRead(LT_FRONT_PIN)) 
			| (toDigital(analogRead(LT_LEFT_PIN)) << 1)
			| (toDigital(analogRead(LT_BACK_PIN)) << 2)
			| (toDigital(analogRead(LT_RIGHT_PIN)) << 3);
}

/**
 * Checks whether certain limit switch is closed or not.
 *   return true if the switch is closed, false otherwise.
 */
bool checkLimitSwitch(int pin) {
	return digitalRead(pin) == 0;
}

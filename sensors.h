/**
 * sensors.h - Header containing prototypes and macros for sensors.cpp
 *
 * Created on Sept 26, 2015 by Cuong Nguyen
 */
#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

// Sensor pins
#define ENCODER_PIN 		0

// Line tracking sensor pins
/**
 * Line tracking sensor setup
 *			0 (front)
 *		3		1
 *			2
 */
#define LT_FRONT_PIN 		0
#define LT_BACK_PIN 		0
#define LT_LEFT_PIN 		0
#define LT_RIGHT_PIN 		0

// LT sensor value larger than LT_BORDER means it is on black line.
#define LT_BORDER       0
#define toDigital(x) (x > LT_BORDER)

// Limit switches pins
#define LIMIT_FRONT_PIN		0
#define LIMIT_CRANE_HOR_PIN	0
#define LIMIT_CRANE_VER_PIN	0
#define LIMIT_SLIDE_IN_PIN	0
#define LIMIT_SLIDE_OUT_PIN	0

void setupSensors();

void startEncoder();
void stopAndResetEncoder();
void countEncoderISR();
int getEncoder();

int getLineTrackingVal();

bool checkLimitSwitch(int);

#endif

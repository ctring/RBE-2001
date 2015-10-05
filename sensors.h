/**
 * sensors.h - Header containing prototypes and macros for sensors.cpp
 *
 * Created on Sept 26, 2015 by Cuong Nguyen
 */
#ifndef SENSOR_H
#define SENSOR_H

// Sensor pins
#define ENCODER_LEFT_PIN 	2
#define ENCODER_RIGHT_PIN   3

// Line tracking sensor pins
#define LT_FRONT_PIN 	A4
#define LT_0_PIN 		A0
#define LT_1_PIN 		A1
#define LT_2_PIN 		A2
#define LT_3_PIN    	A3

// LT sensor value larger than LT_BORDER means it is on black line.
#define LT_BORDER			500
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
void countLeftEncoderISR();
void countRightEncoderISR();
int getLeftEncoder();
int getRightEncoder();

void getLineTrackingVal(int*);

bool checkHorizontalLine();
bool checkLimitSwitch(int);

#endif

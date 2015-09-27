/**
 * sensors.h - Header containing prototypes and macros for sensors.cpp
 *
 * Created on Sept 26, 2015 by Cuong Nguyen
 */
#ifndef SENSOR_H
#define SENSOR_H

// Sensor pins
#define ENCODER_PIN 

// Line tracking sensor pins
/**
 * Line tracking sensor setup
 *			0 (front)
 *		3		1
 *			2
 */
#define LT_FRONT_PIN
#define LT_BACK_PIN
#define LT_LEFT_PIN
#define LT_RIGHT_PIN

// LT sensor value larger than LT_BORDER means it is on black line.
#define LT_BORDER
#define toDigital(x) (x > LT_BORDER)

// Limit switches pins
#define LIMIT_FRONT_PIN
#define LIMIT_CRANE_HOR_PIN
#define LIMIT_CRANE_VER_PIN
#define LIMIT_SLIDE_IN_PIN
#define LIMIT_SLIDE_OUT_PIN

void setupSensors();

void startEncoder();
void stopAndResetEncoder();
void countEncoderISR();
int getEncoder();

void getLineTrackingVal(int&);

bool checkLimitSwitch(int);

#endif
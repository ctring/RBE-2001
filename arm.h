/**
 * arms.h - Header containing prototypes and macros for arms.cpp
 *
 * Created on Sept 27, 2015 by Cuong Nguyen
 */
#ifndef ARM_H
#define ARM_H

#define CRANE_PIN 		0
#define SLIDER_PIN 		0
#define GRIPPER_PIN		0

#define CRANE_TO_HOR 	0
#define CRANE_TO_VER 	180
#define CRANE_STOP 		90

#define SLIDER_IN 		0
#define SLIDER_OUT 		180
#define SLIDER_STOP 	90

#define GRIPPER_OPEN 	180
#define GRIPPER_CLOSE 	0

void setupArm();

int craneToHor();
int craneToVer();
int slideIn();
int slideOut();
int openGripper();
int closeGripper();

#endif

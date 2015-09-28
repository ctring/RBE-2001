/**
 * arms.h - Source code for controlling the arm
 *
 * Created on Sept 27, 2015 by Cuong Nguyen
 */

#include "arm.h"

Servo gripper;
Servo crane;
Servo slider;

void setupArm() {
	slider.attach(SLIDER_PIN);
	gripper.attach(GRIPPER_PIN);
	crane.attach(CRANE_PIN);
}

int craneToHor() {
	if (checkLimitSwitch(LIMIT_CRANE_HOR_PIN)) {
		crane.write(CRANE_STOP);
		return true;
	}
	crane.write(CRANE_TO_HOR);
	return false;
}

int craneToVer() {
	if (checkLimitSwitch(LIMIT_CRANE_VER_PIN)) {
		crane.write(CRANE_STOP);
		return true;
	}
	crane.write(CRANE_TO_VER);
	return false;
}

int slideIn() {
	if (checkLimitSwitch(LIMIT_SLIDE_IN_PIN)) {
		slider.write(SLIDER_STOP);
		return true;
	}
	slider.write(SLIDER_IN);
	return false;
}

int slideOut() {
	if (checkLimitSwitch(LIMIT_SLIDE_OUT_PIN)) {
		slider.write(SLIDER_STOP);
		return true;
	}
	slider.write(SLIDER_OUT);
	return false;
}

int openGripper() {
	gripper.write(GRIPPER_OPEN);
	delay(1000);
	return true;
}

int closeGripper() {
	gripper.write(GRIPPER_CLOSE);
	delay(1000);
	return true;
}

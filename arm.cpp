/**
 * arms.h - Source code for controlling the arm
 *
 * Created on Sept 27, 2015 by Cuong Nguyen
 */

#include "arm.h"

Servo gripper;
Servo crane;
Servo slider;

/**
 * Sets up pins for slider, gripper and crane
 */
void setupArm() {
	slider.attach(SLIDER_PIN);
	gripper.attach(GRIPPER_PIN);
	crane.attach(CRANE_PIN);
}

/**
 * Rotates the crane to horizontal position.
 * @return true when limit switch reached, false otherwise.
 */
int craneToHor() {
	if (checkLimitSwitch(LIMIT_CRANE_HOR_PIN)) {
		crane.write(CRANE_STOP);
		return true;
	}
	crane.write(CRANE_TO_HOR);
	return false;
}

/**
 * Rotates the crane to vertical position.
 * @return true when limit switch reached, false otherwise.
 */
int craneToVer() {
	if (checkLimitSwitch(LIMIT_CRANE_VER_PIN)) {
		crane.write(CRANE_STOP);
		return true;
	}
	crane.write(CRANE_TO_VER);
	return false;
}

/**
 * Slides the slider in.
 * @return true when limit switch reached, false otherwise.
 */
int slideIn() {
	if (checkLimitSwitch(LIMIT_SLIDE_IN_PIN)) {
		slider.write(SLIDER_STOP);
		return true;
	}
	slider.write(SLIDER_IN);
	return false;
}

/**
 * Slides the slider out.
 * @return true when limit switch reached, false otherwise.
 */
int slideOut() {
	if (checkLimitSwitch(LIMIT_SLIDE_OUT_PIN)) {
		slider.write(SLIDER_STOP);
		return true;
	}
	slider.write(SLIDER_OUT);
	return false;
}

/**
 * Opens the gripper.
 * @return true.
 */
int openGripper() {
	gripper.write(GRIPPER_OPEN);
	delay(1000);
	return true;
}

/**
 * Closes the gripper.
 * @return true.
 */
int closeGripper() {
	gripper.write(GRIPPER_CLOSE);
	delay(1000);
	return true;
}

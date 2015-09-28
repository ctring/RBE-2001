#include <Servo.h>

#include "sensors.h"
#include "movement.h"
#include "arm.h"
#include "states.h"	

void setup() {
	setupMotors();
	setupSensors();
	setupArm();
}

int state = 0;
int side = 0;

void loop() {
	bool finished = false;
	switch (state) {
		case 0: 
			finished = getOldRod();
			break;
		case 1:
			finished = storeOldRod();
			break;
		case 2: 
			finished = getNewRod();
			break;
		case 3:
			finished = placeNewRod();
			break;
	}
	if (finished) {
		state++;
		if (state >= 4) {
			state = 0;
			side = 1 - side;
		}
	}	
}

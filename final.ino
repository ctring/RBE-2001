#include <Servo.h>
#include <BluetoothClient.h>
#include <BluetoothMaster.h>
#include <ReactorProtocol.h>
#include <TimerOne.h>

#include "sensors.h"
#include "movement.h"
#include "arm.h"
#include "executor.h"
#include "test.h"

extern byte storageData;
extern byte supplyData;

int GET_OLD_ROD[] = {
		GO_FORWARD, 
		TO_VERTICAL,
		OPEN_GRIPPER,
		SLIDE_OUT,
		CLOSE_GRIPPER,
		SLIDE_IN,
		TO_HORIZONTAL,
		END_OF_LIST
	};

int STORE_OLD_ROD[] = {
		CALC_NEXT_LINE,
		GO_FORWARD_AND_COUNT,
		TURN_90,
		GO_FORWARD,
		SLIDE_OUT,
		OPEN_GRIPPER,
		SLIDE_IN,
		CLOSE_GRIPPER,
		GO_BACKWARD,
		TURN_90,
		END_OF_LIST
	};

int GET_NEW_ROD[] = {
		CALC_NEXT_LINE,
		GO_FORWARD_AND_COUNT,
		TURN_90,
		GO_FORWARD,
		OPEN_GRIPPER,
		SLIDE_OUT,
		CLOSE_GRIPPER,
		SLIDE_IN,
		GO_BACKWARD,
		TURN_90,
		END_OF_LIST
	};

int PUT_NEW_ROD[] = {
		GO_FORWARD,
		TO_VERTICAL,
		SLIDE_OUT,
		OPEN_GRIPPER,
		SLIDE_IN,
		CLOSE_GRIPPER,
		TO_HORIZONTAL,
		SWITCH_SIDE,
		END_OF_LIST
	};

int listLength(int* list) {
	int len = 0;
	while (list[len] != END_OF_LIST) len++;
	return len;
}

void setup() {
  	Serial.begin(9600);
	setupMotors();
	setupSensors();
	//setupArm();
}

int state = 0;

void loop() {
	int* tasks;
	switch (state) {
		case 0: 
			tasks = GET_OLD_ROD;
			break;
		case 1:
			tasks = STORE_OLD_ROD;
			break;
		case 2: 
			tasks = GET_NEW_ROD;
			break;
		case 3:
			tasks = PUT_NEW_ROD;
			break;
	}
	if (executeTasks(tasks, listLength(tasks))) {
		state = (state + 1) % 4;
	}
}

void testLoop() {
 bool finished = false;
 switch (state) {
    case 0:
      finished = turn90(LEFT);
      break;
    case 1:
      finished = turn90(LEFT);
      break;
    case 2:
      finished = turn180();
      break;
    case 3:
      finished = turn90(RIGHT);
      break;
    case 4:
      finished = turn90(RIGHT);
      break;  
    case 5:
      finished = turn180();
      break;
  }
  if (finished) {
    delay(1000);
    state++;
  }
}

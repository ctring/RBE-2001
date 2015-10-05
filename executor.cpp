#include "movement.h"
#include "arm.h"
#include "executor.h"

int taskPointer = 0;

bool doTask(int task) {
	switch (task) {
		case GO_FORWARD: 		
			return goForward(false);
		case GO_BACKWARD:	
			return goBackward(); 
		case CALC_NEXT_LINE:	
			return calcNextLine();
		case GO_FORWARD_AND_COUNT:
			return goForwardAndCount();
		case TURN_LEFT:		
			return turn90(LEFT);	
		case TURN_RIGHT:		
			return turn90(RIGHT);
		case TURN_90:		
			// turn this based on the side
			return true;
		case TURN_180:
			return turn180();
		case TO_VERTICAL:
			return craneToVer();
		case TO_HORIZONTAL:
			return craneToHor();
		case SLIDE_OUT:
			return slideOut();
		case SLIDE_IN:
			return slideIn();
		case OPEN_GRIPPER:
			return openGripper();
		case CLOSE_GRIPPER:
			return closeGripper();
		case SWITCH_SIDE:
			return switchSide();
		default:		
			return true;
	}
}

bool executeTasks(int* tasks, int noOfTasks) {
	if (taskPointer == noOfTasks) {
    taskPointer = 0;
		return true;
	}
	if (doTask(tasks[taskPointer])) {
		taskPointer++;
	}
	return false;
}

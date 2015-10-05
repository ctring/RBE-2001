#ifndef EXECUTOR_H
#define EXECUTOR_H

#define END_OF_LIST				-1
#define GO_FORWARD 				0
#define GO_BACKWARD				1
#define TURN_LEFT				2
#define TURN_RIGHT				3
#define TURN_180				4
#define TO_VERTICAL 			5
#define TO_HORIZONTAL  			6
#define SLIDE_OUT				7
#define SLIDE_IN				8
#define OPEN_GRIPPER			9
#define CLOSE_GRIPPER			10
#define CALC_NEXT_LINE 			11
#define GO_FORWARD_AND_COUNT 	12
#define TURN_90					13
#define SWITCH_SIDE				14

bool doTask(int);
bool executeTasks(int* tasks, int noOfTasks);

#endif

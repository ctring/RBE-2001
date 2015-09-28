#include "states.h"
#include "movement.h"
#include "arm.h"

int task = 0;

int getOldRod() {
	int finished = false;
	switch (task) {
		case 0: finished = goForward();
		  		break;
		case 1:	finished = craneToVer(); 		
				break;
		case 2: finished = openGripper(); 		
				break;
		case 3: finished = slideOut(); 		
				break;
		case 4: finished = closeGripper(); 	
				break;
		case 5: finished = slideIn(); 			
				break;
		case 6: finished = craneToHor(); 		
				break;
		case 7: finished = goBackward(A_BIT); 	
				break;
		case 8: finished = turn180();			
				break;
	}
	if (finished) {
		task++;
		if (task >= 9) {
			return true;
		}
	}
	return false;
}

int storeOldRod() {}
int getNewRod() {}
int placeNewRod() {}
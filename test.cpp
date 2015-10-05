#include "test.h"

void printLineTrackingSensors() {
	int data[5];
	getLineTrackingVal(data);
	for (int i = 0; i < 5; i++) {
	Serial.print(data[i]);
	Serial.print(" ");
	}
	Serial.println();
}
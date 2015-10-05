#include "bluetooth.h"

// instantiate needed objects
ReactorProtocol pcol(byte(thisROBOT));         // instantiate the protocol object and set the robot/team source address
BluetoothClient bt;                            // instantiate a Bluetooth client object
BluetoothMaster btmaster;                      // ...and a master object

volatile unsigned char tickCount;              // elapsed time in ticks (timer interrupts)
volatile unsigned long elapsedTime;            // ...and in seconds
volatile unsigned char hbCount;                // ticks since last heartbeat message was sent
volatile boolean sendHB;                       // flag indicating it is time to send a heartbeat message

byte storageData;                              // holds the bitmask for the storage tubes
byte supplyData;                               // ... and the supply tubes

byte pkt[10];                                // allocate memory for the bytes in the packet
int sz;                                      // holds the size of the message (in bytes)
byte type;                                   // hold the message type id
byte data1[3];    

void setupBluetooth() {
	Serial1.begin(115200);

	tickCount = 0;
	hbCount = 0;
	elapsedTime = 0;
	sendHB = false;

	Timer1.initialize(100000);
	Timer1.attachInterrupt(timer1ISR);
}



void readBluetoothPacket() {
	if (btmaster.readPacket(pkt)) {              // if we have received a message
	    if (pcol.getData(pkt, data1, type)) {      // see if we can extract the type and data
			switch (type) {                          // process the message based on the type
				case 0x01:                               // received a storage tube message
					storageData = data1[0];                // extract and save the storage-related data (the byte bitmask)
				break;
				case 0x02:                               // received a supply tube message
					supplyData = data1[0];                 // extract and save the supply-related data (the byte bitmask)
				break;
				default:                                 // ignore other types of messages
				break;
			}
		}
	}
}

void sendHeartbeat() {
	if (sendHB) {                          // execute if GO flag is set and it's time to generate a heartbeat message
		sendHB = false;                            // clear the heartbeat flag

		// generate and send the heartbeat message    
		pcol.setDst(0x00);			       // this will be a broadcast message
		sz = pcol.createPkt(0x07, data1, pkt);     // create a packet using the heartbeat type ID (there is no data)
		btmaster.sendPkt(pkt, sz);                 // send to the field computer

		// example of sending a radiation alert message (new fuel rod)
		delay(20);                                 // wait a little while so we don't spam the field control computer
		pcol.setDst(0x00);			       // this will be a broadcast message
		data1[0] = 0xFF;                           // indicate a new fuel rod
		sz = pcol.createPkt(0x03, data1, pkt);     // create a packet using the radiation alert type ID (1 byte of data used this time)
		btmaster.sendPkt(pkt, sz);                 // send to the field computer
	}
}

void timer1ISR() {
	tickCount++;			// increment the 100ms tick counter
	hbCount++;				// increment the heartbeat counter
	if (tickCount == 10) {	// do the following once a second
		tickCount = 0;		// reset the tick counter
		elapsedTime++;		// increment the elapsed time counter (in seconds)
	}
	if (hbCount == 20) {	// do the following every other second
		hbCount = 0;		// reset the heartbeat counter
		sendHB = true;		// note it is time to send a heartbeat message
	}
}

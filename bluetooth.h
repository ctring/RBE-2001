#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <BluetoothClient.h>
#include <BluetoothMaster.h>
#include <ReactorProtocol.h>
#include <TimerOne.h>

#define thisROBOT 14

void setupBluetooth();
void readBluetoothPacket();
void sendHeartbeat();

void timer1ISR();

#endif
#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include <stdlib.h>
#include <Arduino.h>

#define MCU1_ID 0x22
#define MCU2_ID 0x33

#define TYPE_HELLO 1
#define TYPE_QUERY_DATA_I2C 2


void CommunicationInit();
void SendPacket(char * message, uint8_t type); 
void ReceivePacket();
#endif
#include "communication.h"
#include <Arduino.h>
#include <stdlib.h>

// Package structure:
/*
start package indicator
package counter (nr)
ID sender
ID receiver
type
<optional fields>
payload
checksum
end indicator
*/

// package number
uint8_t p_nr = 0;

// Creating packages
void encoding(char * message) {

}

void CommunicationInit() {
	Serial.begin(9600);	
}

int calculateChecksum(char * message, uint8_t type, uint8_t p_nr) {
  // return 13 + length(MY_ID) + length(RECEIVER_ID) + length(message) + length(type) + length(checksum);
    return 22 + strlen(message);
}

 void SendPacket(char * message, uint8_t type) {
//void sendPacket(uint8_t message, uint8_t type) {
  // start indicator
  Serial.print("STX");
  Serial.print("0");
  if(p_nr < 10) {
    Serial.print(" ");
  } else if(p_nr >99) {
    p_nr = 0;
  }
  Serial.print(p_nr++);
  Serial.print(" ");
  // Sender ID
  Serial.print(MCU2_ID, HEX);
  // Receiver ID
  Serial.print(" ");
  Serial.print(MCU1_ID, HEX);

  Serial.print(" ");
  // Serial.print(QUERY_DATA_TYPE);
  Serial.print(type);
  Serial.print(" ");
  Serial.print(message);
  Serial.print(" ");

  int checksum = calculateChecksum(message, type, p_nr);
  Serial.print(checksum);

  Serial.print(" ");
  Serial.print("ETX");
}

// TODO
// Extracting data from packages
void DecodePacket() {

}

// MCU2 sends query to MCU1 to send data
void QuerySensorData() {
	SendPacket("QUERY_SENSOR_DATA", TYPE_QUERY_DATA_I2C);
}

void SendHello() {
	SendPacket("Hello!", TYPE_HELLO);
}

int ReceiveData() {
	// TODO
	// parseInt(Serial.read(....))
	int data = 10;
	return data;
}

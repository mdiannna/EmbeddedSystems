#include "communication.h"
#include <Arduino.h>

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


void CommunicationInit() {
	Serial.begin(9600);	
}

int calculateChecksum(char * message, uint8_t type, uint8_t p_nr) {
	// return 13 + length(MY_ID) + length(RECEIVER_ID) + length(message) + length(type) + length(checksum);
  	return 21 + strlen(message);
}

 void SendPacket(char * message, uint8_t type) {
//void sendPacket(uint8_t message, uint8_t type) {
	// start indicator
	Serial.print("STX");
	Serial.print(" ");
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
	Serial.println("ETX");

}

void ReceivePacket() {
	// while(Serial.available()) {
	// 	char c = Serial.read();
	// 	Serial.println("!!++++++++++++");
	// 	Serial.println(c);
	// 	Serial.println("!!++++++++++++");
	// }

	if(Serial.available()) {
		String in = Serial.readString();
		Serial.println("++++++++++++");
		Serial.println(in);
		Serial.println("++++++++++++");
	}
}
#include "communication.h"
#include <Arduino.h>
#include <stdlib.h>
#include <Stream.h>
#include <string.h>


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

// char mystr[100];
// char * mystr;
String mystr;

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
	Serial.print(" ");
	if(p_nr+1 < 10) {
		Serial.print(" ");
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
	Serial.println("ETX");

}

char * substring(char * s, int start, int n_chars) {
	char subbuff[n_chars+1];
	memcpy( subbuff, &s[start], n_chars );
	subbuff[n_chars] = '\0';
	return subbuff;
}

int ReceivePacket() {
	int validPacket = 1;

	mystr = Serial.readString(); //Read the serial data and store in var
  	Serial.println("----"+mystr+"----");

  	// size_t etx_pos = strstr(mystr, "ETX");
  	size_t etx_pos = mystr.indexOf("ETX");
  	Serial.print("ETX found at");
  	Serial.print(etx_pos);

  	// int messageLen = strlen(mystr);
  	int messageLen = etx_pos+3;
  	// char * startIndicator = substring(mystr,0, 3);
  	if(messageLen-6 <0) {
  		validPacket = 0;
  		Serial.println("PACKET NOT VALID");
  	} else {
		// char * checksum = substring(mystr, messageLen-6, 2);
		// char * endIndicator = substring(mystr, messageLen-3, 3);
		char * checksum;
		memcpy(checksum, &mystr[messageLen-6], 2 );
		// FOR DEBUG:
		Serial.println("--Message length:");
		Serial.print(messageLen);
		// Serial.println("--Start indicator:");
		// Serial.print(startIndicator);

		Serial.println("Checkum:");
		Serial.print(checksum);
		// Serial.println("--Start indicator:");
		// Serial.print(startIndicator);
	}
  	// if(... type==SEND_SENSOR_DATA) {

  	// 	return COMMAND_SEND_SENSOR_DATA;
  	// }
  	return 0;
}
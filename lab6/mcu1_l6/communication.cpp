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
	if(p_nr < 10) {
		Serial.print("0");
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

// char * mysubstring(char * s, int start, int n_chars) {
// 	char subbuff[n_chars+1];
// 	memcpy( subbuff, &s[start], n_chars );
// 	subbuff[n_chars] = '\0';
// 	return subbuff;
// }
	
int ReceivePacket() {
    int validPacket = 1;
    if(Serial.available() ){
    mystr = Serial.readString(); //Read the serial data and store in var
    Serial.println("--------------------------");
    Serial.println("----"+mystr+"----");
    Serial.println("--------------------------");

  	// size_t etx_pos = strstr(mystr, "ETX");
  	size_t stx_pos = mystr.indexOf("STX");
  	Serial.print("STX found at");
  	Serial.print(stx_pos);

  	if(stx_pos>2) {
  		validPacket = 0;
      Serial.println();
  		Serial.println("!!! PACKET NOT VALID !!!");
      Serial.println();
  		return -1;
  	} 
Serial.println();
  	size_t etx_pos = mystr.indexOf("ETX");
  	Serial.print("ETX found at");
  	Serial.println(etx_pos);

  	int messageLen = etx_pos+3;
  	// FOR DEBUG:
	Serial.print("--Message length:");
	Serial.println(messageLen);

  	if(messageLen-6 <0) {
  		validPacket = 0;
  		Serial.println("PACKET NOT VALID");
  		return -1;
  	} 

  	String checksum_s = mystr.substring(messageLen-6, messageLen-4);
  	Serial.print("Checkum:");
	  Serial.println(checksum_s);
   int checksum = checksum_s.toInt();
   Serial.println(checksum);

  if(checksum != messageLen) {
    validPacket = 0;
    Serial.println("PACKET NOT VALID");
    return -1;
  }
	
	String packageCnt = mystr.substring(4, 6);
	Serial.print("Package counter");
	Serial.println(packageCnt);
 Serial.println(packageCnt.toInt());

	String type_s = mystr.substring(13, 15);
	Serial.print("Type:");
	Serial.println(type_s);
  int type = type_s.toInt();
  Serial.println(type);
	return type;
  
//  	 if(type==COMMAND_SEND_SENSOR_DATA) {
//      Serial.println("COMMAND_SEND SENSOR_DATA");
//         return COMMAND_SEND_SENSOR_DATA;
//  	 }

  	return 0;
  }
  else {
    return -2;
  }
}

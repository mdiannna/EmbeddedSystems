
#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#define MCU1_ID 0x22
#define MCU2_ID 0x33

#define TYPE_HELLO 1
#define TYPE_QUERY_DATA_I2C 2

extern int data;

void CommunicationInit();
void QuerySensorData();
int ReceiveData();
void SendHello();


#endif

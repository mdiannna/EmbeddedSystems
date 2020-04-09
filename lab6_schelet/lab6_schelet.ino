#include"timer-api.h"
//https://github.com/sadr0b0t/arduino-timer-api/tree/master/src/avr
//https://habr.com/en/post/337430/

#define OFS_A 1000
#define REC_A 1000
int rec_cnt_A = OFS_A;


#define OFS_B 5000
#define REC_B 500
int rec_cnt_B = OFS_B;

void TaskA() {
 Serial.println("Task A");
}

void TaskB() {
 Serial.println("Task B"); 
}

void TaskC() {
  
}


void timer_handle_interrupts(int timer) {
  if(--rec_cnt_A <=0) {
    TaskA();
    rec_cnt_A = REC_A;
  }
  
  if(--rec_cnt_B <=0) {
    TaskA();
    rec_cnt_B = REC_B;
  }
  
}

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}

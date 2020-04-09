#include "tasks.h"

int rec_cnt_A = OFS_A;
int rec_cnt_B = OFS_B;

/**
* Taskul care genereaza date si stocheaza rezultatele intro variabila globala/semnal
*/
void TaskA() {
 Serial.println("Task Provider");
}

/**
* taskul care utilizeaza date, consumer, citeste variabila/semnalul produs de provider
*/
void TaskB() {
 Serial.println("Task Consumer"); 
}

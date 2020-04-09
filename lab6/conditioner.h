
#ifndef CONDITIONER_H_
#define CONDITIONER_H_


#define MAX_TEMP 26
#define MIN_TEMP 24

void ConditionerInit();
void TurnConditionerOn();
void TurnConditionerOff();
int IsConditionerTurnedOn();
int IsConditionerTurnedOff();

int TemperatureExceedsMaxTemp(double);
int TemperatureBelowMinTemp(double);


#endif

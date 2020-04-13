
//
//#define REC_BMPTP 7000
//#define OFFS_BMPTP 0


#define REC_TP 1000
#define OFFS_TP 500

#define REC_CONDIT_ON_OFF 10000 //10 sec
#define OFFS_CONDIT_ON_OFF 1500


extern float temperatureVal;
extern double pressureVal;
extern double relPressureVal;



// TP task code
void TaskReadTemperatureProvider();

// ConditOnOff code
void TaskConditionerOnOffConsumer();

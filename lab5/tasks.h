
//
//#define REC_BMPTP 7000
//#define OFFS_BMPTP 0


#define REC_BMPTP 3000
#define OFFS_BMPTP 500

#define REC_BMPPPC 7000
#define OFFS_BMPPPC 2000

#define REC_BMPRPC 7000
#define OFFS_BMPRPC 4000

#define REC_CONDIT_ON_OFF 10000 //10 sec
#define OFFS_CONDIT_ON_OFF 1500


extern double temperatureVal;
extern double pressureVal;
extern double relPressureVal;



// BMPTP task code
void TaskReadBMPTemperatureProvider();

// BMPTP task code
void TaskReadBMPPressureProviderConsumer() ;

// BMPRPC task code
void TaskReadBMPRelPressureConsumer();

// ConditOnOff code
void TaskConditionerOnOffConsumer();

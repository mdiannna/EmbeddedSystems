
//
//#define REC_BMPTP 7000
//#define OFFS_BMPTP 0


#define REC_TP 1000
#define OFFS_TP 1500

#define REC_CONDIT_ON_OFF 10000 //10 sec
#define OFFS_CONDIT_ON_OFF 2000

#define REC_GET_KPD 130
#define OFFS_GET_KPD 1000


#define REC_READ_SCHAR 500
#define OFFS_READ_SCHAR 550

#define REC_CHK_PWD 1000
#define OFFS_CHK_PWD 600


#define REC_TURN_LIGHTS_ON 1000
#define OFFS_TURN_LIGHTS_ON 1000

#define REC_BTN_LED_1 1000
#define OFFS_BTN_LED_1 300

extern float temperatureVal;
extern double pressureVal;
extern double relPressureVal;
extern char charKeypad;
extern int passwordIsCorrect;
extern char charSerial;

// TP task code
void TaskReadTemperatureProvider();

// ConditOnOff code
void TaskConditionerOnOffConsumer();

// GET_KPD code
void TaskReadKeypadCharPwd();

// READ_SCHAR code
// void TaskReadSerialChar();


// TASK_CHK_PWD
void TaskChechPassword();

// TURN_LIGHTS_ON
void TaskTurnCarLightsOn();

// BTN_LED_1
void TaskButtonLedLab1();

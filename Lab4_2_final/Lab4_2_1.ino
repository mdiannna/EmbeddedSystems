
// https://tutorial.cytron.io/2012/06/22/pid-for-embedded-design/
// Libraries:
// https://github.com/br3ttb/Arduino-PID-AutoTune-Library/blob/master/PID_AutoTune_v0
// https://github.com/br3ttb/Arduino-PID-Library/blob/master/



/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

//#include "PID_v1.h"
#define LIBRARY_VERSION  1.2.1

class PID
{


  public:

  //Constants used in some of the functions below
  #define AUTOMATIC 1
  #define MANUAL  0
  #define DIRECT  0
  #define REVERSE  1
  #define P_ON_M 0
  #define P_ON_E 1

  //commonly used functions **************************************************************************
    PID(double*, double*, double*,        // * constructor.  links the PID to the Input, Output, and 
        double, double, double, int, int);//   Setpoint.  Initial tuning parameters are also set here.
                                          //   (overload for specifying proportional mode)

    PID(double*, double*, double*,        // * constructor.  links the PID to the Input, Output, and 
        double, double, double, int);     //   Setpoint.  Initial tuning parameters are also set here
  
    void SetMode(int Mode);               // * sets PID to either Manual (0) or Auto (non-0)

    bool Compute();                       // * performs the PID calculation.  it should be
                                          //   called every time loop() cycles. ON/OFF and
                                          //   calculation frequency can be set using SetMode
                                          //   SetSampleTime respectively

    void SetOutputLimits(double, double); // * clamps the output to a specific range. 0-255 by default, but
                                          //   it's likely the user will want to change this depending on
                                          //   the application
  


  //available but not commonly used functions ********************************************************
    void SetTunings(double, double,       // * While most users will set the tunings once in the 
                    double);              //   constructor, this function gives the user the option
                                          //   of changing tunings during runtime for Adaptive control
    void SetTunings(double, double,       // * overload for specifying proportional mode
                    double, int);             

  void SetControllerDirection(int);   // * Sets the Direction, or "Action" of the controller. DIRECT
                      //   means the output will increase when error is positive. REVERSE
                      //   means the opposite.  it's very unlikely that this will be needed
                      //   once it is set in the constructor.
    void SetSampleTime(int);              // * sets the frequency, in Milliseconds, with which 
                                          //   the PID calculation is performed.  default is 100
                      
                      
                      
  //Display functions ****************************************************************
  double GetKp();             // These functions query the pid for interal values.
  double GetKi();             //  they were created mainly for the pid front-end,
  double GetKd();             // where it's important to know what is actually 
  int GetMode();              //  inside the PID.
  int GetDirection();           //

  private:
  void Initialize();
  
  double dispKp;        // * we'll hold on to the tuning parameters in user-entered 
  double dispKi;        //   format for display purposes
  double dispKd;        //
    
  double kp;                  // * (P)roportional Tuning Parameter
    double ki;                  // * (I)ntegral Tuning Parameter
    double kd;                  // * (D)erivative Tuning Parameter

  int controllerDirection;
  int pOn;

    double *myInput;              // * Pointers to the Input, Output, and Setpoint variables
    double *myOutput;             //   This creates a hard link between the variables and the 
    double *mySetpoint;           //   PID, freeing the user from having to constantly tell us
                                  //   what these values are.  with pointers we'll just know.
        
  unsigned long lastTime;
  double outputSum, lastInput;

  unsigned long SampleTime;
  double outMin, outMax;
  bool inAuto, pOnE;
};

// https://github.com/br3ttb/Arduino-PID-Library

/**********************************************************************************************
 * Arduino PID Library - Version 1.2.1
 * by Brett Beauregard <br3ttb@gmail.com> brettbeauregard.com
 *
 * This Library is licensed under the MIT License
 **********************************************************************************************/

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


/*Constructor (...)*********************************************************
 *    The parameters specified here are those for for which we can't set up
 *    reliable defaults, so we need to have the user set them.
 ***************************************************************************/
PID::PID(double* Input, double* Output, double* Setpoint,
        double Kp, double Ki, double Kd, int POn, int ControllerDirection)
{
    myOutput = Output;
    myInput = Input;
    mySetpoint = Setpoint;
    inAuto = false;

    PID::SetOutputLimits(0, 255);        //default output limit corresponds to
                        //the arduino pwm limits

    SampleTime = 100;             //default Controller Sample Time is 0.1 seconds

    PID::SetControllerDirection(ControllerDirection);
    PID::SetTunings(Kp, Ki, Kd, POn);

    lastTime = millis()-SampleTime;
}

/*Constructor (...)*********************************************************
 *    To allow backwards compatability for v1.1, or for people that just want
 *    to use Proportional on Error without explicitly saying so
 ***************************************************************************/

PID::PID(double* Input, double* Output, double* Setpoint,
        double Kp, double Ki, double Kd, int ControllerDirection)
    :PID::PID(Input, Output, Setpoint, Kp, Ki, Kd, P_ON_E, ControllerDirection)
{

}


/* Compute() **********************************************************************
 *     This, as they say, is where the magic happens.  this function should be called
 *   every time "void loop()" executes.  the function will decide for itself whether a new
 *   pid Output needs to be computed.  returns true when the output is computed,
 *   false when nothing has been done.
 **********************************************************************************/
bool PID::Compute()
{
   if(!inAuto) return false;
   unsigned long now = millis();
   unsigned long timeChange = (now - lastTime);
   if(timeChange>=SampleTime)
   {
      /*Compute all the working error variables*/
      double input = *myInput;
      double error = *mySetpoint - input;
      double dInput = (input - lastInput);
      outputSum+= (ki * error);

      /*Add Proportional on Measurement, if P_ON_M is specified*/
      if(!pOnE) outputSum-= kp * dInput;

      if(outputSum > outMax) outputSum= outMax;
      else if(outputSum < outMin) outputSum= outMin;

      /*Add Proportional on Error, if P_ON_E is specified*/
     double output;
      if(pOnE) output = kp * error;
      else output = 0;

      /*Compute Rest of PID Output*/
      output += outputSum - kd * dInput;

      if(output > outMax) output = outMax;
      else if(output < outMin) output = outMin;
      *myOutput = output;

      /*Remember some variables for next time*/
      lastInput = input;
      lastTime = now;
      return true;
   }
   else return false;
}

/* SetTunings(...)*************************************************************
 * This function allows the controller's dynamic performance to be adjusted.
 * it's called automatically from the constructor, but tunings can also
 * be adjusted on the fly during normal operation
 ******************************************************************************/
void PID::SetTunings(double Kp, double Ki, double Kd, int POn)
{
   if (Kp<0 || Ki<0 || Kd<0) return;

   pOn = POn;
   pOnE = POn == P_ON_E;

   dispKp = Kp; dispKi = Ki; dispKd = Kd;

   double SampleTimeInSec = ((double)SampleTime)/1000;
   kp = Kp;
   ki = Ki * SampleTimeInSec;
   kd = Kd / SampleTimeInSec;

  if(controllerDirection ==REVERSE)
   {
      kp = (0 - kp);
      ki = (0 - ki);
      kd = (0 - kd);
   }
}

/* SetTunings(...)*************************************************************
 * Set Tunings using the last-rembered POn setting
 ******************************************************************************/
void PID::SetTunings(double Kp, double Ki, double Kd){
    SetTunings(Kp, Ki, Kd, pOn); 
}

/* SetSampleTime(...) *********************************************************
 * sets the period, in Milliseconds, at which the calculation is performed
 ******************************************************************************/
void PID::SetSampleTime(int NewSampleTime)
{
   if (NewSampleTime > 0)
   {
      double ratio  = (double)NewSampleTime
                      / (double)SampleTime;
      ki *= ratio;
      kd /= ratio;
      SampleTime = (unsigned long)NewSampleTime;
   }
}

/* SetOutputLimits(...)****************************************************
 *     This function will be used far more often than SetInputLimits.  while
 *  the input to the controller will generally be in the 0-1023 range (which is
 *  the default already,)  the output will be a little different.  maybe they'll
 *  be doing a time window and will need 0-8000 or something.  or maybe they'll
 *  want to clamp it from 0-125.  who knows.  at any rate, that can all be done
 *  here.
 **************************************************************************/
void PID::SetOutputLimits(double Min, double Max)
{
   if(Min >= Max) return;
   outMin = Min;
   outMax = Max;

   if(inAuto)
   {
     if(*myOutput > outMax) *myOutput = outMax;
     else if(*myOutput < outMin) *myOutput = outMin;

     if(outputSum > outMax) outputSum= outMax;
     else if(outputSum < outMin) outputSum= outMin;
   }
}

/* SetMode(...)****************************************************************
 * Allows the controller Mode to be set to manual (0) or Automatic (non-zero)
 * when the transition from manual to auto occurs, the controller is
 * automatically initialized
 ******************************************************************************/
void PID::SetMode(int Mode)
{
    bool newAuto = (Mode == AUTOMATIC);
    if(newAuto && !inAuto)
    {  /*we just went from manual to auto*/
        PID::Initialize();
    }
    inAuto = newAuto;
}

/* Initialize()****************************************************************
 *  does all the things that need to happen to ensure a bumpless transfer
 *  from manual to automatic mode.
 ******************************************************************************/
void PID::Initialize()
{
   outputSum = *myOutput;
   lastInput = *myInput;
   if(outputSum > outMax) outputSum = outMax;
   else if(outputSum < outMin) outputSum = outMin;
}

/* SetControllerDirection(...)*************************************************
 * The PID will either be connected to a DIRECT acting process (+Output leads
 * to +Input) or a REVERSE acting process(+Output leads to -Input.)  we need to
 * know which one, because otherwise we may increase the output when we should
 * be decreasing.  This is called from the constructor.
 ******************************************************************************/
void PID::SetControllerDirection(int Direction)
{
   if(inAuto && Direction !=controllerDirection)
   {
      kp = (0 - kp);
      ki = (0 - ki);
      kd = (0 - kd);
   }
   controllerDirection = Direction;
}

/* Status Funcions*************************************************************
 * Just because you set the Kp=-1 doesn't mean it actually happened.  these
 * functions query the internal state of the PID.  they're here for display
 * purposes.  this are the functions the PID Front-end uses for example
 ******************************************************************************/
double PID::GetKp(){ return  dispKp; }
double PID::GetKi(){ return  dispKi;}
double PID::GetKd(){ return  dispKd;}
int PID::GetMode(){ return  inAuto ? AUTOMATIC : MANUAL;}
int PID::GetDirection(){ return controllerDirection;}





//#include "PID_AutoTune_v0.h"

// class PID_ATune
// {


//   public:
//   //commonly used functions **************************************************************************
//     PID_ATune(double*, double*);                         // * Constructor.  links the Autotune to a given PID
//     int Runtime();                        // * Similar to the PID Compue function, returns non 0 when done
//   void Cancel();                      // * Stops the AutoTune 
  
//   void SetOutputStep(double);               // * how far above and below the starting value will the output step? 
//   double GetOutputStep();                 // 
  
//   void SetControlType(int);                 // * Determies if the tuning parameters returned will be PI (D=0)
//   int GetControlType();                 //   or PID.  (0=PI, 1=PID)     
  
//   void SetLookbackSec(int);             // * how far back are we looking to identify peaks
//   int GetLookbackSec();               //
  
//   void SetNoiseBand(double);              // * the autotune will ignore signal chatter smaller than this value
//   double GetNoiseBand();                //   this should be acurately set
  
//   double GetKp();                   // * once autotune is complete, these functions contain the
//   double GetKi();                   //   computed tuning parameters.  
//   double GetKd();                   //
  
//   private:
//     void FinishUp();
//   bool isMax, isMin;
//   double *input, *output;
//   double setpoint;
//   double noiseBand;
//   int controlType;
//   bool running;
//   unsigned long peak1, peak2, lastTime;
//   int sampleTime;
//   int nLookBack;
//   int peakType;
//   double lastInputs[101];
//     double peaks[10];
//   int peakCount;
//   bool justchanged;
//   bool justevaled;
//   double absMax, absMin;
//   double oStep;
//   double outputStart;
//   double Ku, Pu;
  
// };



// //#include <PID_AutoTune_v0.h>


// PID_ATune::PID_ATune(double* Input, double* Output)
// {
//   input = Input;
//   output = Output;
//   controlType =0 ; //default to PI
//   noiseBand = 0.5;
//   running = false;
//   oStep = 30;
//   SetLookbackSec(10);
//   lastTime = millis();
  
// }



// void PID_ATune::Cancel()
// {
//   running = false;
// } 
 
// int PID_ATune::Runtime()
// {
//   justevaled=false;
//   if(peakCount>9 && running)
//   {
//     running = false;
//     FinishUp();
//     return 1;
//   }
//   unsigned long now = millis();
  
//   if((now-lastTime)<sampleTime) return false;
//   lastTime = now;
//   double refVal = *input;
//   justevaled=true;
//   if(!running)
//   { //initialize working variables the first time around
//     peakType = 0;
//     peakCount=0;
//     justchanged=false;
//     absMax=refVal;
//     absMin=refVal;
//     setpoint = refVal;
//     running = true;
//     outputStart = *output;
//     *output = outputStart+oStep;
//   }
//   else
//   {
//     if(refVal>absMax)absMax=refVal;
//     if(refVal<absMin)absMin=refVal;
//   }
  
//   //oscillate the output base on the input's relation to the setpoint
  
//   if(refVal>setpoint+noiseBand) *output = outputStart-oStep;
//   else if (refVal<setpoint-noiseBand) *output = outputStart+oStep;
  
  
//   //bool isMax=true, isMin=true;
//   isMax=true;isMin=true;
//   //id peaks
//   for(int i=nLookBack-1;i>=0;i--)
//   {
//     double val = lastInputs[i];
//     if(isMax) isMax = refVal>val;
//     if(isMin) isMin = refVal<val;
//     lastInputs[i+1] = lastInputs[i];
//   }
//   lastInputs[0] = refVal;  
//   if(nLookBack<9)
//   {  //we don't want to trust the maxes or mins until the inputs array has been filled
//   return 0;
//   }
  
//   if(isMax)
//   {
//     if(peakType==0)peakType=1;
//     if(peakType==-1)
//     {
//       peakType = 1;
//       justchanged=true;
//       peak2 = peak1;
//     }
//     peak1 = now;
//     peaks[peakCount] = refVal;
   
//   }
//   else if(isMin)
//   {
//     if(peakType==0)peakType=-1;
//     if(peakType==1)
//     {
//       peakType=-1;
//       peakCount++;
//       justchanged=true;
//     }
    
//     if(peakCount<10)peaks[peakCount] = refVal;
//   }
  
//   if(justchanged && peakCount>2)
//   { //we've transitioned.  check if we can autotune based on the last peaks
//     double avgSeparation = (abs(peaks[peakCount-1]-peaks[peakCount-2])+abs(peaks[peakCount-2]-peaks[peakCount-3]))/2;
//     if( avgSeparation < 0.05*(absMax-absMin))
//     {
//     FinishUp();
//       running = false;
//     return 1;
   
//     }
//   }
//    justchanged=false;
//   return 0;
// }
// void PID_ATune::FinishUp()
// {
//     *output = outputStart;
//       //we can generate tuning parameters!
//       Ku = 4*(2*oStep)/((absMax-absMin)*3.14159);
//       Pu = (double)(peak1-peak2) / 1000;
// }

// double PID_ATune::GetKp()
// {
//   return controlType==1 ? 0.6 * Ku : 0.4 * Ku;
// }

// double PID_ATune::GetKi()
// {
//   return controlType==1? 1.2*Ku / Pu : 0.48 * Ku / Pu;  // Ki = Kc/Ti
// }

// double PID_ATune::GetKd()
// {
//   return controlType==1? 0.075 * Ku * Pu : 0;  //Kd = Kc * Td
// }

// void PID_ATune::SetOutputStep(double Step)
// {
//   oStep = Step;
// }

// double PID_ATune::GetOutputStep()
// {
//   return oStep;
// }

// void PID_ATune::SetControlType(int Type) //0=PI, 1=PID
// {
//   controlType = Type;
// }
// int PID_ATune::GetControlType()
// {
//   return controlType;
// }
  
// void PID_ATune::SetNoiseBand(double Band)
// {
//   noiseBand = Band;
// }

// double PID_ATune::GetNoiseBand()
// {
//   return noiseBand;
// }

// void PID_ATune::SetLookbackSec(int value)
// {
//     if (value<1) value = 1;
  
//   if(value<25)
//   {
//     nLookBack = value * 4;
//     sampleTime = 250;
//   }
//   else
//   {
//     nLookBack = 100;
//     sampleTime = value*10;
//   }
// }

// int PID_ATune::GetLookbackSec()
// {
//   return nLookBack * sampleTime / 1000;
// }





//#include "motor.h"

// Motor A
#define enA 10
#define in1 11
#define in2 12

void InitMotor();
void MotorForward(int speed);
void MotorBackward(int speed);
void MotorStop();




void InitMotor() {
  pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT); 
}

void MotorForward(int speed) {
  
  digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA,speed);
}

void MotorBackward(int speed) {
  digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // analogWrite(enA,PowerToSpeed(power));
    analogWrite(enA,speed);
}

void MotorStop() {
  digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(enA,0); 
}

//#include "encoder.h"

#define ENCODER_PIN 6 // change


int maxTimeOneRotation;

void EncoderInit() {
   pinMode(ENCODER_PIN,INPUT);
  MotorForward(165);

  delay(1000);
  
  MotorForward(255);
    delay(3000);
  
    while(ReadEncoderValue()!=1);
      unsigned long startTime = millis();
 delay(50);
     while(ReadEncoderValue()!=1);
    unsigned long elapsedTime = millis()-startTime;
     //MotorStop();
    Serial.println("max time 1 rotation:");
    Serial.println(elapsedTime);
    maxTimeOneRotation = elapsedTime;
    delay(3000);
}
double ReadEncoderValue() {
   int value = digitalRead(ENCODER_PIN);
  
 // Serial.println("Encoder value:");
 // Serial.println(value);
 return value;
  
}






double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
// Kp, Ki, Kd
PID myPID(&Input, &Output, &Setpoint,600,100,10, DIRECT);
PID_ATune aTune(&Input, &Output);

/*********
 * ADDED CODE
 */
bool tuning;
byte ATuneModeRemember=2;
double aTuneStep=50, aTuneNoise=1, aTuneStartValue=100;
unsigned int aTuneLookBack=20;
double kp=2,ki=0.5,kd=2;
/**************/



// void changeAutoTune()
// {
//  if(!tuning)
//   {
//     //Set the output to the desired starting frequency.
//     Output=aTuneStartValue;
//     aTune.SetNoiseBand(aTuneNoise);
//     aTune.SetOutputStep(aTuneStep);
//     aTune.SetLookbackSec((int)aTuneLookBack);
//     AutoTuneHelper(true);
//     tuning = true;
//   }
//   else
//   { //cancel autotune
//     aTune.Cancel();
//     tuning = false;
//     AutoTuneHelper(false);
//   }
// }



void PID_Init() {
  //turn the PID on
  myPID.SetMode(AUTOMATIC);

  //kp = aTune.GetKp();
 // ki = aTune.GetKi();
 // kd = aTune.GetKd();
 // myPID.SetTunings(kp,ki,kd);
}

void SerialInit() {
   Serial.begin(9600);
}

unsigned long currentTime;
unsigned long prevTime;


void TimeInit() {
  currentTime = millis();
  prevTime = millis();
}
void setup()
{
  TimeInit();
  SerialInit();
  // //initialize the variables we're linked to
  // Input = ReadEncoderValue();
  
  // Serial.println("Input:");
  Setpoint = 230;

  //AutoTuneInit();
  EncoderInit();
// TunePID();
  PID_Init(); 
 
   
}
 int counter = 0;
 int angle = 0; 
 int aState;
 int aLastState; 


double CalculateMotorSpeed(unsigned long time_1_rotation) {
  //return 1000.0/time_1_rotation;
  return 10000/time_1_rotation;
}

unsigned long CalculateElapsedTime(unsigned long prevTime, unsigned long currentTime) {
  return currentTime - prevTime;
}

int AdjustKp(int kp, int ki, int kd) {
  Serial.println("Adjust kp");
  Serial.println(kp);
  myPID.Compute();
  //Wait for overshooting
  while(Output <Setpoint) {
     Serial.println("kp:");
  Serial.println(kp);
   Serial.println("Output:");
  Serial.println(Output);
   Serial.println("Input:");
  Serial.println(Input);
   Serial.println("Setpoint");
  Serial.println(Setpoint);
  kp+=100;
    myPID.SetTunings(kp,ki,kd);

  myPID.Compute();
  }
  Serial.println("kp overshooting");
  Serial.println(kp);
  kp = kp/2;
  Serial.println(kp);
  return kp;
}

int AdjustKi(int kp, int ki, int kd) {
  
  myPID.SetTunings(kp,ki,kd);
myPID.Compute();
  while(Output <Setpoint) {
  ki=10; 
  myPID.SetTunings(kp,ki,kd);

 
  myPID.Compute();

  Serial.println("ki overshooting");
  Serial.println(ki);
  ki = ki/2;
  AdjustKp(kp,ki,kd);
  Serial.println(ki);
  }
  return ki;
}

int AdjustKd(int kp, int ki, int kd) {
    kd++;
    return kd;
}

void TunePID() {
  Serial.println("Tune PID");
  int kp = 1;
  int ki = 1;
  int kd = 1;
  Output = 0;
  Setpoint = 200;
  Input = maxTimeOneRotation/2;
  
  kp = 10;
    myPID.SetTunings(kp,ki,kd);

  kp = AdjustKp(kp, ki, kd);
  myPID.SetTunings(kp,ki,kd);
  
  ki = 10;
  myPID.SetTunings(kp,ki,kd);
  kp = AdjustKp(kp,ki,kd);
  myPID.SetTunings(kp,ki,kd);
  ki = AdjustKi(kp, ki, kd);
  myPID.SetTunings(kp,ki,kd);
  
  kd = 3;
  myPID.SetTunings(kp,ki,kd);
  kp = AdjustKp(kp,ki,kd);
  myPID.SetTunings(kp,ki,kd);
  ki = AdjustKi(kp, ki, kd);
  myPID.SetTunings(kp,ki,kd);
  kd = AdjustKd(kp, ki, kd);
  myPID.SetTunings(kp,ki,kd);

  Serial.println("--------");
  Serial.println("test after adjunsting:");
  myPID.Compute();
  Serial.println("Output:");
  Serial.println(Output);
  Serial.println("Setpoint:");
  Serial.println("Setpoint");
  
}

int motorSpeed; 
void loop()
{
  
  // O rotatie completa
  if(ReadEncoderValue()==1) {
    prevTime = currentTime;
  currentTime = millis();

    //TODO:calculate Speed
  //  motorSpeed = 110;
    unsigned long elapsedTime = CalculateElapsedTime(prevTime, currentTime);
    Serial.println("Elapsed Time:");
    Serial.println(elapsedTime);
    motorSpeed = CalculateMotorSpeed(elapsedTime);
    Serial.println("---Motor speed:----");
    Serial.println(motorSpeed);
  }
  Input = motorSpeed;
  Serial.println("Input:");
 Serial.print(Input);
  Input = map(Input, 0, maxTimeOneRotation, 0, 255);  //Scales 0-1023 to 0-255 (or whatever you want)
  myPID.Compute();

  Serial.println("Input:");
  Serial.print(Input);
  Serial.println("Output:");
  Serial.print(Output);
  
  MotorForward(Output);
 
}

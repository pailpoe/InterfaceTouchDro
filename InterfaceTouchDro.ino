//Interface touch dro
//Pailpoe, 2020
#include "HardwareTimer.h"


#define OUT_LED PC13

//Hard timer 1 for X scale : T1C1 (PA8) and T1C2 (PA9)
HardwareTimer timer_X(1);
//Hard timer 3 for Y scale : T3C1 (PA6) and T3C2 (PA7)  
HardwareTimer timer_Y(3);
//Hard timer 2 for Z scale : T2C1 (PA0) and T2C2 (PA1)  
HardwareTimer timer_Z(2);
//Hard timer 2 for W scale : T4C1 (PB6) and T4C2 (PB7)  
HardwareTimer timer_W(4);

//Variable overflow counter
long lOverflowX = 0;
long lOverflowY = 0;
long lOverflowZ = 0;
long lOverflowW = 0;

//******************  IT function
void IT_Handler_Quadrature_X()
{
  if (timer_X.getDirection()) lOverflowX--;
  else lOverflowX++;
}
void IT_Handler_Quadrature_Y()
{
  if (timer_Y.getDirection())lOverflowY--;
  else lOverflowY++;
}
void IT_Handler_Quadrature_Z()
{
  if (timer_Z.getDirection())lOverflowZ--;
  else lOverflowZ++; 
}
void IT_Handler_Quadrature_W()
{
  if (timer_W.getDirection())lOverflowW--;
  else lOverflowW++;
}
void SysTick_Handler() 
{ 
  //TestSys++;
}
void setup()   
{
  /* Systick */ 
  systick_attach_callback(SysTick_Handler);
  /* IO config */ 
  pinMode(OUT_LED, OUTPUT);
  digitalWrite(OUT_LED, LOW);
  pinMode(PA8, INPUT_PULLUP); 
  pinMode(PA9, INPUT_PULLUP);
  pinMode(PA6, INPUT_PULLUP);
  pinMode(PA7, INPUT_PULLUP);
  pinMode(PA0, INPUT_PULLUP);
  pinMode(PA1, INPUT_PULLUP);
  pinMode(PB6, INPUT_PULLUP);
  pinMode(PB7, INPUT_PULLUP); 
  /* Quadratrure decoder */   
  SetTimerAsQuadratureEncoder(&timer_X,IT_Handler_Quadrature_X);
  SetTimerAsQuadratureEncoder(&timer_Y,IT_Handler_Quadrature_Y);
  SetTimerAsQuadratureEncoder(&timer_Z,IT_Handler_Quadrature_Z);
  SetTimerAsQuadratureEncoder(&timer_W,IT_Handler_Quadrature_W);
  /* Serial 2 */ 
  Serial2.begin(38400);
}

void loop() 
{
    long Xvalue;
    long Yvalue;
    long Zvalue;
    long Wvalue;
    char bufferChar[16];
    //Update encoder    
    Xvalue = (long)timer_X.getCount() + lOverflowX * 65536;
    Yvalue = (long)timer_Y.getCount() + lOverflowY * 65536; 
    Zvalue = (long)timer_Z.getCount() + lOverflowZ * 65536; 
    Wvalue = (long)timer_W.getCount() + lOverflowW * 65536;     
    
    delay(50);
    digitalWrite(OUT_LED, !digitalRead(OUT_LED));
    sprintf(bufferChar,"X%ld;",Xvalue);
    Serial2.print(bufferChar);
    sprintf(bufferChar,"Y%ld;",Yvalue);
    Serial2.print(bufferChar);
    sprintf(bufferChar,"Z%ld;",Zvalue);
    Serial2.print(bufferChar);
    sprintf(bufferChar,"W%ld;",Wvalue);
    Serial2.print(bufferChar);     
}

void SetTimerAsQuadratureEncoder(HardwareTimer *timerConf,voidFuncPtr handler) 
{
  timerConf->pause(); //stop... 
  timerConf->setMode(0, TIMER_ENCODER); //set mode, the channel is not used when in this mode. 
  timerConf->setPrescaleFactor(1); //normal for encoder to have the lowest or no prescaler. 
  timerConf->setOverflow(0xFFFF);    
  timerConf->setCount(0);          //reset the counter. 
  timerConf->setEdgeCounting(TIMER_SMCR_SMS_ENCODER3); //or TIMER_SMCR_SMS_ENCODER1 or TIMER_SMCR_SMS_ENCODER2. This uses both channels to count and ascertain direction. 
  timerConf->attachInterrupt(0, handler); //Overflow interrupt  
  timerConf->resume();                 //start the encoder... 
}

//Interface touch dro
#include "HardwareTimer.h"
#include "QuadDecoder.h"

#define OUT_LED PC13

//Hard timer 1 for X scale quadrature : T1C1 (PA8) and T1C2 (PA9)
HardwareTimer timer_X(1);
//Hard timer 3 for Y scale quadrature : T3C1 (PA6) and T3C2 (PA7)  
HardwareTimer timer_Y(3);
//Hard timer 2 for Z scale quadrature : T2C1 (PA0) and T2C2 (PA1)  
HardwareTimer timer_Z(2);

//Quad decoder Class
QuadDecoder Quad_X(512,false,false);
QuadDecoder Quad_Y(512,false,false);
QuadDecoder Quad_Z(512,false,false);




//******************  IT function
void IT_Overflow_X(){
if (timer_X.getDirection()){
  Quad_X.OverflowMinus();
} else{
  Quad_X.OverflowPlus();
}
}
void IT_Overflow_Y(){
if (timer_Y.getDirection()){
   Quad_Y.OverflowMinus();
} else{
  Quad_Y.OverflowPlus();
}
}
void IT_Overflow_Z(){
if (timer_Z.getDirection()){
   Quad_Z.OverflowMinus();
} else{
  Quad_Z.OverflowPlus();
}
}
void SysTick_Handler() 
{ 
  //TestSys++;
}



void setup()   {

 
  //Test led PC13
  pinMode(OUT_LED, OUTPUT);  //
  digitalWrite(OUT_LED, LOW);

  /* Systick used by I2C at 1Khz... */ 
  systick_attach_callback(SysTick_Handler);


  
  //## configure timer_X as quadrature encoder ##
  pinMode(PA8, INPUT_PULLUP);  //channel A
  pinMode(PA9, INPUT_PULLUP);  //channel B
  timer_X.setMode(0, TIMER_ENCODER); //set mode, the channel is not used when in this mode. 
  timer_X.pause(); //stop... 
  timer_X.setPrescaleFactor(1); //normal for encoder to have the lowest or no prescaler. 
  timer_X.setOverflow(0xFFFF);    
  timer_X.setCount(0);          //reset the counter. 
  timer_X.setEdgeCounting(TIMER_SMCR_SMS_ENCODER3); //or TIMER_SMCR_SMS_ENCODER1 or TIMER_SMCR_SMS_ENCODER2. This uses both channels to count and ascertain direction. 
  timer_X.attachInterrupt(0, IT_Overflow_X); //Overflow interrupt  
  timer_X.resume();                 //start the encoder... 
  //timer_X.getCount();

  //## configure timer_Y as quadrature encoder ##
  pinMode(PA6, INPUT_PULLUP);  //channel A
  pinMode(PA7, INPUT_PULLUP);  //channel B
  timer_Y.setMode(0, TIMER_ENCODER); //set mode, the channel is not used when in this mode. 
  timer_Y.pause(); //stop... 
  timer_Y.setPrescaleFactor(1); //normal for encoder to have the lowest or no prescaler. 
  timer_Y.setOverflow(0xFFFF);    
  timer_Y.setCount(0);          //reset the counter. 
  timer_Y.setEdgeCounting(TIMER_SMCR_SMS_ENCODER3); //or TIMER_SMCR_SMS_ENCODER1 or TIMER_SMCR_SMS_ENCODER2. This uses both channels to count and ascertain direction. 
  timer_Y.attachInterrupt(0, IT_Overflow_Y); //Overflow interrupt  
  timer_Y.resume();                 //start the encoder... 
  //timer_Y.getCount();

  //## configure timer_Z as quadrature encoder ##
  pinMode(PA0, INPUT_PULLUP);  //channel A
  pinMode(PA1, INPUT_PULLUP);  //channel B
  timer_Z.setMode(0, TIMER_ENCODER); //set mode, the channel is not used when in this mode. 
  timer_Z.pause(); //stop... 
  timer_Z.setPrescaleFactor(1); //normal for encoder to have the lowest or no prescaler. 
  timer_Z.setOverflow(0xFFFF);    
  timer_Z.setCount(0);          //reset the counter. 
  timer_Z.setEdgeCounting(TIMER_SMCR_SMS_ENCODER3); //or TIMER_SMCR_SMS_ENCODER1 or TIMER_SMCR_SMS_ENCODER2. This uses both channels to count and ascertain direction. 
  timer_Z.attachInterrupt(0, IT_Overflow_Z); //Overflow interrupt  
  timer_Z.resume();                 //start the encoder... 
  //timer_Z.getCount();

  Serial2.begin(38400);
}

void loop() 
{
    long Xvalue;
    long Yvalue;
    long Zvalue;
    char bufferChar[16];
    //Update encoder
    Quad_X.CounterValue(timer_X.getCount());
    Quad_Y.CounterValue(timer_Y.getCount());
    Quad_Z.CounterValue(timer_Z.getCount());
    Xvalue = Quad_X.GetValuelong(); 
    Yvalue = Quad_Y.GetValuelong(); 
    Zvalue = Quad_Z.GetValuelong(); 
   
    delay(50);
    digitalWrite(OUT_LED, !digitalRead(OUT_LED));
    sprintf(bufferChar,"X%ld;",Xvalue);
    Serial2.print(bufferChar);
    sprintf(bufferChar,"Y%ld;",Yvalue);
    Serial2.print(bufferChar);
    sprintf(bufferChar,"Z%ld;",Zvalue);
    Serial2.print(bufferChar);    
}

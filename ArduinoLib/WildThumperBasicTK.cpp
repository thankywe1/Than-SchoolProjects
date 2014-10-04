/*
	File Name  = WildThumperBasicTK.cpp
	Programmer = Than Kywe [Yonathan Phoenix]
	Date 	   = 07/16/2013
*/
#include "..\Servo.h"
#include "WildThumperBasicTK.h"

WildThumperBasicTK::WildThumperBasicTK(int charger){
  //This part is from the WildThumper sample
  //----------------------------- Initialize Servos ----------------------------------------------------

  Servo0.attach(S0);                     // attach servo to I/O pin
  Servo1.attach(S1);                     // attach servo to I/O pin
  Servo2.attach(S2);                     // attach servo to I/O pin
  Servo3.attach(S3);                     // attach servo to I/O pin
  Servo4.attach(S4);                     // attach servo to I/O pin
  Servo5.attach(S5);                     // attach servo to I/O pin
  Servo6.attach(S6);                     // attach servo to I/O pin

  //------------------------------ Set servos to default position ---------------------------------------

  Servo0.writeMicroseconds(DServo0);     // set servo to default position
  Servo1.writeMicroseconds(DServo1);     // set servo to default position
  Servo2.writeMicroseconds(DServo2);     // set servo to default position
  Servo3.writeMicroseconds(DServo3);     // set servo to default position
  Servo4.writeMicroseconds(DServo4);     // set servo to default position
  Servo5.writeMicroseconds(DServo5);     // set servo to default position
  Servo6.writeMicroseconds(DServo6);     // set servo to default position

  //------------------------------ Initialize I/O pins --------------------------------------------------

  pinMode (charger,OUTPUT);              // change Charger pin to output
  digitalWrite (charger,1);              // disable current regulator to charge battery

  if (Cmode==1) 
  {
    Serial.begin(Brate);                 // enable serial communications if Cmode=1
    Serial.flush();                      // flush buffer
  } 
  //Serial.begin(57600);
  ch = charger;	
}

void WildThumperBasicTK::RCMode(){
void RCmode()
{
  //This part is from the WildThumper sample	
  //------------------------- Code for Radio Controlled inputs ---------------------------------------------------------

  Speed=pulseIn(RCleft,HIGH,25000);             // read throttle/left stick
  Steer=pulseIn(RCright,HIGH,25000);            // read steering/right stick


  if (Speed==0) Speed=1500;                     // if pulseIn times out (25mS) then set speed to stop
  if (Steer==0) Steer=1500;                     // if pulseIn times out (25mS) then set steer to centre

  if (abs(Speed-1500)<RCdeadband) Speed=1500;   // if Speed input is within deadband set to 1500 (1500uS=center position for most servos)
  if (abs(Steer-1500)<RCdeadband) Steer=1500;   // if Steer input is within deadband set to 1500 (1500uS=center position for most servos)

  if (Mix==1)                                   // Mixes speed and steering signals
  {
    Steer=Steer-1500;
    Leftspeed=Speed-Steer;
    Rightspeed=Speed+Steer;
  }
  else                                          // Individual stick control
  {
    Leftspeed=Speed;
    Rightspeed=Steer;
  }
 
  Leftmode=2;
  Rightmode=2;
  if (Leftspeed>(Leftcenter+RCdeadband)) Leftmode=0;          // if left input is forward then set left mode to forward
  if (Rightspeed>(Rightcenter+RCdeadband)) Rightmode=0;       // if right input is forward then set right mode to forward

  LeftPWM=abs(Leftspeed-Leftcenter)*10/scale;                 // scale 1000-2000uS to 0-255
  LeftPWM=min(LeftPWM,255);                                   // set maximum limit 255

  RightPWM=abs(Rightspeed-Rightcenter)*10/scale;              // scale 1000-2000uS to 0-255
  RightPWM=min(RightPWM,255);                                 // set maximum limit 255

}

void WildThumperBasicTK::SerialMode(){
  //This pat is modified by Than Kywe[Yonathan Phoenix]. 

  if (Serial.available()>1)            // command available
  {
    int A=Serial.read();
    int B=Serial.read();
    int command=A*256+B;
    switch (command)
    {
      case 17996:                      // FL
        Serial.flush();                // flush buffer
        break;
        
      case 16718:                           // AN - return values of analog inputs 1-5
        for (int i=1;i<6;i++)               // index analog inputs 1-5
        {
          data=analogRead(i);               // read 10bit analog input 
          Serial.write(highByte(data));     // transmit high byte
          Serial.write(lowByte(data));      // transmit low byte
        }
        break;
              
       case 21334:                          // SV - receive postion information for servos 0-6
         for (int i=0;i<15;i++)             // read 14 bytes of data
         {
           Serialread();                                      
           servo[i]=data;
         }
         Servo0.writeMicroseconds(servo[0]*256+servo[1]);     // set servo position
         Servo1.writeMicroseconds(servo[2]*256+servo[3]);     // set servo position
         Servo2.writeMicroseconds(servo[4]*256+servo[5]);     // set servo position
         Servo3.writeMicroseconds(servo[6]*256+servo[7]);     // set servo position
         Servo4.writeMicroseconds(servo[8]*256+servo[9]);     // set servo position
         Servo5.writeMicroseconds(servo[10]*256+servo[11]);   // set servo position
         Servo6.writeMicroseconds(servo[12]*256+servo[13]);   // set servo position
         break;
       
       case 18498:                          // HB - mode and PWM data for left and right motors
         Serialread();
         Leftmode=data;
         Serialread();
         LeftPWM=data;
         Serialread();
         Rightmode=data;
         Serialread();
         RightPWM=data;
         break;
         
       default:                             // invalid command
         Serial.flush();                    // flush buffer
    }
  }

}

void WildThumperBasicTK::SerialRead(){
  do 
  {
    data=Serial.read();
  } while (data<0);

}


void WildThumperBasicTK::ITwoCMode(){

}

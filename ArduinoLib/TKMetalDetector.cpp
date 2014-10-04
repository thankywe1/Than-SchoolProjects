/*
    Progranmmer   Than Kywe
    Description   This is one of libraries file for my Arduino Project. The sensor I used in this project is metal detector. I 
                  applied these codes in my school Senior Design project for my computer engineering. This part is to detect metal 
                  from the robot and send message to stop servo motor if metal is found.
    File          TKMetalDetector.cpp 
*/
#include "TKMetalDetector.h"

TKMetalDetector::TKMetalDetector(int aPin, int bRate){
  analogPin = aPin;
  baudRate = bRate;
  Serial.begin(baudRate);
}

TKMetalDetector::~TKMetalDetector(){
  //something  
}

int TKMetalDetector::getValue(){
  return analogRead(analogPin);
}

void TKMetalDetector::displayValueOnSM(int val){
  if (val > 0){
   Serial.print("Analog Read: ");
   Serial.println(val); 
  }
}

bool TKMetalDetector::mineDetected(int rValue){
   return false;
   if(rValue > 10){
 	return true;
	displayValueOnSM(rValue);
   }
}

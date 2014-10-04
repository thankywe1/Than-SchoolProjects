/*
    Programmer    Than Kywe
    Description   This is one of libraries file for my Arduino Project. The sensor I used in this project is Ultrasonic HC-SR04. I 
                  applied these codes in my school Senior Design project for my computer engineering. This part is to detect block 
                  from  my Arduino-Robot so that robot can avoid from hitting barriers or blocks.
    File          TKBlockDetector.cpp 
*/
#include "TKBlockDetector.h"

TKBlockDetector::TKBlockDetector(int iPin, int oPin, int bRate){
  inputPin = iPin;
  outputPin = oPin;
  baudRate = bRate;
  distance = 0;
  Serial.begin(baudRate);
}

TKBlockDetector::~TKBlockDetector(){
  //something  
}

void TKBlockDetector::setupStage(){
  Serial.begin(9600);
  pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT);
}

void TKBlockDetector::getDistance(){
  digitalWrite(outputPin, LOW);		//send low pulse
  delayMicroseconds(2);			//delay for 2uS
  digitalWrite(outputPin, HIGH);	//send high pulse
  delayMicroseconds(10);		//delay for 10uS
  digitalWrite(outputPin, LOW);		//back to low pulse
  distance = pulseIn(inputPin, HIGH);
  distance = distance/74/2;
  //return distance;
}

void TKBlockDetector::distInInches(){
  getDistance();
  //return distance;	
}

void TKBlockDetector::displayDistanceOfBlock(){
   //getDistance();
   Serial.print("Distance of block: ");
   Serial.println(distance); 
}

bool TKBlockDetector::foundBlock(){
   return false;
   if(distance < 13){
 	return true;
	//displayValueOnSM(rValue);
   }
}

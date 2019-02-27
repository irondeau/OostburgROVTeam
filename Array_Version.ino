#include <Servo.h>
#include <Utility.h>
int serialVal = 30; // TODO change 0 value in processing and on this line

Servo rockDrop;
Servo fishFry;
Servo mainGripper; 

int depthSensor = A0;
int depthValue = 0;
int depthCount = 0; // TODO Make local timer not have here (make local variable) 

int motorDirectionPins[] = {22, 24, 26, 28, 30};
int motorPWMPins[] = {9, 10, 11, 12, 13};

int motorDirectionFB1 = LOW;
int motorDirectionFB2 = HIGH;
int motorDirectionLR1 = LOW;
int motorDirectionLR2 = HIGH;

void setup() {

  foreach(motorDirectionPins, 4, pinMode, OUTPUT);
  foreach(motorPWMPins, 4, pinMode, OUTPUT);
  
  pinMode(depthSensor, INPUT);

  rockDrop.attach(1);
  fishFry.attach(2);
  mainGripper.attach(3);
  
  Serial.begin(9600);
}

void loop() {

  int inputHigh;
  int inputLow;
  int outputHigh;
  int outputLow;
  int directionPins;
  int PWMPins;
  int motorDirection;

  //Controller Input from Processsing 
  if(Serial.available() > 0) {
    serialVal = Serial.read(); //Read the serial value from processing and set it to variable serialVal
  }

  //Depth Sensor
  if(depthCount < 10000) {

   depthCount++;
   
  } else {
    
   depthValue = analogRead(depthSensor);
   depthValue = depthValue;
   Serial.println(depthValue);

   depthCount = 0;
   
  }
  
  //Left Joystick
  if(serialVal <= 28 && serialVal >= 0) {         //Between values 0 and 32
    inputLow = 28;                                 //May have to reverse the input values 
    inputHigh = 0;
    outputLow = 0;
    outputHigh = 255;
    
    theFunction(serialVal, inputLow, inputHigh, outputLow, outputHigh, motorDirectionPins[0], motorPWMPins[0], motorDirectionFB1); 

      } else if(serialVal < 32) {
        
        analogWrite(motorPWMPins[0], 0);
      
      } else if(serialVal <= 64) {
        inputLow = 32;                                 //May have to reverse the input values 
        inputHigh = 64;
        outputLow = 0;
        outputHigh = 255;
        
        theFunction(serialVal, inputLow, inputHigh, outputLow, outputHigh, motorDirectionPins[0], motorPWMPins[0], motorDirectionFB2);
        
        //Right Joystick
      } else if(serialVal <= 28 && serialVal >= 0) {         //Between values 0 and 32
        inputLow = 34;                                 //May have to reverse the input values 
        inputHigh = 94;
        outputLow = 0;
        outputHigh = 255;
    
        theFunction(serialVal, inputLow, inputHigh, outputLow, outputHigh, motorDirectionPins[1], motorPWMPins[1], motorDirectionFB1);

      } else if(serialVal < 99) {

        analogWrite(motorPWMPins[3], 0);
        
      } else if(serialVal <= 129) {
        inputLow = 99;                                 //May have to reverse the input values 
        inputHigh = 129;
        outputLow = 0;
        outputHigh = 255;
    
        theFunction(serialVal, inputLow, inputHigh, outputLow, outputHigh, motorDirectionPins[1], motorPWMPins[1], motorDirectionFB2);

        //Triggers
      } else if(serialVal <= 160) {
        inputLow = 130;                                 //May have to reverse the input values 
        inputHigh = 160;
        outputLow = 0;
        outputHigh = 255;

        theFunction(serialVal, inputLow, inputHigh, outputLow, outputHigh, motorDirectionPins[2], motorPWMPins[2], LOW);

      } else if(serialVal <= 164) {

        analogWrite(motorPWMPins[2], 0);
        
      } else if(serialVal <= 194) {
        inputLow = 164;                                 //May have to reverse the input values 
        inputHigh = 194;
        outputLow = 0;
        outputHigh = 255;

        theFunction(serialVal, inputLow, inputHigh, outputLow, outputHigh, motorDirectionPins[2], motorPWMPins[2], HIGH);

        //Bumpers
      } else if(serialVal == 195) {
        
        digitalWrite(motorDirectionPins[3], motorDirectionLR1);
        analogWrite(motorPWMPins[3], 175);

        digitalWrite(motorDirectionPins[4], motorDirectionLR1);
        analogWrite(motorPWMPins[4], 175);
        
      } else if(serialVal == 196) {
        
        digitalWrite(motorDirectionPins[3], motorDirectionLR2);
        analogWrite(motorPWMPins[3], 175);

        digitalWrite(motorDirectionPins[4], motorDirectionLR2);
        analogWrite(motorPWMPins[4], 175);
      
      } else if(serialVal == 197) {
        
        analogWrite(motorPWMPins[3], 0);
        analogWrite(motorPWMPins[4], 0);
      
        //Rock Drop      
      } else if(serialVal == 198 ) {

        rockDrop.write(0);
        
      } else if(serialVal == 199 ) {

        rockDrop.write(0);

        //Fish Fry
      } else if(serialVal == 200 ) {

        fishFry.write(0);
      
      } else if(serialVal == 201 ) {

        fishFry.write(0);

        //Main Gripper
      } else if(serialVal == 202) {

        mainGripper.write(0);
        
      } else if(serialVal == 203) {

        mainGripper.write(0);

        //Multidirection Control
      } else if(serialVal >= 205 && serialVal <= 208) {     //Value is between 205 and 208

    switch(serialVal) {
      
      //NORTH: Dpad UP
      case 205:
      
        motorDirectionPins[0] = 22;
        motorDirectionPins[1] = 24;
        motorDirectionPins[3] = 28;
        motorDirectionPins[4] = 30;
        
        motorPWMPins[4] = 13;
        motorPWMPins[3] = 12;
        motorPWMPins[1] = 10;
        motorPWMPins[0] = 9;

        motorDirectionFB1 = LOW;
        motorDirectionFB2 = HIGH;
        motorDirectionLR1 = LOW;
        motorDirectionLR2 = HIGH;
        
        break;
        
      //WEST: Dpad Left
      case 208:
      
        motorDirectionPins[0] = 30;
        motorDirectionPins[1] = 28;
        motorDirectionPins[3] = 22;
        motorDirectionPins[4] = 24;
        
        motorPWMPins[4] = 9;
        motorPWMPins[3] = 10;
        motorPWMPins[1] = 13;
        motorPWMPins[0] = 12;

        motorDirectionFB1 = HIGH;
        motorDirectionFB2 = LOW;
        motorDirectionLR1 = LOW;
        motorDirectionLR2 = HIGH;
        
        break;

      //SOUTH: Dpad Down
      case 207:
      
        motorDirectionPins[0] = 24;
        motorDirectionPins[1] = 22;
        motorDirectionPins[3] = 30;
        motorDirectionPins[4] = 28;
        
        motorPWMPins[4] = 12;
        motorPWMPins[3] = 13;
        motorPWMPins[1] = 9;
        motorPWMPins[0] = 10;

        motorDirectionFB1 = HIGH;
        motorDirectionFB2 = LOW;
        motorDirectionLR1 = HIGH;
        motorDirectionLR2 = LOW;
        
        break;

      //EAST: Dpad Right
      case 206:
      
        motorDirectionPins[0] = 28;
        motorDirectionPins[1] = 30;
        motorDirectionPins[3] = 24;
        motorDirectionPins[4] = 22;
        
        motorPWMPins[4] = 10;
        motorPWMPins[3] = 9;
        motorPWMPins[1] = 12;
        motorPWMPins[0] = 13;

        motorDirectionFB1 = LOW;
        motorDirectionFB2 = HIGH;
        motorDirectionLR1 = HIGH;
        motorDirectionLR2 = LOW;
        
        break;

      default:
      
        break;
      
    }
  }
}
     
void theFunction(int serialInput, int inputLow, int inputHigh, int outputLow, int outputHigh, int directionPins, int PWMPins, int motorDirection) {
  int mappedValue;

  digitalWrite(directionPins, motorDirection);
  
  mappedValue = map(serialInput, inputLow, inputHigh, outputLow, outputHigh);

  analogWrite(PWMPins, mappedValue);
}

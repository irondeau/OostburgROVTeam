#include <Servo.h>
int serialVal = 30; // TODO change 0 value in processing and on this line

Servo rockDrop;
Servo fishFry;
Servo mainGripper; 

int depthSensor = A0;
int depthValue = 0;
int depthCount = 0; // TODO Make local timer not have here (make local variable) 

struct motorDirectionPins {
  int motor1DIR = 22;
  int motor2DIR = 24;
  int motor3DIR = 26;
  int motor4DIR = 28;
  int motor5DIR = 30;
  
};

struct motorPWMPins {
  int motor1PWM = 13;
  int motor2PWM = 12;
  int motor3PWM = 11;
  int motor4PWM = 10;
  int motor5PWM = 9;
};

motordirectionPins myDirPins; //TODO Change myDirPins to a better name
motorPWMPins myPWMPins; //TODO Change myPWMPins to a better name

int motorDirectionFB1 = LOW;
int motorDirectionFB2 = HIGH;
int motorDirectionLR1 = LOW;
int motorDirectionLR2 = HIGH;

void setup() {

  pinMode(myDirPins, OUTPUT); //TODO May not work. May have to individually list pins
  pinMode(myPWMPins, OUTPUT); //TODO May not work. May have to individually list pins
  
  pinMode(depthSensor, INPUT);

  rockDrop.attach();
  fishFry.attach();
  mainGripper.attach();
  
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
    inputLow = 0;                                 //May have to reverse the input values 
    inputHigh = 28;
    outputLow = 0;
    outputHigh = 255;
    directionPins = myDirPins.motor1DIR;
    PWMPins = myPWMPins.motor1PWM;
    motorDirection = motorDirectionFB1;
    
    joyStickUpperRange(serialVal, inputLow, inputHigh, outputLow, outputHigh, directionPins, PWMPins, motorDirection); 

      } else if(serialVal < 32) {
        
        analogWrite(myPWMPins.motor1PWM, 0);
      
      } else if(serialVal <= 64) {
        inputLow = 33;                                 //May have to reverse the input values 
        inputHigh = 64;
        outputLow = 0;
        outputHigh = -255;
        directionPins = myDirPins.motor2DIR;
        PWMPins = myPWMPins.motor2PWM;
        motorDirection = motorDirectionFB2;
        
        joyStickLowerRange(serialVal, inputLow, inputHigh, outputLow, outputHigh, directionPins, PWMPins, motorDirection);
        
        //Right Joystick
      } else if(serialVal <= 28 && serialVal >= 0) {         //Between values 0 and 32
        inputLow = 34;                                 //May have to reverse the input values 
        inputHigh = 94;
        outputLow = 0;
        outputHigh = 255;
        directionPins = myDirPins.motor1DIR;
        PWMPins = myPWMPins.motor1PWM;
        motorDirection = motorDirectionFB1;
    
        joyStickUpperRange(serialVal, inputLow, inputHigh, outputLow, outputHigh, directionPins, PWMPins, motorDirection);

      } else if(serialVal < 99) {

        analogWrite(myPWMPins.motor2PWM, 0)
        
      } else if(serialVal <= 129) {
        inputLow = 99;                                 //May have to reverse the input values 
        inputHigh = 129;
        outputLow = 0;
        outputHigh = -255;
        directionPins = myDirPins.motor2DIR;
        PWMPins = myPWMPins.motor2PWM;
        motorDirection = motorDirectionFB2;
    
        joyStickUpperRange(serialVal, inputLow, inputHigh, outputLow, outputHigh, directionPins, PWMPins, motorDirection,);

        //Triggers
      } else if(serialVal <= 160) {
        inputLow = 130;                                 //May have to reverse the input values 
        inputHigh = 160;
        outputLow = 0;
        outputHigh = 255;
        directionPins = myDirPins.motor3DIR;
        PWMPins = myPWMPins.motor3PWM;
        motorDirection = LOW;

        joyStickUpperRange(serialVal, inputLow, inputHigh, outputLow, outputHigh, directionPins, PWMPins, motorDirection,);

      } else if(serialVal <= 164) {

        analogWrite(myPWMPins.motor3PWM, 0)
        
      } else if(serialVal <= 194) {
        inputLow = 164;                                 //May have to reverse the input values 
        inputHigh = 194;
        outputLow = 0;
        outputHigh = -255;
        directionPins = myDirPins.motor3DIR;
        PWMPins = myPWMPins.motor3PWM;
        motorDirection = HIGH;

        joyStickUpperRange(serialVal, inputLow, inputHigh, outputLow, outputHigh, directionPins, PWMPins, motorDirection,);

        //Bumpers
      } else if(serialVal == 195) {
        
        digitalWrite(myDirPins.motor4DIR, motorDirectionLR1);
        analogWrite(myPWMPins.motor4PWM, 175);

        digitalWrite(myDirPins.motor5DIR, motorDirectionLR1);
        analogWrite(myPWMPins.motor5PWM, 175);
        
      } else if(serialVal == 196) {
        
        digitalWrite(myDirPins.motor4DIR, motorDirectionLR2);
        analogWrite(myPWMPins.motor4PWM, 175);

        digitalWrite(myDirPins.motor5DIR, motorDirectionLR2);
        analogWrite(myPWMPins.motor5PWM, 175);
      
      } else if(serialVal == 197) {
        
        analogWrite(myPWMPins.motor4PWM, 0);
        analogWrite(myPWMPins.motor5PWM, 0);
      
        //Rock Drop      
      } else if(servialVal == ) {

        rockDrop.write();
        
      } else if(servialVal == ) {

        rockDrop.write();

        //Fish Fry
      } else if(servialVal == ) {

        fishFry.write()
      
      } else if(servialVal == ) {

        fishFry.write()

        //Main Gripper
      } else if(servialVal == ) {

        mainGripper.write()
        
      } else if(servialVal == ) {

        mainGripper.write()

        //Multidirection Control
      } else if(serialVal >= 205 && serialVal <= 208) {     //Value is between 205 and 208

    switch(serialVal) {
      
      //NORTH: Dpad UP
      case 205:
      
        myDirPinsmotor1DIR = 22;
        myDirPinsmotor2DIR = 24;
        myDirPinsmotor4DIR = 28;
        myDirPinsmotor5DIR = 30;
        
        myPWMPins.motor1PWM = 13;
        myPWMPins.motor2PWM = 12;
        myPWMPins.motor4PWM = 10;
        myPWMPins.motor5PWM = 9;

        motorDirectionFB1 = LOW;
        motorDirectionFB2 = HIGH;
        motorDirectionLR1 = LOW;
        motorDirectionLR2 = HIGH;
        
        break;
        
      //WEST: Dpad Left
      case 208:
      
        myDirPinsmotor1DIR = 30;
        myDirPinsmotor2DIR = 28;
        myDirPinsmotor4DIR = 22;
        myDirPinsmotor5DIR = 24;
        
        myPWMPins.motor1PWM = 9;
        myPWMPins.motor2PWM = 10;
        myPWMPins.motor4PWM = 13;
        myPWMPins.motor5PWM = 12;

        motorDirectionFB1 = HIGH;
        motorDirectionFB2 = LOW;
        motorDirectionLR1 = LOW;
        motorDirectionLR2 = HIGH;
        
        break;

      //SOUTH: Dpad Down
      case 207:
      
        myDirPinsmotor1DIR = 24;
        myDirPinsmotor2DIR = 22;
        myDirPinsmotor4DIR = 30;
        myDirPinsmotor5DIR = 28;
        
        myPWMPins.motor1PWM = 12;
        myPWMPins.motor2PWM = 13;
        myPWMPins.motor4PWM = 9;
        myPWMPins.motor5PWM = 10;

        motorDirectionFB1 = HIGH;
        motorDirectionFB2 = LOW;
        motorDirectionLR1 = HIGH;
        motorDirectionLR2 = LOW;
        
        break;

      //EAST: Dpad Right
      case 206:
      
        myDirPinsmotor1DIR = 28;
        myDirPinsmotor2DIR = 30;
        myDirPinsmotor4DIR = 24;
        myDirPinsmotor5DIR = 22;
        
        myPWMPins.motor1PWM = 10;
        myPWMPins.motor2PWM = 9;
        myPWMPins.motor4PWM = 12;
        myPWMPins.motor5PWM = 13;

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
     
void joyStickUpperRange(serialInput, inputLow, inputHigh, outputLow, outputHigh, directionPins, PWMPins, motorDirection) {
  int mappedValue;

  digitalWrite(directionPins, motorDirection);
  
  mappedValue = map(serialInput, inputLow, inputHigh, outputLow, outputHigh);

  analogWrite(PWMPins, mappedValue);
}

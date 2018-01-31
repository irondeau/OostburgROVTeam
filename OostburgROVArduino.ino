int serialVal = 30;
int motorCtrlSpd;
int directionalControl = 0;

int motor1Direction;
int motor2Direction;
int motor3Direction;
int motor4Direction;
int motor5Direction;
int motor6Direction;

int motor1PWMVal;
int motor2PWMVal;
int motor3PWMVal;
int motor4PWMVal;
int motor5PWMVal;
int motor6PWMVal;

int motor1DIR = 22;
int motor2DIR = 24;
int motor3DIR = 26;
int motor4DIR = 28;
int motor5DIR = 30;
int motor6DIR = 32;

int motor1PWM = 13;
int motor2PWM = 12;
int motor3PWM = 11;
int motor4PWM = 10;
int motor5PWM = 9;
int motor6PWM = 8;

int dirBoolFB1 = LOW;
int dirBoolFB2 = HIGH;
int dirBoolLR1 = LOW;
int dirBoolLR2 = HIGH;

void setup() {

  pinMode(motor1DIR, OUTPUT);
  pinMode(motor1PWM, OUTPUT);
  pinMode(motor2DIR, OUTPUT);
  pinMode(motor2PWM, OUTPUT);
  pinMode(motor3DIR, OUTPUT);
  pinMode(motor3PWM, OUTPUT);
  pinMode(motor4DIR, OUTPUT);
  pinMode(motor4PWM, OUTPUT);
  pinMode(motor5DIR, OUTPUT);
  pinMode(motor5PWM, OUTPUT);
  pinMode(motor6DIR, OUTPUT);
  pinMode(motor6PWM, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    serialVal = Serial.read(); //Read the serial value from processing and set it to variable serialVal
  }

  motorCtrlSpd = 7.96;

  //LEFT JOYSTICK
  if(serialVal <= 28 && serialVal >= 0) {               //Between values 0 and 28
    
    motor1Direction = dirBoolFB1;
    digitalWrite(motor1DIR, motor1Direction);
    motor1PWMVal = abs((serialVal - 32) * motorCtrlSpd);
    analogWrite(motor1PWM, motor1PWMVal);
    
  } else if(serialVal < 32) {                           //Between values 29 and 32
    
    analogWrite(motor1PWM, 0);
    
  } else if(serialVal <= 64) {                          //Between values 33 and 64
    
    motor1Direction = dirBoolFB2;
    digitalWrite(motor1DIR, motor1Direction);
    motor1PWMVal = (serialVal - 32) * motorCtrlSpd;
    analogWrite(motor1PWM, motor1PWMVal);

    //RIGHT JOYSTICK
  } else if(serialVal <= 94) {                          //Between values 34 and 94

    motor2Direction = dirBoolFB1;
    digitalWrite(motor2DIR, motor2Direction);
    motor2PWMVal = abs((serialVal - 97) * motorCtrlSpd);
    analogWrite(motor2PWM, motor2PWMVal);
    
  } else if(serialVal < 99) {                           //Between values 95 and 98

    analogWrite(motor2PWM, 0);
  
  } else if(serialVal <= 129) {                         //Between values 99 and 129

    motor2Direction = dirBoolFB2;
    digitalWrite(motor2DIR, motor2Direction);
    motor2PWMVal = (serialVal - 97) * motorCtrlSpd;
    analogWrite(motor2PWM, motor2PWMVal);

    //TRIGGERS
  } else if(serialVal <= 160) {                          //Between values 130 and 160

    motor3Direction = LOW;
    digitalWrite(motor3DIR, motor3Direction);
    motor3PWMVal = abs((serialVal - 162) * motorCtrlSpd);
    analogWrite(motor3PWM, motor3PWMVal);

  } else if(serialVal <= 164) {                         //Between values 161 and 164

    analogWrite(motor3PWM, 0);
    
  } else if(serialVal <= 194) {                         //Between values 164 and 194

    motor3Direction = HIGH;
    digitalWrite(motor3DIR, motor3Direction);
    motor3PWMVal = (serialVal - 162) * motorCtrlSpd;
    analogWrite(motor3PWM, motor3PWMVal);

    //BUMPERS
  } else if(serialVal == 195) {

    motor4Direction = dirBoolLR1;
    digitalWrite(motor4DIR, motor4Direction);
    motor4PWMVal = 175;
    analogWrite(motor4PWM, motor4PWMVal);

    motor5Direction = dirBoolLR1;
    digitalWrite(motor5DIR, motor5Direction);
    motor5PWMVal = 175;
    analogWrite(motor5PWM, motor5PWMVal);
    
  } else if(serialVal == 196) {

    motor4Direction = dirBoolLR2;
    digitalWrite(motor4DIR, motor4Direction);
    motor4PWMVal = 175;
    analogWrite(motor4PWM, motor4PWMVal);

    motor5Direction = dirBoolLR2;
    digitalWrite(motor5DIR, motor5Direction);
    motor5PWMVal = 175;
    analogWrite(motor5PWM, motor5PWMVal);
    
  } else if(serialVal == 197) {

    analogWrite(motor4PWM, 0);

    //GRIPPER
  } else if(serialVal == 198) {

    motor6Direction = LOW;
    digitalWrite(motor6DIR, motor6Direction);
    motor6PWMVal = 150;
    analogWrite(motor6PWM, motor6PWMVal);
    
  } else if(serialVal == 199) {
    
    motor6Direction = HIGH;
    digitalWrite(motor6DIR, motor6Direction);
    motor6PWMVal = 150;
    analogWrite(motor6PWM, motor6PWMVal);
    
  } else if(serialVal == 200) {

    analogWrite(motor6Direction, 0);

    //Multidirectional Control
  } else if(serialVal >= 204 && serialVal <= 207) {

    switch(serialVal) {
      case 205:
      
        motor1DIR = 22;
        motor2DIR = 24;
        motor4DIR = 28;
        motor5DIR = 30;
        
        motor1PWM = 13;
        motor2PWM = 12;
        motor4PWM = 10;
        motor5PWM = 9;

        dirBoolFB1 = LOW;
        dirBoolFB2 = HIGH;
        dirBoolLR1 = LOW;
        dirBoolLR2 = HIGH;
        
        break;

      case 206:
      
        motor1DIR = 30;
        motor2DIR = 28;
        motor4DIR = 22;
        motor5DIR = 24;
        
        motor1PWM = 9;
        motor2PWM = 10;
        motor4PWM = 13;
        motor5PWM = 12;

        dirBoolFB1 = HIGH;
        dirBoolFB2 = LOW;
        dirBoolLR1 = LOW;
        dirBoolLR2 = HIGH;
        
        break;

      case 207:
      
        motor1DIR = 22;
        motor2DIR = 24;
        motor4DIR = 28;
        motor5DIR = 30;
        
        motor1PWM = 13;
        motor2PWM = 12;
        motor4PWM = 10;
        motor5PWM = 9;

        dirBoolFB1 = LOW;
        dirBoolFB2 = HIGH;
        dirBoolLR1 = LOW;
        dirBoolLR2 = HIGH;
        
        break;

      case 208:
      
        motor1DIR = 22;
        motor2DIR = 24;
        motor4DIR = 28;
        motor5DIR = 30;
        
        motor1PWM = 13;
        motor2PWM = 12;
        motor4PWM = 10;
        motor5PWM = 9;

        dirBoolFB1 = LOW;
        dirBoolFB2 = HIGH;
        dirBoolLR1 = LOW;
        dirBoolLR2 = HIGH;
        
        break;

      default:
      
        break;
      
    }
  }
}

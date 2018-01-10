int serialVal = 30;
int motorCtrlSpd;

int motor1Direction;
int motor2Direction;
int motor3Direction;
int motor4Direction;

int motor1PWMVal;
int motor2PWMVal;
int motor3PWMVal;
int motor4PWMVal;

const int motor1DIR = 22;
const int motor2DIR = 24;
const int motor3DIR = 26;
const int motor4DIR = 28;

const int motor1PWM = 13;
const int motor2PWM = 12;
const int motor3PWM = 11;
const int motor4PWM = 10;

void setup() {

  pinMode(motor1DIR, OUTPUT);
  pinMode(motor1PWM, OUTPUT);
  pinMode(motor2DIR, OUTPUT);
  pinMode(motor2PWM, OUTPUT);
  pinMode(motor3DIR, OUTPUT);
  pinMode(motor3PWM, OUTPUT);
  pinMode(motor4DIR, OUTPUT);
  pinMode(motor4PWM, OUTPUT);

 Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    serialVal = Serial.read(); //Read the serial value from processing and set it to variable serialVal
  }

  motorCtrlSpd = 7.96;

  //LEFT JOYSTICK
  if(serialVal <= 28 && serialVal >= 0) {               //Between values 0 and 28
    
    motor1Direction = LOW;
    digitalWrite(motor1DIR, motor1Direction);
    motor1PWMVal = abs((serialVal - 32) * motorCtrlSpd);
    analogWrite(motor1PWM, motor1PWMVal);
    
  } else if(serialVal < 32) {                           //Between values 29 and 32
    
    analogWrite(motor1PWM, 0);
    
  } else if(serialVal <= 64) {                          //Between values 33 and 64
    
    motor1Direction = HIGH;
    digitalWrite(motor1DIR, motor1Direction);
    motor1PWMVal = (serialVal - 32) * motorCtrlSpd;
    analogWrite(motor1PWM, motor1PWMVal);

    //RIGHT JOYSTICK
  } else if(serialVal <= 94) {                          //Between values 34 and 94

    motor2Direction = LOW;
    digitalWrite(motor2DIR, motor2Direction);
    motor2PWMVal = abs((serialVal - 97) * motorCtrlSpd);
    analogWrite(motor2PWM, motor2PWMVal);
    
  } else if(serialVal < 99) {                           //Between values 95 and 98

    analogWrite(motor2PWM, 0);
  
  } else if(serialVal <= 129) {                         //Between values 99 and 129

    motor2Direction = HIGH;
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

    motor4Direction = LOW;
    digitalWrite(motor4DIR, motor4Direction);
    motor4PWMVal = 150;
    analogWrite(motor4PWM, motor4PWMVal);
    
  } else if(serialVal == 196) {

    motor4Direction = HIGH;
    digitalWrite(motor4DIR, motor4Direction);
    motor4PWMVal = 150;
    analogWrite(motor4PWM, motor4PWMVal);
    
  } else if(serialVal == 197) {

    analogWrite(motor4PWM, 0);
    
  }
}

int serialVal = 32;

int motorCtrlSpd = 7.97;

int motor1PWMVal = 0;
int motor2PWMVal = 0;
int motor3PWMVal = 0;
int motor4PWMVal = 0;
int motor5PWMVal = 0;
int motor6PWMVal = 0;
int lightVal = 0;

const int motor1PWM = 9; //Left joystick forwards/reverse
const int motor1DIR = 22; //Left joystick direction

const int motor2PWM = 6; //Right joystick forwards/reverse
const int motor2DIR = 24; //Right joystick direction

const int motor3PWM = 5; //Triggers up/down
const int motor3DIR = 26; //Triggers direction

const int motor4PWM = 3; //Gripper Value
const int motor4DIR = 28; //Gripper Direction

const int motor5PWM = 10; //Left Bumper for Strafing
const int motor5DIR = 30; //Strafe Direction

const int motor6PWM = 11; //Right Bumper for Strafing
const int motor6DIR = 32; //Strafe Direction

const int light = 34; // Light Pin

int motor1Direction;
int motor2Direction;
int motor3Direction;
int motor4Direction;
int motor5Direction;
int motor6Direction;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1PWM, OUTPUT); // PWM to control motor speed; use analogWrite to write a value to the motor
  pinMode(motor1DIR, OUTPUT); // Directional Control: HIGH to reverse directon

  pinMode(motor2PWM, OUTPUT); // PWM to control motor speed; use analogWrite to write a value to the motor
  pinMode(motor2DIR, OUTPUT); // Directional Control: HIGH to reverse directon

  pinMode(motor3PWM, OUTPUT); // PWM to control motor speed; use analogWrite to write a value to the motor
  pinMode(motor3DIR, OUTPUT); // Directional Control: HIGH to reverse directon

  pinMode(motor4PWM, OUTPUT); // PWM to control motor speed; use analogWrite to write a value to the motor
  pinMode(motor4DIR, OUTPUT); // Directional Control: HIGH to reverse directon

  pinMode(motor5PWM, OUTPUT); // PWM to control motor speed; use analogWrite to write a value to the motor
  pinMode(motor5DIR, OUTPUT); // Directional Control: HIGH to reverse directon

  pinMode(motor6PWM, OUTPUT); // PWM to control motor speed; use analogWrite to write a value to the motor
  pinMode(motor6DIR, OUTPUT); // Directional Control: HIGH to reverse directon  

  pinMode(light, OUTPUT); // Light ON/OFF
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    serialVal = Serial.read(); //Read the serial value from processing and set it to variable serialVal
  }

  //Speed Adjustment
  if (serialVal == 201) {
    motorCtrlSpd = 7.97 / 2.75;
  } else if (serialVal == 202) {
    motorCtrlSpd = 7.97;
  }

  //Left Motor
  if (serialVal <= 29 && serialVal >= 0) {
    motor1Direction = HIGH;
    digitalWrite(motor1DIR, motor1Direction);
    motor1PWMVal = abs((serialVal - 29) * motorCtrlSpd * 1.0979);
  } else if (serialVal > 32 && serialVal <= 64) {
    motor1Direction = LOW;
    digitalWrite(motor1DIR, motor1Direction);
    motor1PWMVal = (serialVal - 32) * motorCtrlSpd;
  }
  //Right Motor
  else if (serialVal <= 97 && serialVal >= 65) {     //if serialVal is less than 129 and greater than 65 then
    motor2Direction = LOW;                            //change the direction to forwards
    digitalWrite(motor2DIR, motor2Direction);          //write to the direction pin
    motor2PWMVal = abs((serialVal - 97) * motorCtrlSpd);       //and calculate for the value between -255 and 255
  } else if (serialVal > 97 && serialVal <= 129) {  //else if serialVal is greater than 192 and less than 255 then
    motor2Direction = HIGH;                             //change the direction to backwards
    digitalWrite(motor2DIR, motor2Direction);          //write to the direction pin
    motor2PWMVal = (serialVal - 97) * motorCtrlSpd;            //and calculater fo the value between -255 and 255
  } 
  //Vertical Motors
  else if (serialVal <= 162 && serialVal >= 130) {
    motor3Direction = LOW;                            //change the direction to forwards
    digitalWrite(motor3DIR, motor3Direction);          //write to the direction pin
    motor3PWMVal = abs((serialVal - 162) * motorCtrlSpd);   
  } else if (serialVal > 162 && serialVal <= 194) {
    motor3Direction = HIGH;                             //change the direction to forwards
    digitalWrite(motor3DIR, motor3Direction);          //write to the direction pin
    motor3PWMVal = (serialVal - 162) * motorCtrlSpd;
  } else if (serialVal == 207) {
    motor3Direction = LOW;
    digitalWrite(motor3DIR, motor3Direction);
    motor3PWMVal = 70;
  }
  //Strafing Motors
  else if (serialVal == 195) {
    motor5Direction = LOW;
    digitalWrite(motor5DIR, motor5Direction);
    motor5PWMVal = 200;
    motor6Direction = LOW;
    digitalWrite(motor6DIR, motor6Direction);
    motor6PWMVal = 200;
  } else if (serialVal == 196) {
    motor5Direction = HIGH;
    digitalWrite(motor5DIR, motor5Direction);
    motor5PWMVal = 200;
    motor6Direction = HIGH;
    digitalWrite(motor6DIR, motor6Direction);
    motor6PWMVal = 200;
  }
  //Gripper
  else if (serialVal == 198) {
    motor4Direction = LOW;
    digitalWrite(motor4DIR, motor4Direction);
    motor4PWMVal = 30;
  } else if (serialVal == 199) {
    motor4Direction = HIGH;
    digitalWrite(motor4DIR, motor4Direction);
    motor4PWMVal = 30;
  }
  //Light
  else if (serialVal == 203) {
    lightVal = HIGH;
    digitalWrite(light, lightVal);
  } else if (serialVal == 204) {
    lightVal = LOW;
    digitalWrite(light, lightVal);
  }
  
  //Dead Zones
  else if (serialVal <= 32 && serialVal >= 30) {  //else if serialVal <= 32 and >= 30
    motor1PWMVal = 0;                               //set pwm of motor 1 to 0
  } else if (serialVal == 97) {                    //else if serialVal is 97
    motor2PWMVal = 0;                               //set pwm of motor 2 to 0
  } else if (serialVal == 162) {                   //else if serialVal is 162
    motor3PWMVal = 0;                               //set pwm of motor 3 to 0
  } else if (serialVal == 200) {
    motor4PWMVal = 0;
  } else if (serialVal == 197) {
    motor5PWMVal = 0;
    motor6PWMVal = 0;
  }
  
    analogWrite(motor1PWM, motor1PWMVal); //
    analogWrite(motor2PWM, motor2PWMVal); //  
    analogWrite(motor3PWM, motor3PWMVal); //  Push the PWM values
    analogWrite(motor4PWM, motor4PWMVal); //
    analogWrite(motor5PWM, motor5PWMVal); //
    analogWrite(motor6PWM, motor6PWMVal); //
}

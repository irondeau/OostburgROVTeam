int soundsensor = A0;
#include <Servo.h>
Servo myservo;

void setup() {
  
  pinMode (soundsensor, INPUT);

  myservo.attach(9);

  Serial.begin(9600);

}

void loop() {
  int statusSensor = analogRead(soundsensor);
  
  Serial.println(statusSensor);

  delay(1000);

  if(statusSensor > 190) {
    
    myservo.write(30);
    delay(3000);
  }
  else{
    myservo.write(90);
  }
}


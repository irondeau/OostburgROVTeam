import net.java.games.input.*;
import org.gamecontrolplus.*;
import org.gamecontrolplus.gui.*;

import processing.serial.*;

ControlIO control;
Configuration config;
ControlDevice gpad;

Serial myPort;
String portName;
int portNumber = 0;
int limit = 4;

int gameInputPlaceholder = 0;

void setup() {
  size(1000, 800);
  
  //Initialize controlIO
  control = ControlIO.getInstance(this);
  
  //Find a device that matches the configuration file
  gpad = control.getMatchedDevice("xboxconfig");
  if(gpad == null) {
    println("No suitable decive configured"); 
    System.exit(-1); // End the program
  }
  
  while(portNumber < limit) {
    try {
      portName = Serial.list()[portNumber];
    } catch(Exception e) {
      System.err.println("Retrying...");
      portNumber++;
      continue;
    }
    break;
  }
  myPort = new Serial(this, portName, 9600);
  delay(1000); 
}

void sendAxisInput(String input, int offset) {
  
  gameInputPlaceholder = (int)(gpad.getSlider(input).getValue() * 32 + offset);
  myPort.write(gameInputPlaceholder);
  println(gameInputPlaceholder);
  
}

void draw() {
  
  if (gpad.getSlider("YLeftAxis").getValue() != 0) {
    sendAxisInput("YLeftAxis", 32);
  }
  if (gpad.getSlider("YRightAxis").getValue() != 0) {
    sendAxisInput("YRightAxis", 97);
  }
  if (gpad.getSlider("Triggers").getValue() != 0) {
    sendAxisInput("Triggers", 162);
  }
  if (gpad.getButton("LeftBumper").pressed()) {
    myPort.write(195);
    println("195");
  } else if (gpad.getButton("RightBumper").pressed()) {
    myPort.write(196);
    println("196");
  } else {
    myPort.write(197);
  }
  if (gpad.getButton("A").pressed()) {
    myPort.write(198);
    println("198");
  } else if (gpad.getButton("B").pressed()) {
    myPort.write(199);
    println("199");
  } else {
    myPort.write(200);
  }
  if (gpad.getButton("Y").pressed()) {
    myPort.write(201);
    println("201");
  } else {
    myPort.write(202);
  }
  if (gpad.getButton("X").pressed()) {
    myPort.write(203);
    println("203");
  } else {
    myPort.write(204);
  }
  
  float hat = gpad.getHat("DPad").getValue();
  if (hat == 2.0) {
    myPort.write(205);
    println("205");
  } else if (hat == 4.0) {
    myPort.write(206);
    println("206");
  } else if (hat == 6.0) {
    myPort.write(207);
    println("207");
  } else if (hat == 8.0) {
    myPort.write(208);
    println("208");
  }
  println(hat);
  
  keyPressed();
}

void keyPressed() {
  if (key == ENTER) {
    myPort.write(209);
    println("ENTER");
  }
  key = '.';
}
import net.java.games.input.*;
import org.gamecontrolplus.*;
import org.gamecontrolplus.gui.*;

import processing.serial.*;

ControlIO control;
Configuration config;
ControlDevice gpad;

Serial myPort;

int gameInputPlaceholder = 0;

void setup() {
  size(500, 400);
  
  //Initialize controlIO
  control = ControlIO.getInstance(this);
  
  //Find a device that matches the configuration file
  gpad = control.getMatchedDevice("xboxconfig");
  if(gpad == null) {
    println("No suitable decive configured");
    System.exit(-1); // End the program
  }
  
  String portName = Serial.list()[0];
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
  if (gpad.getSlider("Triggers").getValue() > .1 || gpad.getSlider("Triggers").getValue() < -.1) {
    sendAxisInput("Triggers", 162);
  }
  if (gpad.getButton("LeftBumper").pressed()) {
    myPort.write(195);
    println("195");
  }
  if (gpad.getButton("RightBumper").pressed()) {
    myPort.write(196);
    println("196");
  }
  if (gpad.getButton("A").pressed()) {
    myPort.write(197);
    println("197");
  }
  if (gpad.getButton("B").pressed()) {
    myPort.write(198);
    println("198");
  }
  if (gpad.getButton("Y").pressed()) {
    myPort.write(199);
    println("199");
  }
  if (gpad.getButton("X").pressed()) {
    myPort.write(200);
    println("200");
  }
  
  keyPressed();
}

void keyPressed() {
  if (key == ENTER) {
    myPort.write(207);
    println("ENTER");
  }
  key = '.';
}
import net.java.games.input.*;
import org.gamecontrolplus.*;
import org.gamecontrolplus.gui.*;

import processing.serial.*;

ControlIO control;
Configuration config;
ControlDevice gpad;

Serial myPort;

int yLeftAxisPlcHldr;
int yRightAxisPlcHldr;
int zAxisPlcHldr;

void setup() {
  size(200,200);
  //Initialize the ControlIO
  control = ControlIO.getInstance(this);
  //Find a device that matches the coniguration file
  gpad = control.getMatchedDevice("xboxconfig");
  if (gpad == null) {
    println("No suitable device configured");
    System.exit(-1); //End the Program NOW!
  }
  //Set up the serial communication
  String portName = Serial.list()[0]; // Define the port being used
  myPort = new Serial(this, portName, 9600);
  delay(1000);
}

void draw() {
  if (gpad.getSlider("YLeftAxis").getValue() != 0) {
    yLeftAxisPlcHldr = (int)(gpad.getSlider("YLeftAxis").getValue()*32 + 32); //Value between 0 and 64
    myPort.write(yLeftAxisPlcHldr);
    println(yLeftAxisPlcHldr);
  }
  if (gpad.getSlider("YRightAxis").getValue() != 0){
    yRightAxisPlcHldr = (int)(gpad.getSlider("YRightAxis").getValue()*32 + 97); //Value between 65 and 129
    myPort.write(yRightAxisPlcHldr);
    println(yRightAxisPlcHldr);
  }
  if (gpad.getSlider("Triggers").getValue() > .1 || gpad.getSlider("Triggers").getValue() < -.1){
    zAxisPlcHldr = (int)(gpad.getSlider("Triggers").getValue()*32 + 162); //Value between 130 and 194
    myPort.write(zAxisPlcHldr);
    println(zAxisPlcHldr);
  } else if (gpad.getSlider("Triggers").getValue() < .1 && gpad.getSlider("Triggers").getValue() > -.1) {
    keyPressed();
  }
  
  if (gpad.getButton("LeftBumper").pressed()) {
    myPort.write(195);                                                    //Value of 195
    println("195"); 
  } else if (gpad.getButton("RightBumper").pressed()) {
    myPort.write(196);                                                    //Value of 197
    println("196"); 
  } else {
    myPort.write(197);                                                    //Else Write Value 198
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
  
  if (gpad.getButton("Start").pressed()) {
    myPort.write(201);
    println("201");
  } else if (gpad.getButton("Back").pressed()) {
    myPort.write(202);
    println("202");
  }
  
  if (gpad.getButton("Y").pressed()) {
    myPort.write(203);
    println("203");
  } else if (gpad.getButton("X").pressed()) {
    myPort.write(204);
    println("204");
  }
}

void keyPressed() {
  if (key == ENTER) {
    myPort.write(207);
    println("Enter");
  } else {
    myPort.write(162);
  }
}
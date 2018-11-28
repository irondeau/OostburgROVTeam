import net.java.games.input.*;
import org.gamecontrolplus.*;
import org.gamecontrolplus.gui.*;

import processing.serial.*;

ControlIO control;
Configuration config;
ControlDevice gpad;

Serial myPort;
String portName;
String serialVal = "0";
int portNumber = 0;
int limit = 4;

int gameInputPlaceholder = 0;

PFont font60;
PFont font40;
PFont font30;
PFont font20;

int timeMillis = 0;
int timeMillisInt = 0;
int timeSec = 0;
int timeMin = 14;
int startingTime = 0;

String currentDepth = "0";
String depth1 = "0", depth2 = "0";
int depth1X = 1075, depth1Y = 150, depth1Height = 50, depth1Width = 150, depth2X = 1275, depth2Y = 150, depth2Height = 50, depth2Width = 150;
boolean mouse;

int rovHeight = 150;

void setup() {
  size(1500, 800);
  font20 = createFont("Arial", 20);
  font30 = createFont("Arial", 30);
  font40 = createFont("Arial", 40);
  font60 = createFont("Arial", 60);
  frameRate(8);
  
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
  if(portName != null) {
    myPort = new Serial(this, portName, 9600);
  } else {
    System.exit(-1);
  }
  delay(1000); 
}

void sendAxisInput(String input, int offset) {
  
  gameInputPlaceholder = (int)(gpad.getSlider(input).getValue() * 32 + offset);
  myPort.write(gameInputPlaceholder);
  println(gameInputPlaceholder);
  
}

void draw() {
  if(myPort.available() > 0) {
    serialVal = myPort.readStringUntil('\n');
  }
  
  if(myPort.available() > 0) {
    
    serialVal = myPort.readStringUntil('\n');
    
    if(serialVal != "0" && serialVal != null) {
      
      //currentDepth = str(float(serialVal) * 1.79);
    
      currentDepth = str(map(float(serialVal), 0, 255, 0, 457.2));
      
    }
    
  }
  
  background(125);
  drawCube(0, 0, 0, 0, 0, 0);
  drawBox1();
  drawBox2(0, 0, 0, 0, 90);
  displayTime();
  
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
  myPort.clear();
}

void drawCube(int north, int east, int south, int west, int up, int down) {
  
  strokeWeight(1);
  
  //Draw ROV cube
  stroke(0);
  fill(255);
  quad(300, 300, 500, 200, 700, 300, 500, 400);
  quad(300, 300, 500, 400, 500, 400 + rovHeight, 300, 300 + rovHeight);
  quad(700, 300, 500, 400, 500, 400 + rovHeight, 700, 300 + rovHeight);
  
  strokeWeight(2);
  
  stroke(north * 255, 0, 0);
  line(675, 287, 800, 225);
  
  stroke(east * 255, 0, 0);
  line(600, 425, 800, 525);
  
  stroke(south * 255, 0, 0);
  line(400, 425, 200, 525);
  
  stroke(west * 255, 0, 0);
  line(325, 287, 200, 225);
  
  stroke(up * 255, 0, 0);
  line(500, 300, 500, 100);
  
  stroke(down * 255, 0, 0);
  line(500, 550, 500, 600);
  
}

void drawBox1() {
  
  strokeWeight(1);
  rect(1025, 25, 450, 300);
  
  fill(0);
  textAlign(CENTER);
  textFont(font30);
  text(currentDepth + " cm", 1250, 100);
  text(str(abs(float(depth1) - float(depth2))), 1250, 285);
  textFont(font20);
  text("Current Depth", 1250, 65);
  text("Depth 1", 1150, 140);
  text("Depth 2", 1350, 140);
  text("Distance", 1250, 250);
  
  fill(200);
  if(overDepth(depth1X, depth1Y, depth1Width, depth1Height) && mouse) {
   
    depth1 = currentDepth;
    fill(150);
    
  }
  
  stroke(0);
  rect(depth1X, depth1Y, depth1Width, depth1Height);
  fill(0);
  textFont(font30);
  text(depth1, 1150, 185);
  
  fill(200);
  if(overDepth(depth2X, depth2Y, depth2Width, depth2Height) && mouse) {
    
    depth2 = currentDepth;
    fill(150);
    
  }
  
  stroke(0);
  rect(depth2X, depth2Y, depth2Width, depth2Height);
  fill(0);
  textFont(font30);
  text(depth2, 1350, 185);
  
}

void drawBox2(int north, int east, int south, int west, int gripper) {
  
  strokeWeight(1);
  fill(255);
  rect(1025, 350, 450, 425);
  
  fill(0);
  textFont(font40);
  textAlign(LEFT);
  text("N", 1125, 400);
  text("E", 1196, 465);
  text("S", 1125, 530);
  text("W", 1045, 465);
  
  textFont(font30);
  if(gripper == 90) {
    text("Gripper Status: STOPPED", 1060, 600);
  } else if(gripper < 90) {
    text("Gripper Status: CLOSING", 1060, 600);
  } else if(gripper > 90) {
    text("Gripper Status: OPENING", 1060, 600);
  }
  
  strokeWeight(2);
  
  stroke(north * 255, 0, 0);
  line(1138, 410, 1138, 450); //North
  line(1138, 410, 1133, 415);
  line(1138, 410, 1143, 415);
  
  stroke(east * 255, 0, 0);
  line(1138, 450, 1186, 450); //East
  
  stroke(south * 255, 0, 0);
  line(1138, 450, 1138, 490); //South
  
  stroke(west * 255, 0, 0);
  line(1090, 450, 1138, 450); //West
  
}

void displayTime() {
  
  timeMillis = millis();
  timeMillisInt = int(str(timeMillis).substring(int(str(timeMillis).length() - 3), int(str(timeMillis).length() - 1)));
  timeMillisInt = 99 - timeMillisInt;
  
  timeSec = (millis() - startingTime) / 1000;
  timeSec = 59 - timeSec;
  if(timeSec == -1) {
    startingTime += 60000;
    timeMin--;
  }
  
  fill(255, 255, 255);
  textFont(font60);
  text(nf(timeMin, 2) + ":" + nf(timeSec, 2) +":" + nf(timeMillisInt, 2), 10, 55);
  
  
}

boolean overDepth(int x, int y, int w, int h) {

  if(mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h) {
    
    return true;
    
  } else {
    
    return false;
    
  }
  
}

void mousePressed() {
  
  mouse = true;
  
}

void mouseReleased() {
  
  mouse = false;
  
}

void keyPressed() {
  if (key == ENTER) {
    myPort.write(209);
    println("ENTER");
  }
  key = '.';
}

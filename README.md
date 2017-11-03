# Oostburg ROV Team Summary
This project was created for the purpose of building and organizing the software that runs the Oostburg Remotely Operated Vehicle (ROV), a High School Club focused on teaching students about robotics and company management. The robot runs using an Arduino Mega and the Processing computer language. Follow the steps below to understand how the robot is set up.

### Arduino Setup
The Arduino is connected to a laptop via USB connection quite simply. To allow the cable to travel under the water, a USB-ethernet adapter is used on both ends of an ethernet cable where one is plugged into the computer and the other is connected to the Arduino inside of the dry housing of the robot. When the Arduino is successfully connected, an orange and a green light should light up on the Arduino to indicate power and signal.

Parts required for this connection:
```
  1 x Laptop Computer with Arduino Software
  1 x Arduino (any model)
  2 x USB-ethernet adapter
  1 x Ethernet cable
  1 x USB cable
```
  
Laptop -> USB-ethernet adapter -> ethernet cable -> USB-ethernet calbe -> USB cable -> Arduino

It is possible to connect separate power to the Arduino through the power jack. The arduino takes 9-12V DC @ 2A which can be harnessed from the power connected to the ROV.

### Motor Driver Setup
The motor drivers that were used on our ROV were bought from Pololu and can be found at https://www.pololu.com/product/2992. The drivers take in a PWM (pulse width modulation) signal from the Arduino and use it to determine the speed of the motor. This is an example of the Pololu G2 High-Power Motor Driver:
```
GND DIR PWM SLP FLT CS  3V3 VM 
_|___|___|___|___|___|___|___|_
|o   o   o   o   o   o   o   o|
|                             |
|                             |
|                             |
|                             |
|                             |
|         HIGH-POWER          |
|        MOTOR DRIVER         |
|                             |
|                             |
|                             |
|                             |
|                             |
|___o______o______o______o____|
    |      |      |      |
   GND    OUTA   OUTB   VIN 
```
In order to connect the motor and power source, the four large connections must be used. GND(-) and VIN(+) connections are used for power while the OUTA and OUTB are connections to the motor. THe OUTA and OUTB connections are interchangeable, but doing so will result in an opposite rotation of the motor.

The only necessary signal pins to use are the GND, DIR, PWM, and SLP pins. The GND pin on the motor driver connects to the Arduino's GND pin. The DIR pin connects to any output pin on the Arduino, and is used to change the direction of the motor between `HIGH` and `LOW`. The PWM pin on the motor driver must be connected to an Arduino pin with the symbol "~" next to the number or on the Arduino Mega with the pins that have a "PWM" label. The final pin that must be used, the SLP pin, must always have a `HIGH` state for the motor to run.

### Processing Setup
The first step of connecting the Arduino to an XBox controller is to download the Processing software. You can find the download at https://processing.org/download/. Processing works on the three most common opperating systems: Windows, Linux, and Mac OS.

### Connecting an XBox Controller

/*
This example shows how to read a joystick value on PS2 Controller.

Function:
  readButton(button); // Read button status, it will return corresponding data
                      // Digital button: 0 = pressed, 1 = released
                      // Analog button: return a value

  Digital button:
    PS2_SELECT
    PS2_JOYSTICK_LEFT
    PS2_JOYSTICK_RIGHT
    PS2_START
    PS2_UP
    PS2_RIGHT
    PS2_DOWN
    PS2_LEFT
    PS2_LEFT_2
    PS2_RIGHT_2
    PS2_LEFT_1
    PS2_RIGHT_1
    PS2_TRIANGLE
    PS2_CIRCLE
    PS2_CROSS
    PS2_SQUARE

  Analog button:
    PS2_JOYSTICK_LEFT_X_AXIS
    PS2_JOYSTICK_LEFT_Y_AXIS
    PS2_JOYSTICK_RIGHT_X_AXIS
    PS2_JOYSTICK_RIGHT_Y_AXIS
    PS2_JOYSTICK_LEFT_UP
    PS2_JOYSTICK_LEFT_DOWN
    PS2_JOYSTICK_LEFT_LEFT
    PS2_JOYSTICK_LEFT_RIGHT
    PS2_JOYSTICK_RIGHT_UP
    PS2_JOYSTICK_RIGHT_DOWN
    PS2_JOYSTICK_RIGHT_LEFT
    PS2_JOYSTICK_RIGHT_RIGHT

Product page:
  Cytron PS2 Shield: http://www.cytron.com.my/p-shield-ps2
  PS2 Controller: http://www.cytron.com.my/p-ps-gp-1
  CT-UNO: http://www.cytron.com.my/p-ct-uno

Original written by:
            Cytron Technologies

Modified:
  29/06/15  Idris, Cytron Technologies
*/

#include <SoftwareSerial.h>
#include "Cytron_PS2Shield.h"
#include "SabertoothSimplified.h"
#include <Wire.h>
#include "grove_alphanumeric_display.h"

Seeed_Digital_Tube tube;

//Cytron_PS2Shield ps2(2,3); // SoftwareSerial: Rx and Tx pin
Cytron_PS2Shield ps2; // HardwareSerial, note: 

SoftwareSerial SWSerial(NOT_A_PIN, A4); // RX on no pin (unused), TX on pin 11 (to S1).
SabertoothSimplified ST(SWSerial); // Use SWSerial as the serial port.

bool pota;
bool potat;
bool pat;
bool potal;
int pts;
int score=64;
int var;

//************************************************************************************************

void setup()
{
  ps2.begin(9600);      // liaison série PS2 shield
  //Serial.begin(9600); // Set monitor baudrate to 9600
  SWSerial.begin(9600); // liaison série carte Sabertooth
  Wire.begin();

  tube.setTubeType(TYPE_4, TYPE_4_DEFAULT_I2C_ADDR);
  tube.setBrightness(15);
  tube.setBlinkRate(BLINK_OFF);
  tube.displayNum(score);

  attachInterrupt(digitalPinToInterrupt(19), poshaut, FALLING);
  attachInterrupt(digitalPinToInterrupt(18), posbas, FALLING);

  pinMode(19,INPUT);
  pinMode(18,INPUT);

}

//*****************************************************************************************************************************************************

void loop(){
  
// gestion des roues
  
  if(ps2.readButton(PS2_JOYSTICK_LEFT_DOWN)==0 and ps2.readButton(PS2_JOYSTICK_LEFT_UP)==0 and ps2.readButton(PS2_JOYSTICK_LEFT_LEFT)==0 and ps2.readButton(PS2_JOYSTICK_LEFT_RIGHT)==0){
      ST.motor(1, 0);
      ST.motor(2, 0);
  }
  else if(ps2.readButton(PS2_JOYSTICK_LEFT_UP)>0 and ps2.readButton(PS2_JOYSTICK_LEFT_LEFT)==0 and ps2.readButton(PS2_JOYSTICK_LEFT_RIGHT)==0){
      ST.motor(1, 0.8*ps2.readButton(PS2_JOYSTICK_LEFT_UP)/(1.8*ps2.readButton(PS2_RIGHT_1)+1.2));
      ST.motor(2, 0.8*ps2.readButton(PS2_JOYSTICK_LEFT_UP)/(1.8*ps2.readButton(PS2_RIGHT_1)+1.2));
  }
  else if(ps2.readButton(PS2_JOYSTICK_LEFT_DOWN)>0 and ps2.readButton(PS2_JOYSTICK_LEFT_LEFT)==0 and ps2.readButton(PS2_JOYSTICK_LEFT_RIGHT)==0){
      ST.motor(1, -0.8*ps2.readButton(PS2_JOYSTICK_LEFT_DOWN)/(1.8*ps2.readButton(PS2_RIGHT_1)+1.2));
      ST.motor(2, -0.8*ps2.readButton(PS2_JOYSTICK_LEFT_DOWN)/(1.8*ps2.readButton(PS2_RIGHT_1)+1));
  }
  else if(ps2.readButton(PS2_JOYSTICK_LEFT_LEFT)>25){
    ST.motor(1, ps2.readButton(PS2_JOYSTICK_LEFT_LEFT)/(1.8*ps2.readButton(PS2_RIGHT_1)+1.2));
    ST.motor(2, -ps2.readButton(PS2_JOYSTICK_LEFT_LEFT)/(1.8*ps2.readButton(PS2_RIGHT_1)+1.2));
  }
  else if (ps2.readButton(PS2_JOYSTICK_LEFT_RIGHT)>25){
    ST.motor(1, -ps2.readButton(PS2_JOYSTICK_LEFT_RIGHT)/(1.8*ps2.readButton(PS2_RIGHT_1)+1.2));
    ST.motor(2, ps2.readButton(PS2_JOYSTICK_LEFT_RIGHT)/(1.8*ps2.readButton(PS2_RIGHT_1)+1.2));
  }

// gestion ouverture des pinces

  if(ps2.readButton(PS2_LEFT_2)==1 and ps2.readButton(PS2_RIGHT_2)==0){
    digitalWrite(4,0);
    analogWrite(5,255);
    digitalWrite(13,0);
    analogWrite(11,255);
  }
  else if(ps2.readButton(PS2_LEFT_2)==0 and ps2.readButton(PS2_RIGHT_2)==1){
    digitalWrite(4,1);
    analogWrite(5,255);
    digitalWrite(13,1);
    analogWrite(11,255);
  }
  else{
    analogWrite(5,0);
    analogWrite(11,0);
  }

// gestion montée et descente des pinces

  if(ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS)>150 and digitalRead(18)==1){
    digitalWrite(12,0);
    analogWrite(10,70);
    
  }
  else if(ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS)<100 and digitalRead(19)==1){
    digitalWrite(12,1);
    analogWrite(10,200);
    
  }
  else{
    analogWrite(10,0);
  }
  

// gestion maintien des plaques

  if(ps2.readButton(PS2_RIGHT_2)==1 and ps2.readButton(PS2_LEFT_2)==0 ){
    digitalWrite(8,0);
    analogWrite(9,100);
    var=0;
    }
  else if  (ps2.readButton(PS2_RIGHT_2)==0 and ps2.readButton(PS2_LEFT_2)==1 ){
    digitalWrite(8,1);
    analogWrite(9,100);
    var=1;
  }
  else if (var==1) {
    digitalWrite(8,1);
    analogWrite(9,40); 
  }
  else{
     analogWrite(9,0);
  }
  

// gestion de l'afficheur du score
  
    
    
    
  potat=ps2.readButton(PS2_TRIANGLE);
   potal=ps2.readButton(PS2_CIRCLE);
   pat=ps2.readButton(PS2_CROSS);
   pota=ps2.readButton(PS2_SQUARE);

if (potat==0){
   pts=pts+10;
    tube.displayNum(pts);
    delay(100);
  }
 else if (pat==0){
    pts=pts-10;
    tube.displayNum(pts);
    delay(100);
 }
 else if (potal==0){
    pts=pts+1;
    tube.displayNum(pts);
    delay(100);
 }
    else if (pota==0){
    pts=pts-1;
    tube.displayNum(pts);
      delay(100);
   } 
   else{
 tube.displayNum(pts);
   }
 if (pts<0){
    pts=0;
    tube.displayNum(pts);
    delay(100);
   } 

}

//*********************************************************************************************

void poshaut(){
  analogWrite(10,0);
}

//*********************************************************************************************

void posbas(){
  analogWrite(10,0);
}

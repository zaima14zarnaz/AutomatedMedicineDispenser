#include <Wire.h>
#include <LiquidCrystal.h>
#include "RTClib.h"

#include <Keypad.h>
#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
Servo myservo2;                // twelve servo objects can be created on most boards
 
int pos = 0,pos2 = 0;

int med1 = -1;

int rowCounter =0; // row counter
int columnCounter =0; // column counter
int foundColumn = 0;
boolean foundCol = false;
int keyValue = 0;
int noKey = 0;
boolean readKey = false;
int debounce = 300; // set this to the lowest value that gives the best result
const int row1 = 2;
const int row2 = 3;
const int row3 = 4;
const int row4 = 5;
const int colA = 8;
const int colB = 9;
const int colC = 10;
const int colD = 11;
int counter = 0;

int one1h;
int one2h;
int one3h;
int one1m;
int one2m;
int one3m;

int h = 0;
int m = 0;

DateTime now;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};


RTC_DS3231 rtc;

void showDate(void);
void showTime(void);
void showDay(void); 


void setup ()
{
  Serial.begin(9600);
  pinMode(row1, OUTPUT);
pinMode(row2, OUTPUT);
pinMode(row3, OUTPUT);
pinMode(row4, OUTPUT);
pinMode(colA, INPUT_PULLUP);
pinMode(colB, INPUT_PULLUP);
pinMode(colC, INPUT_PULLUP);
pinMode(colD, INPUT_PULLUP);
myservo.attach(12);
myservo2.attach(13);
//

  //delay(2000);
}


void loop () 
{
  checktime();

  if(noKey == 16){ // no keys were pressed
readKey = true; // keyboard is ready to accept a new keypress
}
noKey = 0;
for(rowCounter=row1; rowCounter<(row4 +1); rowCounter++){
scanRow(); // switch on one row at a time
for(columnCounter = colA; columnCounter <colD +1; columnCounter++){
readColumn(); // read the switch pressed
if (foundCol== true){
keyValue =(rowCounter-row1) +4*(columnCounter - colA);
}
}
}
if(readKey==true && noKey == 15)
{ // a key has been pressed
 // used for debug
 if(counter == 0 || counter == 1)
 {
   h = h*10 + keyValue;
   counter++;
 }
 else if(counter == 2 || counter == 3)
 {
   m = m * 10 + keyValue;
   counter++;
   if(counter == 4) 
   {
     Serial.print(h);
     Serial.print(":");
     Serial.println(m);
     counter = 0;
     delay(1000);
     if(h > 19 && h <= 23){ one3h = h ; one3m = m; Serial.println("night");}
     h = 0;
     m = 0;
     
     
     
   } 
 }

 
if (keyValue == 13){
}
else{

}
/********************************************************
// call to part of the sketch that will use the key number
*/

//*******************************************************
readKey = false; // rest the flag
delay(debounce); // debounce
}
 
}
   


void scanRow(){
for(int j =row1; j < (row4 +1); j++){
digitalWrite(j, HIGH);
}
digitalWrite(rowCounter , LOW); // switch on one row
}
void readColumn(){
foundColumn = digitalRead(columnCounter);
if(foundColumn == 0){
foundCol = true;
}
else{
foundCol=false;
noKey=noKey +1; // counter for number of empty columns
}
}

void checktime()
{
  
 
  Serial.print(one3h);
  Serial.print(":");
  Serial.println(one3m);
 
 
    if(one3h == 21 && one3m == 2 && med1 == -1)
    {
      med1 =0;
      Serial.println("Night time");
       for(pos = 0,pos2 = 180; pos <= 180; pos += 1,pos2 = pos2 - 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    myservo2.write(pos2);
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180,pos2 = 0; pos>=0; pos-=1,pos2 = pos2 + 1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    myservo2.write(pos2);
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
    }
    else if(now.minute() != one3m && med1 == 0)
    {
      Serial.println("I am in else");
      med1 = -1;
    }
  
  
}






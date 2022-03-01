#include "Ultrasonic.h"
#include "TM1637.h"
#define ON 1
#define OFF 0

int8_t DisDisp[] = {0x00, 0x00, 0x00, 0x00};

#define CLK 2//pins definitions for TM1637 and can be changed to other ports
#define DIO 3
TM1637 tm1637(CLK, DIO);

Ultrasonic ultrasonic(7);

void setup()
{
  //4-Digit setup
    tm1637.set();
    tm1637.init();
  //Ultra son
    Serial.begin(9600);

    DisDisp[0] = 0;
    DisDisp[1] = 2;
    DisDisp[2] = 3;
    DisDisp[3] = 4;
    tm1637.display(DisDisp);
    pinMode(6, OUTPUT);

}

void loop()

{
    long RangeInCentimeters;

    RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
    
    if(RangeInCentimeters > 10  && RangeInCentimeters <= 50){
      digitalWrite(6, HIGH);
      delay(500);
      digitalWrite(6, LOW);
      delay(500);
    }
    if(RangeInCentimeters <= 10){
      digitalWrite(6, HIGH);
    }
    
    //DisDisp[0] = 1;
    DisDisp[1] = RangeInCentimeters /100;
    DisDisp[2] = (RangeInCentimeters %100)/10;
    DisDisp[3] = RangeInCentimeters %100%10;
    tm1637.display(DisDisp);

    delay(250);

}

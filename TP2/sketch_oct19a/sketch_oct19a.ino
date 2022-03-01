/*macro definitions of PIR motion sensor pin and LED pin*/
#include "Ultrasonic.h"
#define PIR_MOTION_SENSOR 2//Use pin 2 to receive the signal from the module
#define ON 1
#define OFF 0
int REDLED = 8;
int GreenLed = 6;
boolean Allumer = false;
int LedButtonpin = 4;
int Buttonpin = 5;
long RangeInCentimeters;
Ultrasonic ultrasonic(7);
int buttonState = HIGH;

void setup()
{
    pinMode(Buttonpin, INPUT);
    pinMode(LedButtonpin, OUTPUT);
    pinMode(PIR_MOTION_SENSOR, INPUT);
    digitalWrite(LedButtonpin, LOW);
    Serial.begin(9600);  
    
}

void loop()
{
   int reading = digitalRead(Buttonpin);
   
   if (reading != LOW) {
    Allumer = !Allumer;
    }
    Serial
     if( Allumer){
        digitalWrite(REDLED, HIGH);
        if(digitalRead(PIR_MOTION_SENSOR) && RangeInCentimeters <= 10){
          
          RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
          //Serial.println("Hi,people is coming");
          //Serial.println(RangeInCentimeters);
        }
        else{      
            //Serial.println("Watching");
          }
          delay(200);
     }
   else{
    digitalWrite(GreenLed, HIGH);
   }
}

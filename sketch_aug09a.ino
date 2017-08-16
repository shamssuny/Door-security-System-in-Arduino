/*
 * Author : Shams Shahriar
 * Batch-38, Bsc in CSE , Daffodil International University
 * Project: Simple Door Security System
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
int btn1=8,btn2=12;
int btn1state,btn2state;
int pass1=0,pass2=0;
int logged =0;
int buzz = 0;
int stat = LOW;
unsigned long previousMillis = 0;
int del = 1000;
//sensor pins intialize
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;
void setup(){
  //Serial.begin(9600);
  //initial lcd
  lcd.init();                      // initialize the lcd 
 // Print a message to the LCD.
 lcd.backlight();

    pinMode(btn1,INPUT);
    pinMode(btn2,INPUT);

    //sensors
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT);

    pinMode(2,OUTPUT);
}

void loop(){
  if(logged ==0){
      lcd.setCursor(0,0);
      lcd.print("System Off");

      btn1state = digitalRead(btn1);
      if(btn1state == HIGH){
          delay(100);
          pass1++;
          if(pass1>9){
              pass1=0;
            }
        }


      btn2state = digitalRead(btn2);
      if(btn2state == HIGH){
          delay(100);
          pass2++;
          if(pass2>9){
              pass2=0;
            }
        }

        lcd.setCursor(0,1);
        lcd.print("Pass-");
        lcd.print(pass1);
        lcd.print(pass2);
    
       if(pass1 == 3 && pass2 == 3){
          logged = 1;
          pass1=0;
          pass2=0;
        }   
    }


    if(logged == 1){
        //lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("System On...");
        lcd.setCursor(0,1);
        lcd.print("Pass-");
        lcd.print(pass1);
        lcd.print(pass2);


        btn1state = digitalRead(btn1);
      if(btn1state == HIGH){
          delay(100);
          pass1++;
          if(pass1>9){
              pass1=0;
            }
        }


      btn2state = digitalRead(btn2);
      if(btn2state == HIGH){
          delay(100);
          pass2++;
          if(pass2>9){
              pass2=0;
            }
        }


        if(pass1 == 3 && pass2 == 3){
          logged = 0;
          pass1=0;
          pass2=0;
          buzz=0;
          stat = LOW;
          lcd.clear();
          digitalWrite(2,LOW);
          lcd.backlight();
        }


        // Clears the trigPin
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        duration = pulseIn(echoPin, HIGH);
        // Calculating the distance
        distance= duration*0.034/2;
        //Serial.println(distance);
        if(distance<6){
            lcd.print("-Breach!");
            buzz = 1;
            //digitalWrite(2,HIGH);
          }

        if(buzz == 1){
            unsigned long currentMillis = millis();

              if (currentMillis - previousMillis >= del) {
                // save the last time you blinked the LED
                previousMillis = currentMillis;
            
                // if the LED is off turn it on and vice-versa:
                if (stat == LOW) {
                  stat = HIGH;
                  lcd.noBacklight();
                } else {
                  stat = LOW;
                  lcd.backlight();
                }
            
                // set the LED with the ledState of the variable:
                digitalWrite(2, stat);
              }
          }
        
      }
}

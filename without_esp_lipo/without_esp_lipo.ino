
#include <SoftwareSerial.h>
#define red 6
#define yellow 4
#define green 3
#define blue 5
#define lipo A3
float lipoV=0;
float v=0;
float i=0;
int r = 2;
float c = 0; 
float e = 0;
float t = 0;
float id = 0;
void setup()
{
  pinMode (red,OUTPUT);
  pinMode (blue,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(lipo,INPUT);
  Serial.begin(9600);
  delay(5000);
  }
void loop()
{ 
lipoV=analogRead(lipo);
Serial.println(lipoV);
Serial.print("battery voltage");
v = (lipoV * 5)/1023;
i= v/r;
  e = v*i;
  c = e/v;
  id = 1.5*c;
  t = c/id;

    if(lipoV<950)
    {
      digitalWrite(red,HIGH);
      digitalWrite(yellow,LOW);
      digitalWrite(green,LOW);
      Serial.println(lipoV);
      Serial.println(v);
      Serial.println("Low Battery locate for EVCS ASAP");
      Serial.println(e);
      Serial.println("Wh");
      Serial.println(c);
      Serial.println("Ah");
      Serial.println(t);
      Serial.println("h");
      Serial.println(id);
      Serial.println("A,discharging current");
      delay(500);   
    }
    if(lipoV>950 && lipoV<1000)
    {
      digitalWrite(red,LOW);
      digitalWrite(yellow,HIGH);
      digitalWrite(green,LOW);
      Serial.println(lipoV);
      Serial.println(v);
      Serial.println("getting low battery");
      Serial.println(c);
      Serial.println("Ah");
      Serial.println(t);
      Serial.println("h");
      Serial.println(id);
      Serial.println("A,discharging current");
      delay(500);   
    }
      if(lipoV>1000)
      {
        digitalWrite(red,LOW);
        digitalWrite(yellow,LOW);
        digitalWrite(green,HIGH);
        Serial.println(lipoV);
        Serial.println(v);
        Serial.println("green battery");
        Serial.println(c);
        Serial.println("Ah");
        Serial.println(t);
        Serial.println("h");
        Serial.println(id);
        Serial.println("A,discharging current");
        delay(500);
      }
}


 

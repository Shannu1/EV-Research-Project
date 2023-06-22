
#include <SoftwareSerial.h>
//#include <string.h>
#define TIMEOUT 1000//mS
SoftwareSerial Serial1(2,3);//Rx,Tx
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
  Serial1.begin(9600);
  SendCommand("AT+RST", "Ready");
  delay(5000);
  SendCommand("AT+CWMODE=1","OK");
  SendCommand("AT+CIFSR","OK");
  SendCommand("AT+CIPMUX=1","OK");
  SendCommand("AT+CIPSERVER=1,80","OK");
 
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

String IncomingString="";
boolean StringReady = false;
while (Serial1.available())
{
  IncomingString=Serial1.readString();
  boolean StringReady=true;
  }
  if(StringReady)
  {
    Serial.println("Received String: " + IncomingString);
  }
    if(lipoV<950)
    {
      digitalWrite(red,HIGH);
      digitalWrite(yellow,LOW);
      digitalWrite(green,LOW);
      Serial.println(lipoV);
      Serial.println(v);
      Serial.println("low battery");
      Serial.println(e);
      Serial.println("Wh");
      Serial.println(c);
      Serial.println("Ah");
      Serial.println(t);
      Serial.println("h");
      Serial.println(id);
      Serial.println("A,discharging current");
      delay(500);
      SendCommand("AT+CIPSEND=0,33","OK");
      Serial1.println("AT+CIPSEND=0,33");
      Serial1.println("<h1>Low Battery locate for EVCS ASAP.!</h1>");
      delay(1000);
      SendCommand("AT+CIPCLOSE=0","OK");
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
      SendCommand("AT+CIPSEND=0,35","OK");
     
      Serial1.println("AT+CIPSEND=0,35");
      Serial1.println("<h1>Getting Low Battery locate for EVCS.!</h1>");
      delay(1000);
      SendCommand("AT+CIPCLOSE=0","OK");
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
        SendCommand("AT+CIPSEND=0,23","OK");
        
        Serial1.println("AT+CIPSEND=0,23");
        Serial1.println("<h1> Good Battery its green.!</h1>");
        delay(1000);
        SendCommand("AT+CIPCLOSE=0","OK");
      }

}


  boolean SendCommand(String cmd, String ack)
{
  Serial1.println(cmd);
  if (!echoFind(ack))
  return true;
}
 boolean echoFind(String keyword)
{
  byte current_char = 0;
  byte keyword_length = keyword.length();
  long deadline= millis()+ TIMEOUT;
  while(millis()< deadline)
  {
    if (Serial1.available())
    {
      char ch = Serial1.read();
      Serial.write(ch);
      if ((ch== keyword[current_char]) && (++current_char== keyword_length))
      {
        Serial.println();
        return true;
      }
    }
  }
  return false;
}

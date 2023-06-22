
#include <SoftwareSerial.h>
//#include <string.h>
#define TIMEOUT 5000//mS
SoftwareSerial mySerial(7,8);//Rx,Tx
#define red 6
#define yellow 4
#define green 3
#define lipo A1
float lipoV=0;
float v=0;
void setup()
{
  pinMode (red,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(lipo,INPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  SendCommand("AT+RST","Ready");
  delay(5000);
  SendCommand("AT+CWMODE=1","OK");
  SendCommand("AT+CIFSR","OK");
  SendCommand("AT+CIPMUX=1","OK");
  SendCommand("AT+CIPSERVER=1,80","OK");
  mySerial.setTimeout(5000);
  }
void loop()
{
  
lipoV=analogRead(lipo);
Serial.println(lipoV);
Serial.print("battery voltage");
v = (lipoV * 5)/1023;

String IncomingString="";
boolean StringReady = false;
while (mySerial.available())
{
  IncomingString=mySerial.readString();
  boolean StringReady=true;
  }
  if(StringReady)
  {
    Serial.println("Received String: " + IncomingString);
    }
    if(lipoV<850)
    {
      digitalWrite(red,HIGH);
      digitalWrite(yellow,LOW);
      digitalWrite(green,LOW);
      Serial.println(lipoV);
      Serial.println(v);
      Serial.println("low battery");
      mySerial.println("AT+CIPSEND=0,33");
      mySerial.println("<h1>Low Battery locate for EVCS ASAP.!</h1>");
      delay(1000);
      SendCommand("AT+CIPCLOSE=0","OK");
    }
    if(lipoV>900 && lipoV<950)
    {
      digitalWrite(red,LOW);
      digitalWrite(yellow,HIGH);
      digitalWrite(green,LOW);
      Serial.println(lipoV);
      Serial.println(v);
      Serial.println("getting low battery");
      mySerial.println("AT+CIPSEND=0,35");
      mySerial.println("<h1>Getting Low Battery locate for EVCS.!</h1>");
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
        mySerial.println("AT+CIPSEND=0,23");
        mySerial.println("<h1> Good Battery its green.!</h1>");
        delay(1000);
        SendCommand("AT+CIPCLOSE=0","OK");
      }
}


  boolean SendCommand(String cmd, String ack)
{
  mySerial.println(cmd);
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
    if (mySerial.available())
    {
      char ch = mySerial.read();
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

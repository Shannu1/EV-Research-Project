 
#define red   6
#define yellow 4
#define green 3
#define lipo  A1
float lipoV = 0;
float v = 0;

void setup() 
{
pinMode(red,OUTPUT);
pinMode(yellow,OUTPUT);
pinMode(green,OUTPUT);
pinMode(lipo,INPUT);
Serial.begin(9600);

}
void loop() 
{
lipoV = analogRead(lipo);  
Serial.println(lipoV);
Serial.print("battery voltage");
v = (lipoV * 5  )/1023;
if(lipoV<850)
{
  digitalWrite(red,HIGH);
  digitalWrite(yellow,LOW);
  digitalWrite(green,LOW);
  Serial.println(lipoV);
  Serial.println(v);
  Serial.println("low battery");
  delay(1000);
}
if(lipoV>900 && lipoV<950)
{ 
  digitalWrite(red,LOW);
  digitalWrite(yellow,HIGH);
  digitalWrite(green,LOW);
  Serial.println(lipoV);
  Serial.println(v);
  Serial.println("getting low battery");
  delay(1000);
}
if(lipoV>1000)
{
  digitalWrite(red,LOW);
  digitalWrite(yellow,LOW);
  digitalWrite(green,HIGH);
  Serial.println(lipoV);
  Serial.println(v);
  Serial.println("green battery");
  delay(1000);
}
}

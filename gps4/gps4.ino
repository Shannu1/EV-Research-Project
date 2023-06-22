#include<SoftwareSerial.h>
#include <TinyGPS++.h>
SoftwareSerial Serial1(2,3);    
SoftwareSerial gps(10,11);
#define red 6
#define yellow 4
#define green 3
#define lipo A3
float lipoV=0;
float v=0;
float ic=0;

int r = 2;
float c = 0; 
float e = 0;
float t = 0;
float id = 0;
boolean No_IP=false;
String IP="";

String webpage="";
int i=0,k=0;
int  gps_status=0;
String name="<p>1. Name: Shaik Shahanaz </p>";   

String number="<p>2. Vehicle No.: XXXX XY 0001</p>";
String cordinat="<p>Coordinates:</p>";          
String latitude=""; 
String logitude="";                       

String gpsString="";
char *test="$GPGGA";

void check4IP(int t1)
{
  int t2=millis();
  while(t2+t1>millis())
  {
    while(Serial1.available()>0)
    {
      if(Serial1.find("WIFI GOT IP"))
      {
        No_IP=true;
      }
    }
  }
}

void get_ip()
{
  IP="";
  char ch=0;
  while(1)
  {
    Serial1.println("AT+CIFSR");
    while(Serial1.available()>0)
    {
      if(Serial1.find("STAIP,"))
      {
        delay(1000);
        Serial.print("IP Address:");
        while(Serial1.available()>0)
        {
          ch=Serial1.read();
          if(ch=='+')
          break;
          IP+=ch;
        }
      }
      if(ch=='+')
      break;
    }
    if(ch=='+')
    break;
    delay(1000);
  }
  
  Serial.print(IP);
  Serial.print("Port:");
  Serial.println(80);
  delay(1000);
}

void connect_wifi(String cmd, int t)
{
  int temp=0,i=0;
  while(1)
  {
    Serial.println(cmd);
    Serial1.println(cmd); 
    while(Serial1.available()>0)
    {
      if(Serial1.find("OK"))
      {

      i=8;
      }
    }
    delay(t);
    if(i>5)
    break;
    i++;
  }
  if(i==8)
  {
    Serial.println("OK");
  }
  else
  {
  Serial.println("Error");
  }
  delay(1000);
}

void setup() 
{
  pinMode (red,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(lipo,INPUT);
  Serial1.begin(9600);
  Serial.begin(9600); 
  delay(1000);
  connect_wifi("AT",1000);
  connect_wifi("AT+CWMODE=3",1000);
  connect_wifi("AT+CWQAP",1000);  
  connect_wifi("AT+RST",5000);
  check4IP(5000);
  if(!No_IP)
      {
        Serial.println("Connecting Wifi....");
        connect_wifi("AT+CWJAP=\"Flat-4 Gables\",\"Muneer@123\"",7000);   //AT+CWJAP=�wifi_username�,�wifi_password�
      }
      else
        {
        }
      Serial.println("Wifi Connected");
       
      get_ip();
      delay(2000);
      connect_wifi("AT+CIPMUX=1",100);
      connect_wifi("AT+CIPSERVER=1,80",100);
      Serial1.end();
      delay(2000);
      gps.begin(9600);
      get_gps();
      bms_details();
      show_coordinate();
      gps.end();
      Serial1.begin(9600);
      delay(2000);
      Serial.println("System Ready..");
}

void loop() 
{
  k=0;
  Serial.println("Please Refresh Ur Page");
  
  while(k<1000)
  {
    k++;

   while(Serial1.available())
   {
    if(Serial1.find("0,CONNECT"))
    {
      Serial1.end();
  gps.begin(9600);
  get_gps();
  gps.end();
  Serial1.begin(9600);
  Serial1.flush();
   
      Serial.println("Start Printing");
      Send();
      show_coordinate();
      Serial.println("Done Printing");
      delay(5000);
      
      k=1200;
      break;
    }
  }
  delay(1);
 }
}

void gpsEvent()
{
  gpsString="";
  while(1)
  {
   while (gps.available()>0)                //Serial incoming data from GPS
   {
    char inChar = (char)gps.read();
     gpsString+= inChar;                    //store incoming data from GPS to temporary string str[]
     i++;
     if (i < 7)                      
     {
      if(gpsString[i-1] != test[i-1])       //check for right string
      {
        i=0;
        gpsString="";
      }
     }
    if(inChar=='\r')
    {
     if(i>65)
     {
       gps_status=1;
       break;
     }
     else
     {
       i=0;
     }
    }
  }
   if(gps_status)
    break;
  }
}

void get_gps()
{
   gps_status=0;
   int x=0;
   while(gps_status==0)
   {
    gpsEvent();
    int str_lenth=i;
    latitude="";
    logitude="";
    coordinate2dec();
        i=0;x=0;
    str_lenth=0;
   }
}
void bms_details()
{
 lipoV=analogRead(lipo);
Serial.println(lipoV);
Serial.print("battery voltage");
v = (lipoV * 5)/1023;
ic= v/r;
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
 
}
}
void show_coordinate()
{
    
    Serial.print("Latitude:");
    Serial.println(latitude);
    Serial.print("Longitude:");
    Serial.println(logitude);
}

void coordinate2dec()
{
    
    //j=0;
    String lat_degree="";
    for(i=18;i<28;i++)          //extract latitude from string
      lat_degree+=gpsString[i];
   
    String lat_minut="";
    for(i=28;i<30;i++)
      lat_minut+=gpsString[i];
    
    String long_degree="";
    for(i=30;i<33;i++)          //extract longitude from string
      long_degree+=gpsString[i];
      
    String long_minut="";
    for(i=33;i<41;i++)
      long_minut+=gpsString[i];
      
     float minut= lat_minut.toFloat();
     minut=minut/60;
     float degree=lat_degree.toFloat();
     latitude=degree+minut;
     
     minut= long_minut.toFloat();
     minut=minut/60;
     degree=long_degree.toFloat();
     logitude=degree+minut;
}

void Send()
{
     
      webpage = "<h1>Welcome to EV CS navigation System</h1><body bgcolor=f0f0f0>";
      webpage+=name;
     
      webpage+=number;
      webpage+=cordinat;
      webpage+="<p>Latitude:";
      webpage+=latitude;
      webpage+="</p>";
      webpage+="<p>Longitude:";
      webpage+=logitude;
      webpage+="</p>";
      webpage+= "<a href=\"http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=";
      webpage+=latitude;
      webpage+='+';             
      webpage+=logitude;
      webpage+="\">Click Here for google map</a>";
    sendwebdata();
       webpage="";

     while(1)
     {
      Serial.println("AT+CIPCLOSE=0");
      Serial1.println("AT+CIPCLOSE=0");
      while(Serial1.available())
      {
        //Serial.print(Serial1.read());
        if(Serial1.find("0,CLOSE"))
        {
          return;
        }
      }
      delay(500);
      i++;
      if(i>5)
      {
        i=0;
      }
      if(i==0)
      break;
     }
}

void sendwebdata()
{
     i=0;
     while(1)
     {
      unsigned int l=webpage.length();
      Serial1.print("AT+CIPSEND=0,");
      Serial1.println(l+2);
      Serial.println(l+2);
      Serial.println(webpage);

      Serial1.println(webpage);
      while(Serial1.available())
      {
        if(Serial1.find("OK"))
        {
         return;
        }
      }
            i++;
      if(i>5)
        i=0;
        if(i==0)
        break;
      delay(200);
     }
}

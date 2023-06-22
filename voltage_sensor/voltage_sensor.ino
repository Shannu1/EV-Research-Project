  float correctionfactor = .1;
int analogInput = A1;
float vout = 0.0;
float vin =0.0;




float R1 = 30000;   
float R2 = 7500;  
int value = 0; 
void setup() 
{
  pinMode(analogInput, INPUT);
  Serial.begin(9600);
  Serial.print("DC VOLTMETER");
}
void loop()
{
 
  value = analogRead(analogInput);
  vout = (value * 5.0) / 1023.0;
  vin - vout / (R2/(R1+R2));

  vin = vin - correctionfactor;
Serial.print("INPUT V = ");
Serial.println(vin,4);
delay(500);
}

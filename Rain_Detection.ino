
//Prateek
//wwww.prateeks.in
//https://www.youtube.com/c/JustDoElectronics/videos

#include <SoftwareSerial.h>
#define RAIN_SENSOR A0

int rain_value = 0;
int rain_default=10;
boolean rain_flag = 0;
const String PHONE = "+918830584864";
#define rxPin 2
#define txPin 3

SoftwareSerial sim800L(rxPin,txPin);
void setup()
{
  
  Serial.begin(115200);
  sim800L.begin(9600);
  pinMode(RAIN_SENSOR,INPUT);
  Serial.println("Initializing...");
  sim800L.println("AT");
  delay(1000);
  sim800L.println("AT+CMGF=1");
  delay(1000);

}
void loop()
{
  while(sim800L.available()){
  Serial.println(sim800L.readString());
  }
  
  rain_value = analogRead(RAIN_SENSOR);
  rain_value = map(rain_value,0,1023,225,0);
  
  if(rain_value>=rain_default) {
    if(rain_flag == 0) {
      Serial.println("Rain is Detected.");
      rain_flag == 1;
      send_sms();
      make_call();
    }
  }
  else {
    if(rain_flag == 1) {Serial.println("Rain is not Detected.");}  
    rain_flag = 0;
  }
}
void make_call()
{
    Serial.println("calling....");
    sim800L.println("ATD"+PHONE+";");
    delay(20000); //20 sec delay
    sim800L.println("ATH");
    delay(1000); //1 sec delay
}

void send_sms()
{
    Serial.println("sending sms....");
    delay(50);
    sim800L.print("AT+CMGF=1\r");
    delay(1000);
    sim800L.print("AT+CMGS=\""+PHONE+"\"\r");
    delay(1000);
    sim800L.print(" Rain Alarm Plz Check Your Window");
    delay(100);
    sim800L.write(0x1A);
    delay(5000);
}

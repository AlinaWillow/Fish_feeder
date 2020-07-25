// Date, Time and Alarm functions using a DS3231 RTC connected via I2C and Wire lib

#include "Wire.h"
#include "SPI.h"  // not used here, but needed to prevent a RTClib compile error
#include "RTClib.h"

RTC_DS3231 RTC;

#include <Servo.h>
Servo myservo; 
char servo_pin = 9;
int sec = 500;


void setup () {
  
  myservo.attach(servo_pin);
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  RTC.adjust(DateTime(__DATE__, __TIME__));

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
   // RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  DateTime now = RTC.now();

 /*RTC.setAlarm1Simple(15, 43);

 RTC.turnOnAlarm(1);*/

  if (RTC.checkAlarmEnabled(1)) {
    Serial.println("Alarm Enabled");
  }
 

}

void loop () {

  DateTime now = RTC.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);

  /*if (RTC.checkIfAlarm(1)) {
    Serial.println("Alarm Triggered");
  }*/

     if (now.hour() == 16 && now.minute() == 5 && now.second()== 0) { 
      for(int i=0;i<=1;i+=1){
        myservo.write(45);
        //Serial.print("1");
        delay(sec);

        myservo.write(0);
       // Serial.print("0");
        delay(sec);
      } 
      Serial.println("SERVO ON");
     }    
    
  
  
  Serial.println();
  Serial.print("Tempeature = ");
  Serial.print(RTC.getTemperature()); // คำสั่งดึงอุณหภูมิออกมาแสดง
  Serial.println(" C");

  Serial.println("By ArduinoALL");
  Serial.println();
  delay(1000);
}

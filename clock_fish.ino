// Date, Time and Alarm functions using a DS3231 RTC connected via I2C and Wire lib

#include "Wire.h"
#include "SPI.h"  // not used here, but needed to prevent a RTClib compile error
#include "RTClib.h"

RTC_DS3231 RTC;

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

#include <Servo.h>
Servo myservo; 
char servo_pin = 9;
int sec = 500;

void setup () {

  myservo.attach(servo_pin);
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  //RTC.adjust(DateTime(__DATE__, __TIME__));

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  DateTime now = RTC.now();
  myservo.write(0);
 

}

void loop () {

  DateTime now = RTC.now();
  lcd.begin();
  lcd.print(now.year());
  lcd.print('/');
  lcd.print(now.month());
  lcd.print('/');
  lcd.print(now.day());
  
  lcd.setCursor(0,1);
  lcd.print(now.hour());
  lcd.print(':');
  lcd.print(now.minute());
  lcd.print(':');
  lcd.print(now.second());

  lcd.setCursor(0,2);

  lcd.print("Temp = ");
  lcd.print(RTC.getTemperature()); // คำสั่งดึงอุณหภูมิออกมาแสดง
  lcd.print(" C");

  lcd.setCursor(0,3);
  lcd.print("By Liu beauty");

   
  if(now.hour() == 21 && now.minute() == 2 && now.second()== 0){
    servotrig();
  }
}

void lcdtrig(){
  lcd.clear();
    lcd.setCursor(4,2);
    lcd.print("Servo On"); 
  }

void servotrig(){
  for(int i=0;i<=1;i+=1){
        lcdtrig();
        myservo.write(45);
        delay(1000);
        myservo.write(0);
        delay(1000);
  }
} 

#include <ButtonDebounce.h>

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "gw8rE1Sq0DUQO7tEiJIHrzPUg8Dqx35J";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "PTNP";
char pass[] = "Wiboonbajaree1969";
Servo servo; //D6
int sw = D1;
ButtonDebounce button(D1, 250);

BLYNK_WRITE(V3)
{
  if (param.asInt()==0){
 
        servo.write(0);
        Serial.print("0 tele "); 
        delay(500); 
        servo.write(15);  
        delay(500); 
        Serial.println("15 tele");
 
  }

}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  servo.attach(12);
  pinMode(sw, INPUT_PULLUP);
  button.setCallback(buttonChanged);
  
}

void loop()
{
  Blynk.run();
  button.update();
  
}
void buttonChanged(int state){
  Serial.println("Changed: " + String(state));
  if(digitalRead(sw)== 0){
    servo.write(15);
    Serial.println("15 Botton");
  }
  else{
    servo.write(0);
    Serial.println("0 Botton");
  }
}

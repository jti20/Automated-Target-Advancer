//HC-12 Toggle button Send
//Autor Tom Heylen tomtomheylen.com


#include <SoftwareSerial.h>
#include <Wire.h>
#include "SparkFunBME280.h"


SoftwareSerial mySerial(2, 3); //RX, TX

String string1 = "";
String string2 = "";
String string3 = "";
String string4 = "";
int int1 = 0;
int int2 = 0;
int int3 = 0;
float windspeed = 0.0;
int windpin = A0;
String totalstring = "";

BME280 mySensor; //Uses default I2C address 0x77

void setup() {
  mySerial.begin(9600);
  Wire.begin();
  mySensor.setI2CAddress(0x77); //The default for the SparkFun Environmental Combo board is 0x77 (jumper open).
  if(mySensor.beginI2C() == false) Serial.println("Sensor connect failed");
  Serial.begin(9600);
}

void loop() {
  //Read environmental data
  int1 = (int)(mySensor.readFloatHumidity());
  int2 = (int)(mySensor.readFloatPressure()/1000);
  int3 = (int)(mySensor.readTempF());

  //Read winspeed data and convert to MPH
  windspeed = analogRead(windpin);
  Serial.println(windspeed);
  windspeed = windspeed*(5.0/1024.0);
  windspeed = (20.25*windspeed)-8.1;
  windspeed = windspeed*2.237;
  if(windspeed<0){
    windspeed = 0;
  }

  //Convert data to string for transmission
  string1 = String(int1);
  string2 = String(int2);
  string3 = String(int3);
  string4 = String(windspeed);

  //Concatonate strings with "!" to separate individual pieces of data
  totalstring = string1+"!"+string2+"!"+string3+"!"+string4;

  //Send string over HC-12
  mySerial.print(totalstring);
  Serial.println(totalstring);  
  delay(2000);
}







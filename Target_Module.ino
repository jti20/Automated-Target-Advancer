#include <SoftwareSerial.h>
#include <Wire.h>
#include "SparkFunBME280.h"


SoftwareSerial mySerial(2, 3); //RX, TX

//Initialize Constants
String string1 = "";
String string2 = "";
String string3 = "";
String string4 = "";
String string5 = "";
int int1 = 0;
int int2 = 0;
int int3 = 0;
float windspeed = 0.0;
int windpin = A0;
String totalstring = "";
float theta = 0.0;

//Motor Control Constants
int Motor = 8;
const int Sensor_PIN = A1; // Sensor output voltage
int changeTarget = 1;      // Received from the controller to index target
int i = 0;                 // For finding average
float proximity_AVG = 0.0; // Average of the signals from the sensor
const int wind_dir = A2;   // Wind Vane input

BME280 mySensor; //Uses default I2C address 0x77

void setup() {
  mySerial.begin(1200);
  Wire.begin();
  mySensor.setI2CAddress(0x77); //The default for the SparkFun Environmental Combo board is 0x77 (jumper open).
  if(mySensor.beginI2C() == false) Serial.println("Sensor connect failed");
  Serial.begin(9600);
  pinMode(Motor, OUTPUT);
}

void loop() {
  //Code for motor control

  //Check if there is a change target command available
  if(mySerial.available() > 1){
    String strinput = mySerial.readString();
    //Serial.println(strinput);
    if(strinput.charAt(0) == '1'){
      //Serial.println("Motor");
      //RollMotor
      changeTarget = 1;
      // Turn motor on
      digitalWrite(Motor, HIGH);
      Serial.println("Motor On");
      // Wait to get off initial black mark
      delay(3000);
      // Code for sensing stop black mark
    while (changeTarget == 1){    //While no stop signal detected
      int proximityADC = analogRead(Sensor_PIN);   //Read Sensor
      i += 1;      
      float proximityV = (float)proximityADC * 5.0 / 1023.0; // Convert to 0-5 Volts
      proximity_AVG += proximityV;           //AVG of Sensor
      //Serial.println(proximityV);                          
      delay(100);                          //Delay between sensing - the actual is 1s
      if (i  == 9){                      //After 1s, Check for black mark
        proximity_AVG = proximity_AVG/10.0;
        //Serial.println(proximity_AVG);
        i = 0;
        if (proximity_AVG > 3){   //If average sensor reading is > 3 then turn motor off
          digitalWrite(Motor,LOW);
          changeTarget = 0;             
        }
        proximity_AVG = 0;
      }
    }     
    }
  }
  
  //Read environmental data
  int1 = (int)(mySensor.readFloatHumidity());
  int2 = (int)(mySensor.readFloatPressure()/1000);
  int3 = (int)(mySensor.readTempF());

  //Read Wind Direction
  theta = analogRead(wind_dir);
  theta = theta*(5.0/1024.0);
  theta = .036*((19100.0-3820*theta)/theta);
  theta = (int) theta;
  if(theta > 360){
    theta = 360;
  }
  int temptheta = theta;
  String strtheta = String(temptheta);
  strtheta = String(strtheta);
  //Serial.println(strtheta);

  //Read windspeed data and convert to MPH
  windspeed = analogRead(windpin);
  //Serial.println(windspeed);
  windspeed = windspeed*(5.0/1024.0);
  windspeed = (20.25*windspeed)-8.1;
  windspeed = windspeed*2.237;
  if(windspeed<0){
    windspeed = 0;
  }
  if(windspeed>99){
    windspeed = 0;
  }

  //Convert data to string for transmission
  string1 = String(int1);
  string2 = String(int2);
  string3 = String(int3);
  string4 = String(windspeed);
  string5 = String(strtheta);

  //Concatonate strings with "!" to separate individual pieces of data
  totalstring = string1+"!"+string2+"!"+string3+"!"+string4+"!"+string5;

  //Send string over HC-12
  mySerial.print(totalstring);
  //Serial.println(totalstring);  
  delay(2000);
}







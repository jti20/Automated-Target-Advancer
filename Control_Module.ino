#include <LiquidCrystal.h>// include the library code
#include <SoftwareSerial.h>
/**********************************************************/
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);
SoftwareSerial mySerial(2, 3); // RX, TX
int button = 7;
int changecount = 0;
int clearcount = 0;

void setup() {
  lcd.begin(20, 4);  // set up the LCD's number of columns and rows:
  mySerial.begin(1200);
  Serial.begin(9600);
  //Setup button for target advacnce
  pinMode(button, INPUT);
}

void loop() {
  //Check for target change button
  if(digitalRead(button) == HIGH){
    Serial.println("Changing Target");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Changing Target");
    while(changecount < 100){
    mySerial.print("1");
    changecount+=1;
    delay(20);
    }
    while(changecount < 300){
      lcd.setCursor(0,0);
      lcd.print("Changing Target");
      changecount+=1;
      delay(20);
    }
    changecount = 0;
    //Read leftover data to get rid of it
    if(mySerial.available()>1){
      mySerial.readString();
    }
    }

  //Check if data is available on HC-12
  if(mySerial.available() > 1){
    String input = mySerial.readString();
    Serial.println(input);
    //Parse incoming string to get individual data
    int stop1 = input.indexOf('!');
    int stop2 = input.indexOf('!',stop1+1);
    int stop3 = input.indexOf('!',stop2+1);
    int stop4 = input.indexOf('!',stop3+1);

    String string1 = input.substring(0,stop1);
    String string2 = input.substring(stop1+1,stop2);
    String string3 = input.substring(stop2+1,stop3);
    String string4 = input.substring(stop3+1,stop4);
    String string5 = input.substring(stop4+1);

    //Serial.println(string5);

    //Add identifiers to data based on order. Also add padding.
    string1 = "Humidity: " + string1 + "%";
//    if(string1.length() < 20){
//      int numpad = 20 - string1.length();
//      for(int i=0; i<numpad; i++){
//        string1 += ' ';
//      }
//    }
    string1 += ' ';
    string1 += ' ';

    string2 = "Pressure: " + string2 + " kPa";
    if(string2.length() < 20){
      int numpad = 20 - string2.length();
      for(int i=0; i<numpad; i++){
        string2 += ' ';
      }
    }
    string3 = "Temp: " + string3 + " F";
    if(string3.length() < 20){
      int numpad = 20 - string3.length();
      for(int i=0; i<numpad; i++){
        string3 += ' ';
      }
    }
    string4 = "Windspeed: " + string4 + " MPH";
    if(string4.length() < 20){
      int numpad = 20 - string4.length();
      for(int i=0; i<numpad; i++){
        string4 += ' ';
      }
    }
    if(string5.length() < 3){
      int numpad = 3-string5.length();
      for(int i=0; i<numpad; i++){
        string5 += ' ';
      }
    }
  

    //Print to LCD Screen
    lcd.setCursor(0,3);
    lcd.print(string1);
    delay(20);
    lcd.setCursor(0,1);
    lcd.print(string2);
    delay(20);
    lcd.setCursor(0,2);
    lcd.print(string3);
    delay(20);
    lcd.setCursor(0,0);
    lcd.print(string4);
    lcd.setCursor(17,3);
    lcd.print(string5);
  }
  delay(50);
}

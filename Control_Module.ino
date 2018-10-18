#include <LiquidCrystal.h>// include the library code
#include <SoftwareSerial.h>
/**********************************************************/
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);
SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
  lcd.begin(20, 4);  // set up the LCD's number of columns and rows:
  mySerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if(mySerial.available() > 1){
    //Check if data is available on HC-12
    String input = mySerial.readString();
    Serial.println(input);

    //Parse incoming string to get individual data
    int stop1 = input.indexOf('!');
    int stop2 = input.indexOf('!',stop1+1);
    int stop3 = input.indexOf('!',stop2+1);

    String string1 = input.substring(0,stop1);
    String string2 = input.substring(stop1+1,stop2);
    String string3 = input.substring(stop2+1,stop3);
    String string4 = input.substring(stop3+1);

    //Add identifiers to data based on order
    string1 = "Humidity: " + string1 + "%";
    string2 = "Pressure: " + string2 + " kPa";
    string3 = "Temp: " + string3 + " F";
    string4 = "Windspeed: " + string4 + " MPH";

    //Print to LCD Screen
    lcd.setCursor(0,0);
    lcd.print(string1);
    delay(20);
    lcd.setCursor(0,1);
    lcd.print(string2);
    delay(20);
    lcd.setCursor(0,2);
    lcd.print(string3);
    delay(20);
    lcd.setCursor(0,3);
    lcd.print(string4);
  }
  delay(500);
}

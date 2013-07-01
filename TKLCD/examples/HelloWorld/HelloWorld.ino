/**
* Simple Hello World program. To be run on an Arduino connected
* to a TinkerKit LCD module via Serial.
*/

#include <Wire.h>
#include <LiquidCrystal.h>
#include <TKLCD.h>

//TKLCD_Serial lcd = TKLCD_Serial(); // when connecting to TKLCD over Serial
TKLCD_Local lcd = TKLCD_Local(); // when programming a TKLCD module itself


void setup() {
  lcd.begin();
  
  lcd.clear();
  
  lcd.print("Hello World!");
}

void loop() {
   // nothing do be done
}

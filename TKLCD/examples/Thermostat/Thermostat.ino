/**
* Simple Thermostat Example
*/

#include <LiquidCrystal.h>
#include <TKLCD.h>
#include <TinkerKit.h>
#include <Wire.h>

//TKLCD_Serial lcd = TKLCD_Serial(); // when connecting to TKLCD over Serial
TKLCD_Local lcd = TKLCD_Local(); // when programming a TKLCD module itself
TKThermistor therm = TKThermistor(A0);


void setup() {
  lcd.begin();
  
  lcd.clear();
}

void loop() {
  
  int temp = therm.readCelsius();
  
  lcd.home();
  lcd.print("TEMP: ");
  lcd.print(temp);
  lcd.print("C   ");
  lcd.setCursor(0,1);
  
  if(temp < 20) {
    lcd.print("HEATING    ");
  }
  else if (temp > 30){
    lcd.print("COOLING    ");
  }
  else {
    lcd.print("TEMP OK!    ");
  }
}
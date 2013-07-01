/**
* Simple Thermostat Example
*/

#include <LiquidCrystal.h>
#include <Wire.h>
#include <TKLCD.h>
#include <TinkerKit.h>

//TKLCD_Serial lcd = TKLCD_Serial(); // when connecting to TKLCD over Serial
TKLCD_Local lcd = TKLCD_Local(); // when programming a TKLCD module itself
TKPotentiometer pot = TKPotentiometer(A0);


void setup() {
  
  lcd.begin();
  
  lcd.clear();
  
}

void loop() {
  
  int val = pot.read();
  
  
  
  lcd.home();
  lcd.print("Val: ");
  lcd.print(val);
  lcd.print("  ");
  
  lcd.setContrast(val / 4);
  //lcd.setBrightness(val / 4);
  
}
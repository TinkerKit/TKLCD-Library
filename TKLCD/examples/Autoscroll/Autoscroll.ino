 /*
 This sketch demonstrates the use of the autoscroll()
 and noAutoscroll() functions to make new text scroll or not.
 
 based on the Autoscroll example, included
 in the LiquidCrystal Arduino Library
 */
 
#include <Wire.h>
#include <LiquidCrystal.h>
#include <TKLCD.h>

const int EXAMPLES_DELAY = 5000;

//TKLCD_Twi lcd = TKLCD_Twi();
TKLCD_Serial lcd = TKLCD_Serial(); //for Arduino Mega and Mega ADK write
//TKLCD_Serial lcd = TKLCD_Serial(x); where x is the number of the
//serial connector you want to use (x = 1, 2,3 or 4)

/*If you want to modify the address of I2C communication use the function
 lcd.setActiveAddress(NEW_ADDRESS);
 
 Default address is 0x33*/

void setup() {
  lcd.begin();
}

void loop() {
  // set the cursor to (0,0):
  lcd.setCursor(0, 0);
  // print from 0 to 9:
  for (int thisChar = 0; thisChar < 10; thisChar++) {
   lcd.print(thisChar);
   delay(500);
  }

  // set the cursor to (16,1):
  lcd.setCursor(16,1);
  // set the display to automatically scroll:
  lcd.autoscroll();
  // print from 0 to 9:
  for (int thisChar = 0; thisChar < 10; thisChar++) {
    lcd.print(thisChar);
    delay(500);
  }
  // turn off automatic scrolling
  lcd.noAutoscroll();
  
  // clear screen for the next loop:
  lcd.clear();
}


/**
* Demonstrate every feature available in the TKLCD class.
* To be run on an Arduino connected to a TinkerKit LCD module via Serial or TWI.
*/
#include <Wire.h>
#include <LiquidCrystal.h>
#include <TKLCD.h>

const int EXAMPLES_DELAY = 5000;

//TKLCD_Local lcd = TKLCD_Local();
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
  
  lcd.clear();
  
  lcd.print("Simple print");
  delay(EXAMPLES_DELAY);
  
  lcd.clear();
  lcd.print("Cleared that");
  delay(EXAMPLES_DELAY);
  
  lcd.clear();
  lcd.print("Another print");
  delay(EXAMPLES_DELAY);
  lcd.print("Overwrite line 1");
  delay(EXAMPLES_DELAY);
  
  lcd.home();
  lcd.print("New Text line1");
  delay(EXAMPLES_DELAY);
  
  lcd.clear();
  lcd.print("Switching display off");
  delay(EXAMPLES_DELAY);
  lcd.noDisplay();
  delay(EXAMPLES_DELAY);
  lcd.clear();
  lcd.display();
  delay(EXAMPLES_DELAY);
  lcd.print("Display back on");
  delay(EXAMPLES_DELAY);
  
  lcd.clear();
  lcd.print("Testing brightness levels...");
  delay(EXAMPLES_DELAY);
  lcd.setBrightness(0);
  delay(EXAMPLES_DELAY);
  lcd.setBrightness(50);
  delay(EXAMPLES_DELAY);
  lcd.setBrightness(100);
  delay(EXAMPLES_DELAY);
  lcd.setBrightness(150);
  delay(EXAMPLES_DELAY);
  lcd.setBrightness(200);
  delay(EXAMPLES_DELAY);
  lcd.setBrightness(255);
  delay(EXAMPLES_DELAY);
  
  lcd.clear();
  lcd.print("Autoscroll & Cursor pos:");
  delay(EXAMPLES_DELAY);
  lcd.autoscroll();
  lcd.setCursor(0, 0);
  lcd.print("Works?");
  delay(EXAMPLES_DELAY);
  lcd.noAutoscroll();
  
  
  lcd.clear();
  lcd.print("Testing contrast levels...");
  delay(EXAMPLES_DELAY);
  lcd.setContrast(100);
  delay(EXAMPLES_DELAY);
  lcd.setContrast(150);
  delay(EXAMPLES_DELAY);
  lcd.setContrast(200);
  delay(EXAMPLES_DELAY);
  lcd.setContrast(255);
  delay(EXAMPLES_DELAY);
  
  lcd.setContrast(230);
  
  lcd.clear();
  lcd.print("Enabling cursor");
  lcd.cursor();
  delay(EXAMPLES_DELAY);
  lcd.clear();
  lcd.print("Disabling cursor");
  lcd.noCursor();
  delay(EXAMPLES_DELAY);
  
  lcd.clear();
  lcd.print("Enabling blink");
  lcd.blink();
  delay(EXAMPLES_DELAY);
  lcd.clear();
  lcd.print("Disabling blink");
  lcd.noBlink();
  delay(EXAMPLES_DELAY);
  
  lcd.clear();
  lcd.print("Looping again...");
  delay(EXAMPLES_DELAY);
}

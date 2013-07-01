/**
* Demonstrate every feature available in the TKLCD class.
* To be run on an Arduino connected to a TinkerKit LCD module via Serial or TWI.
*/
#include <Wire.h>
#include <LiquidCrystal.h>
#include <TKLCD.h>

const int EXAMPLES_DELAY = 2000;

TKLCD_Local lcd_master = TKLCD_Local();
TKLCD_Twi lcd_slave = TKLCD_Twi();
//TKLCD_Serial lcd_slave = TKLCD_Serial();

/*If you want to modify the address of I2C communication use the function
lcd.setActiveAddress(NEW_ADDRESS);

Default address is 0x33*/

void setup() {
   lcd_master.begin();
   lcd_master.print("TKLCDv0.2");
   lcd_master.setCursor(0,1);
   lcd_master.print("TinkerKit.com");
   delay(6000); //waiting for slave splash screen 
   lcd_slave.begin();
}

void loop() {
  
  lcd_master.clear();
  lcd_slave.clear();
  
  lcd_master.print("Hi Slave");
  delay(EXAMPLES_DELAY);
  lcd_master.clear();
  
  lcd_slave.print("Hi Master");
  delay(EXAMPLES_DELAY);
  lcd_slave.clear();
 
  lcd_master.print("How are you?");
  delay(EXAMPLES_DELAY);
  lcd_master.clear();
  
  lcd_slave.print("Fine thanks..");
  delay(EXAMPLES_DELAY);
  lcd_slave.clear();
  
  lcd_master.print("Ok, Bye!");
  delay(EXAMPLES_DELAY);
  lcd_master.clear();
  
  lcd_slave.print("Bye!");
  delay(EXAMPLES_DELAY);
  lcd_slave.clear();
}

/**
TKLCD.cpp - High level class to print to a TinkerKit LCD module from an 
Arduino via Serial port.

@author Fabio Varesano <fvaresano at yahoo dot it>
modded by
Arturo Guadalupi <arturoguadalupi@gmail.com>
Angelo Scialabba <scialabba.angelo@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.
*/

#include <TKLCD.h>
extern byte MATRIX_I2CADDR;

TKLCD_Serial::TKLCD_Serial() {
  // taken from HardwareSerial.h to discriminate between Arduino UNO/Duemilanove and Leonardo
  #if defined(UBRRH) || defined(UBRR0H) // Arduino UNO
    _ser = &Serial;
  #elif defined(USBCON) // Arduino Leonardo
    _ser = &Serial1;
  #endif
}

#if defined __AVR_ATmega2560__ || __AVR_ATmega1280__
TKLCD_Serial::TKLCD_Serial(int ser_num)
{
  switch (ser_num)
	{
	case 1:
		#if defined(UBRR0H)
		_ser = &Serial;
		#else
			return 0;
		#endif
			break;
			
	case 2:
		#if defined(UBRR1H)
		_ser = &Serial1;
		#else
			return 0;
		#endif
	break;
	
	case 3:
		#if defined(UBRR2H)
		_ser = &Serial2;
		#else
			return 0;
		#endif
	break;
	
	case 4:
		#if defined(UBRR3H)
		_ser = &Serial3;
		#else
			return 0;
		#endif
	}
}
#endif 


void TKLCD_Serial::begin(long speed) {
  _ser->begin(speed);
}

void TKLCD_Serial::clear() {
  command(MATRIX_CLEAR);
}

void TKLCD_Serial::home() {
  command(MATRIX_HOME);
}

void TKLCD_Serial::setCursor(uint8_t col, uint8_t row) {
  command(MATRIX_SETCURSOR_POSITION);
  // following LiquidCristal numbering so we start from 0. But Matrix start from 1 so +1
  write(col+1);
  write(row+1);
}

void TKLCD_Serial::noDisplay() {
  command(MATRIX_DISPLAY_OFF);
}

void TKLCD_Serial::display() {
  command(MATRIX_DISPLAY_ON);
  write((uint8_t) 0x00);
}

void TKLCD_Serial::noBlink() {
  command(MATRIX_BLOCKCURSOR_OFF);
}

void TKLCD_Serial::blink() {
  command(MATRIX_BLOCKCURSOR_ON);
}

void TKLCD_Serial::noCursor() {
  command(MATRIX_UNDERLINECURSOR_OFF);
}

void TKLCD_Serial::cursor() {
  command(MATRIX_UNDERLINECURSOR_ON);
}

/*
void TKLCD_Serial::scrollDisplayLeft() {
  
}

void TKLCD_Serial::scrollDisplayRight() {
  
}

void TKLCD_Serial::leftToRight() {

}

void TKLCD_Serial::rightToLeft() {

}
*/

void TKLCD_Serial::autoscroll() {
  command(MATRIX_AUTOSCROLL_ON);
}

void TKLCD_Serial::noAutoscroll() {
  command(MATRIX_AUTOSCROLL_OFF);
}

/*
void TKLCD_Serial::createChar(uint8_t, uint8_t[]) {
  
}
*/

void TKLCD_Serial::setBrightness(uint8_t brightness) {
  command(MATRIX_SET_BRIGHTNESS);
  write(brightness);
}

void TKLCD_Serial::setContrast(uint8_t contrast) {
  command(MATRIX_SET_CONTRAST);
  write(contrast);
}

void TKLCD_Serial::setSize(uint8_t cols, uint8_t rows) {
  command(EXTENDED_SETSIZE);
  write(cols);
  write(rows);
}


size_t TKLCD_Serial::write(uint8_t var) {
  _ser->write(var);
  return 1; //assume success
}

void TKLCD_Serial::command(uint8_t cmd) {
  write(MATRIX_STARTL_COMMAND);
  write(cmd);
}
  
void TKLCD_Serial::send(uint8_t, uint8_t) {
  
}


// TKLCD_Local


void TKLCD_Local::begin() {
  LiquidCrystal::begin(DEFAULT_SIZE_COL, DEFAULT_SIZE_COL);
  setBrightness(DEFAULT_BRIGHTNESS);
  setContrast(DEFAULT_CONTRAST);
  
  // fixes flickering when using Arduino default PWM frequency of 490Hz,
  // the following line, switches the PWM frequency to 3906.25Hz
  TCCR1B = TCCR1B & 0b11111000 | 0x02;
}

void TKLCD_Local::setBrightness(uint8_t brightness) {
  analogWrite(BACKLIGHT, brightness);
}

void TKLCD_Local::setContrast(uint8_t contrast) {
  analogWrite(CONTRASTPIN, 255-contrast); // contrast is reversed
}


// TKLCD_Twi


TKLCD_Twi::TKLCD_Twi() {
  _twi = &Wire;
  MATRIX_I2CADDR = 0x33;
}

void TKLCD_Twi::begin() {
  _twi->begin();
}

void TKLCD_Twi::setActiveAddress(byte currentAddress)
{
	MATRIX_I2CADDR = currentAddress;
}


void TKLCD_Twi::clear() {
  _twi->beginTransmission(MATRIX_I2CADDR);
  _twi->write(MATRIX_STARTL_COMMAND);
  _twi->write(MATRIX_CLEAR);
  _twi->endTransmission();
}

void TKLCD_Twi::home() {
  _twi->beginTransmission(MATRIX_I2CADDR);
  _twi->write(MATRIX_STARTL_COMMAND);
  _twi->write(MATRIX_HOME);
  _twi->endTransmission();
}

void TKLCD_Twi::setCursor(uint8_t col, uint8_t row) {
  _twi->beginTransmission(MATRIX_I2CADDR);
  _twi->write(MATRIX_STARTL_COMMAND);
  _twi->write(MATRIX_SETCURSOR_POSITION);
    // following LiquidCristal numbering so we start from 0. But Matrix start from 1 so +1
  _twi->write(col+1);
  _twi->write(row+1);
  _twi->endTransmission();

}

void TKLCD_Twi::noDisplay() {

  _twi->beginTransmission(MATRIX_I2CADDR);
  _twi->write(MATRIX_STARTL_COMMAND);
  _twi->write(MATRIX_DISPLAY_OFF);
  _twi->endTransmission();
}

void TKLCD_Twi::display() {
  _twi->beginTransmission(MATRIX_I2CADDR);
  _twi->write(MATRIX_STARTL_COMMAND);
  _twi->write(MATRIX_DISPLAY_ON);
  _twi->endTransmission();
}

void TKLCD_Twi::noBlink() {
  _twi->beginTransmission(MATRIX_I2CADDR);
  _twi->write(MATRIX_STARTL_COMMAND);
  _twi->write(MATRIX_BLOCKCURSOR_OFF);
  _twi->endTransmission();
}

void TKLCD_Twi::blink() {
  _twi->beginTransmission(MATRIX_I2CADDR);
  _twi->write(MATRIX_STARTL_COMMAND);
  _twi->write(MATRIX_BLOCKCURSOR_ON);
  _twi->endTransmission();
}

void TKLCD_Twi::noCursor() {
  _twi->beginTransmission(MATRIX_I2CADDR);
  _twi->write(MATRIX_STARTL_COMMAND);
  _twi->write(MATRIX_UNDERLINECURSOR_OFF);
  _twi->endTransmission();
}

void TKLCD_Twi::cursor() {
  _twi->beginTransmission(MATRIX_I2CADDR);
  _twi->write(MATRIX_STARTL_COMMAND);
  _twi->write(MATRIX_UNDERLINECURSOR_ON);
  _twi->endTransmission();
}

/*
void TKLCD_Twi::scrollDisplayLeft() {
  
}

void TKLCD_Twi::scrollDisplayRight() {
  
}

void TKLCD_Twi::leftToRight() {

}

void TKLCD_Twi::rightToLeft() {

}
*/

void TKLCD_Twi::autoscroll() {
  _twi->beginTransmission(MATRIX_I2CADDR);
  _twi->write(MATRIX_STARTL_COMMAND);
  _twi->write(MATRIX_AUTOSCROLL_ON);
  _twi->endTransmission();
}

void TKLCD_Twi::noAutoscroll() {
  _twi->beginTransmission(MATRIX_I2CADDR);
  _twi->write(MATRIX_STARTL_COMMAND);
  _twi->write(MATRIX_AUTOSCROLL_OFF);
  _twi->endTransmission();
}

/*
void TKLCD_Twi::createChar(uint8_t, uint8_t[]) {
  
}
*/

void TKLCD_Twi::setBrightness(uint8_t brightness) {
  _twi->beginTransmission(MATRIX_I2CADDR);
  _twi->write(MATRIX_STARTL_COMMAND);
  _twi->write(MATRIX_SET_BRIGHTNESS);
   _twi->write(brightness);
  _twi->endTransmission();

}

void TKLCD_Twi::setContrast(uint8_t contrast) {
  _twi->beginTransmission(MATRIX_I2CADDR);
  _twi->write(MATRIX_STARTL_COMMAND);
  _twi->write(MATRIX_SET_CONTRAST);
   _twi->write(contrast);
  _twi->endTransmission();
  }

void TKLCD_Twi::setSize(uint8_t cols, uint8_t rows) {
  _twi->beginTransmission(MATRIX_I2CADDR);
  _twi->write(MATRIX_STARTL_COMMAND);
  _twi->write(EXTENDED_SETSIZE);
   _twi->write(cols);
    _twi->write(rows);
  _twi->endTransmission();
}


size_t TKLCD_Twi::write(uint8_t var) {
  _twi->beginTransmission(MATRIX_I2CADDR);
  _twi->write(var);
  _twi->endTransmission();
  return 1; //assume success
}

/*void TKLCD_Twi::command(uint8_t cmd) {
  write(MATRIX_STARTL_COMMAND);
  write(cmd);
}*/
  
void TKLCD_Twi::send(uint8_t, uint8_t) {
  
}

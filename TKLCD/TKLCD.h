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


#ifndef TKLCD_h
#define TKLCD_h

#include <inttypes.h>
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "Print.h"

#define TKLCD_SERIAL 1
#define TKLCD_LOCAL 2
#define TKLCD_I2C 3

#define DEFAULT_LCD_SERIAL_SPEED 9600

// Redefine Digital outputs as per TKLCD mapping
#define D6 6
#define D5 5
#define D11 11 // yes, we screwed this up

// Define LCD pin mappings
#define LCD_D4  A3
#define LCD_D5  4
#define LCD_D6  12
#define LCD_D7  8
#define LCD_RS  A4
#define LCD_RW  A5
#define LCD_EN  7

// Define default settings
#define DEFAULT_CONTRAST 230
#define DEFAULT_BRIGHTNESS 255
#define DEFAULT_BAUD 9600

// for 16x2 TK display
#define DEFAULT_SIZE_COL 16
#define DEFAULT_SIZE_ROWS 2

// for 8x2 TK display - Use this for smaller version
// #define DEFAULT_SIZE_COL 8
// #define DEFAULT_SIZE_ROWS 2

// connect these to the analog output (PWM) pins!
#define REDLITE 0              // D0
#define GREENLITE 18           // C5
#define BLUELITE 17            // C6
#define BACKLIGHT 10
#define CONTRASTPIN 9         // B7


// commands
#include <matrix_lcd_commands.h>


class TKLCD_Serial : public Print {
public:
  TKLCD_Serial();
  
  TKLCD_Serial(int ser_num);
  
  void begin(long speed = DEFAULT_LCD_SERIAL_SPEED);

  void clear();
  void home();
  void setCursor(uint8_t col, uint8_t row);
  void noDisplay();
  void display();
  void noBlink();
  void blink();
  void noCursor();
  void cursor();
  //void scrollDisplayLeft();
  //void scrollDisplayRight();
  //void leftToRight();
  //void rightToLeft();
  void autoscroll();
  void noAutoscroll();
  
  void setBrightness(uint8_t);
  void setContrast(uint8_t contrast);
  void setSize(uint8_t cols, uint8_t rows);

  //void createChar(uint8_t, uint8_t[]);
  virtual size_t write(uint8_t);
  void command(uint8_t);
  
  using Print::write;
  

  
private:
  void send(uint8_t, uint8_t);
  void write4bits(uint8_t);
  void write8bits(uint8_t);
  HardwareSerial * _ser;

  
};


class TKLCD_Local : public LiquidCrystal {
  public:
    TKLCD_Local() : LiquidCrystal(LCD_RS, LCD_RW, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7){};
    void begin();
    void setBrightness(uint8_t);
    void setContrast(uint8_t contrast);
};


class TKLCD_Twi : public Print {
public:
  
  TKLCD_Twi();
  
  void begin();

  void clear();
  void home();
  void setCursor(uint8_t col, uint8_t row);
  void noDisplay();
  void display();
  void noBlink();
  void blink();
  void noCursor();
  void cursor();
  //void scrollDisplayLeft();
  //void scrollDisplayRight();
  //void leftToRight();
  //void rightToLeft();
  void autoscroll();
  void noAutoscroll();
  
  void setBrightness(uint8_t);
  void setContrast(uint8_t contrast);
  void setSize(uint8_t cols, uint8_t rows);

  //void createChar(uint8_t, uint8_t[]);
  virtual size_t write(uint8_t);
  void command(uint8_t);
  void setActiveAddress(byte currentAddress);
  
  using Print::write;

private:
  byte MATRIX_I2CADDR;
  void send(uint8_t, uint8_t);
  void write4bits(uint8_t);
  void write8bits(uint8_t);
  TwoWire * _twi;
  
};

#endif
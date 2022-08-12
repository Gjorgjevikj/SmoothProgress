/**
 * @file BasicProgress.ino
 * @ingroup examples
 * @brief Basic library usage example
 *
 * This example shows how to display a single horizontal smooth progress bar on a character LCD display.
 */

// Wiring
// For serial (I2C) wiring follow the recommendations for your adapter board
// or for the most common boards you can find a guide at https://create.arduino.cc/projecthub/arduino_uno_guy/i2c-liquid-crystal-displays-5b806c
//
// For parallel (direct I/O control) you can find a guide at https://docs.arduino.cc/learn/electronics/lcd-displays
// The most common wiring (also used here) is:
//  1 - LCD gnd to Arduino GND
//  2 - VCC (5v) to +5V
//  3 - Vo Contrast Voltage (connect to wiper of 10K potentiometer which other contacts are connected to +5V and GND)
//  4 - RS Register Select (rs) to D12
//  5 - Read/Write to GND
//  6 - Enable (en) to D11
//  7 - Data 0 (db0) ----
//  8 - Data 1 (db1)     |-------- Not used in 4 bit mode
//  9 - Data 2 (db2)     |
// 10 - Data 3 (db3) ----
// 11 - Data 4 (db4) to D5
// 12 - Data 5 (db5) to D4
// 13 - Data 6 (db6) to D3
// 14 - Data 7 (db7) to D2
// 15 - Backlight Anode through 220Ohm resistor to +5v
// 16 - Backlight Cathode to GND

// !!! ESP8266 is 3.3V device, while most of the widely available character LCD displays (1602, 2004) are usually for 5V (although such 3.3V displays do exist)
// If your LCD is 3.3V you can connect the signals directly and 3.3V to VDD
// but if your LCD is 5V, for reliable operation you will have to power it by 5V and use a level shifter 

//First include the Liquid Crystal library <LiquidCrystal.h> or <LiquidCrystal_I2C.h>  
//#include <LiquidCrystal_I2C.h> 
#include <LiquidCrystal.h> 

// than include the Smooth progress bars library
#include <SmoothProgress.h>

// SmoothLCDProgressBars supports progress bars in different visual styles
// Each style is stored in separate .h file that should be included next (you have to use at leas one)
// Let's include the style for horizontal progress bar as a square frame with 1 pixel margin
#include <BarStyle1.h>

// Define the lcd object for the display as recommended for the used liquid crystal library
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// The library supports multiple progress bars (up to 4 on a single display), different styles and multiple displays 
// The hardware limitation of these displays implies that all progress bars on a single display have to share the same style
// Next create the association between the lcd display object and the progress bar style 
// as a bar_display (LCD) object (dispA here) to be further used when creating 
// the smooth progress bar object and/or changing the style of the displayed progress bars
LCD dispA(lcd, barStyle1);

// Create the object representing the smooth progress bar to be shown on dispA (lcd)
// defining its size and position on the display
SmoothProgressBar spb(dispA, 10, 5, 0); // progress bar 10 characters wide, at 5-th column, 0-th row 

void setup()
{
    // do the usual lcd initialization for the used liquid crystal library
    lcd.begin(16, 2);

    lcd.print("Smooth progress bar");

    // also initialize the bar_display object (loads the style)
    dispA.begin();

    delay(2000);
}

void loop()
{
    lcd.clear();

    // you can show the progress bar calling showProgressPct and specifying the percentage [0-100] to be filled 
    for (int i = 0; i <= 100; i++)
    {
        lcd.setCursor(0, 0);                  // move cursor to top left
        lcd.print(i);                         // print the string on the display
        lcd.print('%');                       // print the string on the display

        spb.showProgressPct(i);
        delay(25);
    }

    delay(1000);
    lcd.clear();

    // or you can use showProgress method and specifying the number of columns to be filled
    // The length in pixel columns of the progress bar can be found by calling the size() method

    for (int i = spb.size(); i >=0; i--)
    {
        lcd.setCursor(0, 0);                  // move cursor to top left
        lcd.print(i);                         // print the number on the display
        lcd.print(' ');                       // print a character on the display (to overwrite)

        spb.showProgress(i);
        delay(100);
    }
    delay(1000);

    lcd.clear();
    // you can move the progress bar on another position on the display
    // and/or change its size
    if (spb.row() == 0)
    {
        spb.setPosition(spb.col() - 5, 1);
        spb.setLength(spb.getLength() + 5);
    }
    else
    {
        spb.setPosition(spb.col() + 5, 0);
        spb.setLength(spb.getLength() - 5);
    }

}


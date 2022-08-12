/**
 * @file TwoPB_i2c.ino
 * @ingroup examples
 * @brief Shows 2 progress bars on i2c connected LCD
 *
 * This example shows how to display a two horizontal smooth progress bar 
 * on a character LCD display connected through i2c expander board
 */

// Wiring
// For serial (I2C) wiring follow the recommendations for your adapter board
// or for the most common boards you can find a guide at https://create.arduino.cc/projecthub/arduino_uno_guy/i2c-liquid-crystal-displays-5b806c
// The most typical serial wiring for the <LiquidCrystal_I2C.h> would be:
// 
// For Arduino Uno, Nano, Micro:
// Connect SCL to analog 5
// Connect SDA to analog 4
// Connect VDD to 5V DC
// Connect GROUND to common ground
// 
// For ESP8266 (NodeMCU):
// Connect SCL to D1 (GPIO5)
// Connect SDA to D2 (GPIO4)
// Connect VDD to 5V DC (3.3V) DC
// Connect GROUND to common ground
// !!! ESP8266 is 3.3V device, while most of the widely available character LCD displays (1602, 2004) are usually for 5V (although such 3.3V displays do exist)
// If your LCD is 3.3V you can connect the signals directly and 3.3V to VDD
// but if your LCD is 5V, for reliable operation you will have to power it by 5V and also consider using level shifter for the signals


//First include the Liquid Crystal library <LiquidCrystal.h> or <LiquidCrystal_I2C.h>  
#include <LiquidCrystal_I2C.h> 

// than include the Smooth progress bars library
#include <SmoothProgress.h>

// SmoothProgress supports different styles, each stored in separate .h file that should be included next
// Let's include the style for horizontal progress bar as in a square frame with 1 pixel margin
#include <BarStyle1.h>
#include <BarStyle2.h>

// Define the lcd object for the display as usual
LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// The library supports multiple progress bars (up to 4) on a single display, different styles and multiple displays 
// but the hardware limitation of these displays dictates that all progress bars on a single display have to share the same style
// Create the association between the lcd display and the progress bar style 
// as a bar_display (LCD) object dispA to be used when creating the smooth progress bar object
LCD dispA(lcd, barStyle1);

// Create the objects representing the smooth progress bar 
SmoothProgressBar spb1(dispA, 10, 0, 0, 0); // progress bar 10 characters wide, at 0-th row, 0-th column, as progress bar 0
SmoothProgressBar spb2(dispA, 12, 0, 1, 1); // progress bar 12 characters wide, at 1-th row, 0-th column, as progress bar 1

void setup()
{
    // do the usual lcd initialization for the used liquid crystal library
    lcd.init();

    lcd.backlight();                  // enable backlight for the LCD module
    lcd.print("Smooth");
    lcd.setCursor(0, 1);
    lcd.print("Progress");

    // also initialize the bar_display object (loads the style)
    dispA.begin();

    delay(2000);
    lcd.clear();
}

int b1 = 0, b2 = 0;
char buffer[16];

void loop()
{
    sprintf(buffer, "%3d%%", b1);
    lcd.setCursor(12, 0);                       // move cursor to top left
    lcd.print(buffer);                          // print the string on the display
    sprintf(buffer, "%3d%%", b2);
    lcd.setCursor(12, 1);                       // move cursor to top left
    lcd.print(buffer);                          // print the string on the display

    spb1.showProgressPct(b1);
    spb2.showProgressPct(b2);

    b1++;
    b2 += 2;
    if (b1 > 100)
        b1 = 0;
    if (b2 > 100)
    {
        b2 = 0;
        if(&dispA.getStyle() == &barStyle1)
            dispA.setStyle(barStyle2);
        else
            dispA.setStyle(barStyle1);
    }

    delay(50);
}


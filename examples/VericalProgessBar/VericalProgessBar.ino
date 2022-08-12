/**
 * @file VericalProgessBar.ino
 * @ingroup examples
 * @brief Display 2 vertical smooth progress bars on a 20x4 LCD display
 *
 * This example shows how to display a two vertical smooth progress bar on a character LCD display.
 */

 // Wiring
 // For serial (I2C) wiring follow the recommendations for your adapter board
 // or for the most common boards you can find a guide at https://create.arduino.cc/projecthub/arduino_uno_guy/i2c-liquid-crystal-displays-5b806c
 
 //First include the Liquid Crystal library <LiquidCrystal.h> or <LiquidCrystal_I2C.h>  
#include <LiquidCrystal_I2C.h> 
// than include the Smooth progress bars library
#include <SmoothProgress.h>

// SmoothProgress supports different styles, each stored in separate .h file that should be included next
// Let's include the style for horizontal progress bar as in a rounded frame with 1 pixel margin
// To use the program (flash) memory (A.K.A. PROGMEM) for storing the masks that define the style of the progress bar (and save some RAM memory)
// insert #define BAR_STYLE_<#>_IN_PROGMEM before including the corresponding header with the style
// do not forget to use the wrapper when passing the style structure to barstyle constructor
// Include a style for vertical smooth progress bars
#define BAR_STYLES_IN_PROGMEM
#include <BarStyleV2.h>

// Define the lcd object for the display as usual
LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27 for a 20 chars and 4 line display

// The library supports multiple progress bars (up to 4) on a single display, different styles and multiple displays 
// but the hardware limitation of these displays dictates that all progress bars on a single display have to share the same style
// Create the association between the lcd display and the progress bar style 
// as a bar_display (LCD) object dispA to be used when creating the smooth progress bar object
// If the style is stored in PROGMEM use the inPROGMEM wrapper !!!
LCD dispA(lcd, inPROGMEM(barStyleV2));

// Create the object representing the smooth progress bar 
SmoothProgressBar spb1(dispA, 3, 1, 3, 0); // progress bar 3 characters high, at 3-th row, 0-th column, as progress bar 0
SmoothProgressBar spb2(dispA, 4, 19, 3, 1); // progress bar 4 characters high, at 1-th row, 0-th column, as progress bar 1

void setup()
{
    // do the usual lcd initialization for the used liquid crystal library
    lcd.init();

    lcd.backlight();                  // enable backlight for the LCD module
    lcd.print("Vertical ProgressBar");

    // also initialize the bar_display object (loads the style)
    dispA.begin();

    delay(2000);
    lcd.clear();

    lcd.setCursor(5, 0);
    lcd.print("Vertical");
    lcd.setCursor(6, 1);
    lcd.print("Smooth");
    lcd.setCursor(5, 2);
    lcd.print("Progress");
    lcd.setCursor(7, 3);
    lcd.print("Bars");
}

int b1 = 0, b2 = 0;
char buffer[16];         // helper buffer to store C-style strings (generated with sprintf function)

void loop()
{
    sprintf(buffer, "%3d%%", b1);
    lcd.setCursor(0, 0);                       // move cursor to top left
    lcd.print(buffer);                         // print the string on the display
    sprintf(buffer, "%3d%%", b2);
    lcd.setCursor(14, 2);                      // move cursor on the right
    lcd.print(buffer);                         // print the string on the display

    spb1.showProgressPct(b1);
    spb2.showProgressPct(b2);

    b1++;
    b2 += 2;
    if (b1 > 100)
        b1 = 0;
    if (b2 > 100)
        b2 = 0;

    delay(50);
}


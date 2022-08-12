/**
 * @file FourPB.ino
 * @ingroup examples
 * @brief Display 4 horizontal smooth progress bars on a single display
 *
 * This example shows how to display a four horizontal smooth progress bar on a character LCD display.
 */

#include <LiquidCrystal_I2C.h> 
#include <SmoothProgress.h>

// SmoothProgress supports different styles, each stored in separate .h file that should be included next
// Let's include the style for horizontal progress bar as in a square frame with 1 pixel margin
#include <BarStyle2.h>

// Define the lcd object for the display according to the used LCD library
LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// The library supports multiple progress bars (up to 4) on a single display, different styles and multiple displays 
// but the hardware limitation of these displays dictates that all progress bars on a single display have to share the same style
// Create the association between the lcd display and the progress bar style 
// as a bar_display (LCD) object dispA to be used when creating the smooth progress bar object
LCD dispA(lcd, barStyle2);

// Create the objects representing the smooth progress bars (numbered 0 to 3) 
// should not overlap, minimum supported width is 2
SmoothProgressBar spb0(dispA, 10, 0, 0, 0); 
SmoothProgressBar spb1(dispA, 4, 11, 0, 1); 
SmoothProgressBar spb2(dispA, 8, 1, 1, 2); 
SmoothProgressBar spb3(dispA, 6, 10, 1, 3); 

void setup()
{
    lcd.init();   // do the usual lcd initialization for the used liquid crystal library

    lcd.backlight();                  // enable backlight for the LCD module
    lcd.print("4 smooth progress bars");

    // also initialize the bar_display object (loads the style)
    dispA.begin();

    delay(2000);
    lcd.clear();
}

int mc = 0;
int p1 = 0, p2 = 0, p3 = 0, p4 = 0;

void loop()
{
    spb0.showProgressPct(p1);
    spb1.showProgressPct(p2);
    spb2.showProgressPct(p3);
    spb3.showProgressPct(p4);

    p1 = (mc++)%101;
    if (mc % 2 == 0)
        p2++;
    if (mc % 3 == 0)
        p3++;
    if (mc % 5 == 0)
        p4++;

    if (p1 > 100)
        p1 = 0;
    if (p2 > 100)
        p2 = 0;
    if (p3 > 100)
        p3 = 0;
    if (p4 > 100)
        p4 = 0;

    delay(5);
}


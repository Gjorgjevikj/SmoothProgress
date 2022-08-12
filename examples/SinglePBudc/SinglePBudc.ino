/**
 * @file SinglePBudc.ino
 * @ingroup examples
 * @brief Demonstrates the use of remaining user defined characters when using only one progress bar
 *
 * This example shows how to define and display a user defined character together with a progress bar.
 * The smooth progress bars are "drawn" using the user definable characters that are appropriately defined to show the progress.
 * Since these display have only 8 user definable characters, only 4 progress bars can be supported at a time.
 * Each progress bar is "drawn" by printing (in general) 5 different user defined characters:
 *   1. one on the left edge  
 *   2. one in the middle that is completely full (left of the growing edge) 
 *   3. the character representing the growing edge that is partially filled
 *   4. one in the middle that is completely blank (right of the growing edge) 
 *   5. one on the right edge  
 * Except for the character representing the growing edge, the other 4 are common for all progress bars on the display.
 * 4 common + 4 growing edges = 4 independent progress bars at once
 * If only 1 progress bar is in use, 3 user definable characters ca be used for other purposes.
 * Using 2 progress bars will leave you with 2 user definable characters and so on.
 * The codes of the user definable characters are 0-7. The characters with the codes 0-3 are used for the common ones, 
 * and the next ones (4-7) for each of the progress bars in ascending order of the progress bar number. 
 * So if only one progress bar is in use (with id=0), the characters with codes 5,6,and 7 can be used for other purposes.
 */

#include <LiquidCrystal_I2C.h> 
#include <SmoothProgress.h>
// Let's include the style for horizontal progress bar as in a square frame with 1 pixel margin
#include <BarStyle4.h>

// Define the lcd object for the display as usual
LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// The library supports multiple progress bars (up to 4) on a single display, different styles and multiple displays 
// but the hardware limitation of these displays dictates that all progress bars on a single display have to share the same style
// Create the association between the lcd display and the progress bar style 
// as a bar_display (LCD) object dispA to be used when creating the smooth progress bar object
LCD dispA(lcd, barStyle4);

// Create the object representing the smooth progress bar 
SmoothProgressBar spb(dispA, 10, 4, 0); // progress bar 10 characters wide, at 0-th row, 4-th column

void setup()
{
    lcd.init();   // do the usual lcd initialization for the used liquid crystal library

    lcd.backlight();  // enable backlight for the LCD module
    lcd.print("Use defined char");

    // also initialize the bar_display object (loads the style)
    dispA.begin();

    delay(2000);
}

//prepare the data for the user defined characters
// animated moving arrows up
byte image09[8] = { B01010, B10001, B00100, B01010, B10001, B00100, B01010, B10001 };
byte image10[8] = { B10001, B00100, B01010, B10001, B00100, B01010, B10001, B00100 };
byte image11[8] = { B00100, B01010, B10001, B00100, B01010, B10001, B00100, B01010 };
// animated moving arrows down
byte image25[8] = { B01010, B00100, B10001, B01010, B00100, B10001, B01010, B00100 };
byte image26[8] = { B10001, B01010, B00100, B10001, B01010, B00100, B10001, B01010 };
byte image27[8] = { B00100, B10001, B01010, B00100, B10001, B01010, B00100, B10001 };

void loop()
{
    lcd.clear();

    // create the 3 characters
    lcd.createChar(5, image09);
    lcd.createChar(6, image10);
    lcd.createChar(7, image11);

    for (int i = 0; i <= 100; i++)
    {
        lcd.setCursor(15, 0);
        lcd.write(byte(i/5 % 3 + 5)); // display one of the user defined characters

        lcd.setCursor(0, 0);         
        lcd.print(i);                
        lcd.print('%');              

        spb.showProgressPct(i);
        delay(25);
    }

    delay(1000);
    lcd.clear();

    // change the user defined characters to something different
    lcd.createChar(5, image27);
    lcd.createChar(6, image26);
    lcd.createChar(7, image25);

    for (int i = spb.size(); i >=0; i--)
    {
        lcd.setCursor(15, 0);         
        lcd.write(byte(i / 2 % 3 + 5));    // display one of the user defined characters                  

        lcd.setCursor(0, 0);                  
        lcd.print(i);                         
        lcd.print(' ');                       

        spb.showProgress(i);
        delay(100);
    }
    delay(500);
}


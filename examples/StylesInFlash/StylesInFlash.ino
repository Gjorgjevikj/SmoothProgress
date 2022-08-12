/**
 * @file StylesInFlash.ino
 * @ingroup examples
 * @brief Demonstrates how to save memory by storing the styles in the flash memory
 *
 * This example shows how to save memory by storing the styles in the flash memory 
 * and use the styles stored in flash memory (instead of SRAM)
 */

// Wiring
// For serial (I2C) wiring follow the recommendations for your adapter board
// or for the most common boards you can find a guide at https://create.arduino.cc/projecthub/arduino_uno_guy/i2c-liquid-crystal-displays-5b806c

//First include the Liquid Crystal library <LiquidCrystal_I2C.h>  
#include <LiquidCrystal_I2C.h> 

// than include the Smooth progress bars library
#include <SmoothProgress.h>

// SmoothLCDProgressBars supports different styles, each stored in separate .h file that should be included next
// Let's include the style for horizontal progress bar as in a rounded frame with 1 pixel margin
// To use the program (flash) memory (A.K.A. PROGMEM) for storing the masks that define the style of the progress bar (and save some RAM memory)
// insert #define BAR_STYLE_<#>_IN_PROGMEM before including the corresponding header with the style
// do not forget to use the wrapper when passing the style structure to barstyle constructor
#define BAR_STYLE_4_IN_PROGMEM 
#include <BarStyle4.h>

// Define the lcd object for the display as usual
LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// The library supports multiple progress bars (up to 4) on a single display, different styles and multiple displays 
// but the hardware limitation of these displays dictates that all progress bars on a single display have to share the same style
// Create the association between the lcd display and the progress bar style 
// as a bar_display (LCD) object dispA to be used when creating the smooth progress bar object
// If the style is stored in PROGMEM use the inPROGMEM wrapper !!!
LCD dispA(lcd, inPROGMEM(barStyle4));

// Create the object representing the smooth progress bar 
SmoothProgressBar spb1(dispA, 10, 0, 0, 0); // progress bar 10 characters wide, at 0-th row, 0-th column, as progress bar 0
SmoothProgressBar spb2(dispA, 12, 0, 1, 1); // progress bar 12 characters wide, at 1-th row, 0-th column, as progress bar 1

// you can define your own style 
static const PROGMEM struct barstyle
// or use 
// static const struct barstyle
// to store it in SRAM
myBarStyle = { 
    {
        {B00000, B00000, B00001, B00010, B00001, B00000, B00000, B00000},  // leftANDmask
        {B00001, B00010, B00100, B01000, B01000, B00100, B00010, B00001}}, // leftORmask
    {
        {B00000, B00000, B10000, B01000, B10000, B00000, B00000, B00000},  // rightANDmask
        {B10000, B01000, B00100, B00010, B00010, B00100, B01000, B10000}}, // rightORmask
    {
        {B00000, B01010, B10101, B01010, B10101, B01010, B10101, B00000},  // middleANDmask
        {B10101, B00000, B00000, B00000, B00000, B00000, B00000, B10101}}, // middleORmask
    3, // left offset, 
    3, // right offset
    0  // orientation = horizontal
};

void setup()
{
    // do the usual lcd initialization for the used liquid crystal library
    lcd.init();   

    lcd.backlight();              
    lcd.print("Smooth progress bar");

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
    lcd.setCursor(12, 0);                      // move cursor to top left
    lcd.print(buffer);                         // print the string on the display
    sprintf(buffer, "%3d%%", b2);
    lcd.setCursor(12, 1);                      // move cursor to top left
    lcd.print(buffer);                         // print the string on the display

    spb1.showProgressPct(b1);
    spb2.showProgressPct(b2);

    b1++;
    b2+=2;
    if (b1 > 100)
    {
        b1 = 0;
        // you can change the style while the progress bars are running
        if (&dispA.getStyle() == &barStyle4)
            dispA.setStyle(inPROGMEM(myBarStyle));
        else
            dispA.setStyle(inPROGMEM(barStyle4));
    }
    if (b2 > 100)
        b2 = 0;

    delay(50);
}


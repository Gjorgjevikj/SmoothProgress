/**
 * @file BatteryGauge.ino
 * @ingroup examples
 * @brief Four horizontal / vertical battery gauges example using smooth progress bars 
 *
 * This example shows how to display a four horizontal and vertical battery gauges 
 * on a character LCD display using the SmoothProgress library.
 */

 // Wiring : see the comments in the basic.ino example
 
 //First include the Liquid Crystal library <LiquidCrystal.h> or <LiquidCrystal_I2C.h>  
#include <LiquidCrystal_I2C.h> 

// than include the Smooth progress bars library
#include <SmoothProgress.h>

// SmoothProgress supports different styles, each stored in separate .h file that should be included next
// Include the style for basic horizontal battery bar BarStyleBat.h
// To use the flash (program) memory (a.k.a. PROGMEM) for storing the masks that define the style of the progress bar 
// (and save some RAM memory) insert #define BAR_STYLE_<#>_IN_PROGMEM before including the corresponding header with the style
// Do not forget to use the wrapper when passing the style structure to barstyle (LCD) constructor
#define BAR_STYLE_BAT_IN_PROGMEM 
#include <BarStyleBAT.h>
#define BAR_STYLE_BAT_V_IN_PROGMEM 
#include <BarStyleBatV.h>

// Define the lcd object for the display as usual
LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27 for a 20 chars and 4 line display

// The library supports multiple progress bars (up to 4) on a single display, different styles and multiple displays 
// but the hardware limitation of these displays dictates that all progress bars on a single display have to share the same style
// Create the association between the LCD display and the progress bar style 
// as a bar_display (LCD) object dispA to be used when creating the smooth progress bar object
// If the style is stored in flash (program) memory you have to use the inPROGMEM wrapper !!!
LCD dispA(lcd, inPROGMEM(barStyleBat));

// Create the object representing the battery charge
SmoothProgressBar bat[2][4] = {
    {
    SmoothProgressBar(dispA, 6, 0,  0, 0),
    SmoothProgressBar(dispA, 6, 0,  2, 1),
    SmoothProgressBar(dispA, 6, 14, 0, 2),
    SmoothProgressBar(dispA, 6, 14, 2, 3)
},
{
    SmoothProgressBar(dispA, 2, 2,  2, 0),
    SmoothProgressBar(dispA, 2, 7,  2, 1),
    SmoothProgressBar(dispA, 2, 12, 2, 2),
    SmoothProgressBar(dispA, 2, 17, 2, 3)
} };


void setup()
{
    lcd.init();            // do the usual lcd initialization for the used liquid crystal library
    lcd.backlight();       // enable backlight for the LCD module
    lcd.print("4 Batteries");

    dispA.begin();         // also initialize the bar_display object (loads the style)

    delay(2000);
    lcd.clear();
}

char bufferp[16], bufferv[16];  
int val[4];
int style = 0;
unsigned long lastTimeChanged = 0;
const unsigned long ChangeEvery = 5000;

void loop()
{
    // simulate some values
    for (int j = 10; j <= 100; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            val[i] = min(max(j + i * 10, 0), 100);
            bat[style][i].showProgressPct(val[i]);
            sprintf(bufferp, "%3d%%", val[i]);
            dtostrf(3.2 + val[i] / 100.0, 4, 2, bufferv);
            if (style==0)
            {
                lcd.setCursor(6+(i/2)*5-i/2, (i % 2) * 2);  
                lcd.print(bufferp);                          
                lcd.setCursor(1 + (i / 2) * 14, (i % 2) * 2 + 1);
                lcd.print(bufferv);                        
                lcd.print('v');                           
            }
            else
            {
                lcd.setCursor(i * 5 , 0);
                lcd.print(bufferp);                           
                lcd.setCursor(i * 5, 3);
                lcd.print(bufferv);
            }
        }
        delay(20);
        if (millis() - lastTimeChanged > ChangeEvery)
        {
            lastTimeChanged = millis();
            //change the style
            if (style == 0)
            {
                style = 1;
                dispA.setStyle(inPROGMEM(barStyleBatV));
                lcd.clear();
            }
            else
            {
                style = 0;
                dispA.setStyle(inPROGMEM(barStyleBat));
                lcd.clear();
            }
        }
    }
    delay(1000);
}


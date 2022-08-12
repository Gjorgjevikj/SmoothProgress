/**
 * @file VericalProgessBarTemp.ino
 * @ingroup examples
 * @brief 4 vertical temperature
 *
 * 
 */

 
#include <LiquidCrystal_I2C.h> 
#include <SmoothProgress.h>

#define BAR_STYLE_V_T_IN_PROGMEM 
#include <BarStyleVT.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  
LCD dispA(lcd, inPROGMEM(barStyleVT));

// Create the object representing the smooth progress bar 
SmoothProgressBar temp[] = {
    SmoothProgressBar(dispA, 3, 4,  3, 0), 
    SmoothProgressBar(dispA, 3, 9,  3, 1), 
    SmoothProgressBar(dispA, 3, 14, 3, 2), 
    SmoothProgressBar(dispA, 4, 19, 3, 3) 
};

void setup()
{
    lcd.init();
    lcd.backlight();                  
    lcd.print("4 Temperatures");

    dispA.begin();

    delay(2000);
    lcd.clear();
}

float tm = 0.0, phi;
char buffer[16];         
int i, val[4];
const char* title[5] = { "CPU", "GPU", "PSU", "Case" };

void loop()
{
    // simulate some values
    for(i=0, phi = 0; i<4; i++, phi+=M_PI_4)
        val[i] = sin(tm+phi) * 10 + 11;

    val[3] += 5;

    for (i = 0; i < 3; i++)
    {
        temp[i].showProgress(val[i]);
        sprintf(buffer, "%3d\337", val[i]);
        lcd.setCursor(i*5+1, 0);                       // move cursor to top left
        lcd.print(title[i]);                         // print the string on the display
        lcd.setCursor(i * 5, 1);                       // move cursor to top left
        lcd.print(buffer);                         // print the string on the display
    }

    temp[3].showProgress(val[3]);
    sprintf(buffer, "%3d\337", val[3]);
    lcd.setCursor(i * 5, 0);                       // move cursor to top left
    lcd.print(title[3]);                         // print the string on the display
    lcd.setCursor(i * 5, 1);                       // move cursor to top left
    lcd.print(buffer);                         // print the string on the display

    tm += 0.1;
}


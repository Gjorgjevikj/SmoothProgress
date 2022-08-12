/**
 * @file basic.ino
 * @ingroup examples
 * @brief Basic library usage example
 *
 * This example shows how to display multiple smooth progress bar on several LCD displays simultaneously 
 */

// Created:	11.8.2022 23:03:07

// NOTE!!! LiquidCrystal.h and LiquidCrystal_I2C ARE NOT COMPATIBLE 
// with 16x4 LCD displays - having a bug in positioning the cursor on LCDs with this geometry!
// Alternative library that works fine with all LCD displays is hd44780.h

#include <Wire.h>
#include <hd44780.h>                       // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header
#include <hd44780ioClass/hd44780_pinIO.h>

#include <SmoothProgress.h>

// include the styles to be used
#include <BarStyle1.h>
#include <BarStyle2.h>
#include <BarStyle3.h>
#include <BarStyleBAT.h>
#define BAR_STYLES_IN_PROGMEM
#include <BarStyleV2.h>
#include <BarStyleVT.h>
#undef BAR_STYLES_IN_PROGMEM

const barstyle* styleCollection[] = { &barStyle1, &barStyle2, &barStyle3, NULL };

// define the displays
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd0(rs, en, d4, d5, d6, d7); // 16x2
hd44780_pinIO lcd0(rs, en, d4, d5, d6, d7);

hd44780_I2Cexp  lcd1(0x23, 16, 4);  // set the LCD address to 0x23 for a 16 rows by 4 lines display
hd44780_I2Cexp  lcd2(0x27, 20, 4);  // set the LCD address to 0x27 for a 20 rows by 4 lines display

// define the display/style pairing
BarDisplay < hd44780_pinIO > dispA(lcd0, barStyle3);
BarDisplay < hd44780_I2Cexp > dispB(lcd1, inPROGMEM(barStyleVT));
BarDisplay < hd44780_I2Cexp > dispC(lcd2, barStyleBat);

typedef ProgressBar< BarDisplay< hd44780_I2Cexp > > SPB;

// define the progress bar objects
ProgressBar< BarDisplay< hd44780_pinIO > > pba1(dispA,  8, 8, 0, 0);
ProgressBar< BarDisplay< hd44780_pinIO > > pba2(dispA, 10, 1, 1, 1);

SPB temp[] = {
    SPB(dispB, 4, 4,  3, 0),
    SPB(dispB, 4, 9,  3, 1),
    SPB(dispB, 4, 14, 3, 2),
};

SPB bat[] = {
    SPB(dispC, 6, 0,  0, 0),
    SPB(dispC, 6, 0,  2, 1),
    SPB(dispC, 6, 14, 0, 2),
    SPB(dispC, 6, 14, 2, 3)
};

char buffer[16]; // helper buffer to store C-style strings (generated with sprintf function)
const char* title[] = { "CPU", "GPU", "PSU" };

void setup()
{
    Serial.begin(9600);
    delay(100);
    Serial.println("Multi display LCD smooth progress bar DEMO");

    // identify displays..
    lcd0.begin(16, 2);
    lcd0.print("LCD #0");

    //lcd1.init();
    lcd1.begin(16, 4);
    lcd1.backlight();                  
    lcd1.print("LCD #1");

    //lcd2.init();
    lcd2.begin(20, 4);

    lcd2.backlight();                  
    lcd2.print("LCD #2");

    delay(1000);

    dispA.begin();
    dispB.begin();
    dispC.begin();

    lcd0.clear();
    lcd1.clear();
    lcd2.clear();

    delay(200);
}

int mval = 0;

void loop()
{
    int val[4];

    int val1 = mval % (pba1.size() + 1);
    lcd0.setCursor(0, 0);                           
    sprintf(buffer, "val:%3d ", val1);  
    lcd0.print(buffer);                           
    pba1.showProgress(val1);

    int val2 = mval % 101;
    lcd0.setCursor(12, 1);                           
    sprintf(buffer, "%3d%% ", val2);  
    lcd0.print(buffer);
    pba2.showProgressPct(val2);

    if (val2 == 100) // when progress gets to 100%, switch the style 
    {
        const barstyle* nextStyle = NULL;
        for (int i = 0; styleCollection[i]; i++)
        {
            if (&dispA.getStyle() == styleCollection[i])
            {
                nextStyle = styleCollection[i + 1];
                break;
            }
        }
        if (!nextStyle)
            nextStyle = styleCollection[0];
        dispA.setStyle(*nextStyle);
    }

    for (int i = 0; i < 3; i++)
        val[i] = 40 + sin(mval/10.0 + i*M_PI_4) * 30;

    for (int i = 0; i < 3; i++)
    {
        temp[i].showProgress(map(val[i], 10, 70, 3, 28));
        sprintf(buffer, "%3d\337", val[i]);
        lcd1.setCursor(i * 5 + 1, 0);                      
        lcd1.print(title[i]);                         
        lcd1.setCursor(i * 5, 1);                       
        lcd1.print(buffer);                         
    }

    int j = mval % 100 + 1;
    for (int i = 0; i < 4; i++)
    {
        val[i] = min(max(j + i * 10, 0), 100);
        bat[i].showProgressPct(val[i]);
        sprintf(buffer, "%3d%%", val[i]);
        lcd2.setCursor(6 + (i / 2) * 5 - i / 2, (i % 2) * 2);   
        lcd2.print(buffer);                           
        dtostrf(3.2 + val[i] / 100.0, 4, 2, buffer);
        lcd2.setCursor(1 + (i / 2) * 14, (i % 2) * 2 + 1);   
        lcd2.print(buffer);                           
        lcd2.print('v');                           
    }

    mval++;
    delay(100);
}

under developement...

# SmoothProgress

Library for displaying smooth progress bars on the character based LCD displays for Arduino

Uses the user definable characters of the LCD display and can display up to 4 smoot gauges simultaneously. Relies on the LiquidCrystal_I2C.h or LiquidCrystal.h library. It should also work with other libraries for the character LCD displays based on the Hitachi HD44780 or compatible controllers that support write(uint8_t), setCursor(uint8_t, uint8_t) and createChar(uint8_t, uint8_t[]). Just include the LiquidCrystal library **before** including SmoothProgress.h.

![ProgressBar0](https://github.com/Gjorgjevikj/SmoothProgress/blob/main/extras/SmootProgressBar_0_16x2.png) ![ProgressBar1](https://github.com/Gjorgjevikj/SmoothProgress/blob/main/extras/SmootProgressBar_1_16x2.png)

![Battery6](https://github.com/Gjorgjevikj/SmoothProgress/blob/main/extras/BatteryGauge_6_16x2.png) ![Battery7](https://github.com/Gjorgjevikj/SmoothProgress/blob/main/extras/BatteryGauge_7_16x2.png)

![ProgressBar3](https://github.com/Gjorgjevikj/SmoothProgress/blob/main/extras/SmootProgressBar_1_20x4.png) ![Battery8](https://github.com/Gjorgjevikj/SmoothProgress/blob/main/extras/BatteryGauge_7_20x4.png)

The length of the progress bar can be configured as well as the position on the LCD display. The state of the progress bar can be set as a percentage or absolute value (pixels). Supports user defineable styles of the gauges (you should define your own bitmasks). Comes with 3 different (look&feel) progress bar types - just include <BarStyleX.h> and configure the LCDProgressBar object using LCDProgressBar::setStyle(barStyle). The bitmasks can be stored in memory or in flash (PROGMEM) to save space.

Known minorities:
- no checking of the parameters (so the gauges can act unexpectedly if odd values are passed, like negative or very big numbers) for performance reasons.
- the borders drawn with the gauge are considered as part of the gauge (TODO: offsets...) 

So here it is, hopefully someone else can find a use of it (or make a comment).
For explanation on the usage see the comments before the functions and look at the examples.



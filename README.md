final prepartions for release...

# SmoothProgress

Library for displaying smooth progress bars on the character based LCD displays for Arduino

Library for displaying horizontal or vertical progress bar on a character based LCD like Hitachi HD44780 16x2 or 20x4
Relies on the LiquidCrystal.h or LiquidCrystal_I2C.h library (and should work on any platform that supports this library or similar).
Uses the user definable characters of the LCD display and can display up to 4 smooth progress bars simultaneously.
Supports horizontal and vertical progress bars. 
Supports different visual styles for the progress bars (distributed with the library as separate .h files or user defined)
The bit-mask data for the styles in struct bar style (49 bytes) can be stored in RAM or in PROGMEM
Supports progress bars on multiple connected LCD displays - each display with possibly different progress bar style, 4 progress bars per display

Uses the user definable characters of the LCD display and can display up to 4 smoot gauges simultaneously. Relies on the LiquidCrystal_I2C.h or LiquidCrystal.h library. It should also work with other libraries for the character LCD displays based on the Hitachi HD44780 or compatible controllers that support write(uint8_t), setCursor(uint8_t, uint8_t) and createChar(uint8_t, uint8_t[]). Just include the LiquidCrystal library **before** including SmoothProgress.h.

![ProgressBar0](https://github.com/Gjorgjevikj/SmoothProgress/blob/main/extras/SmootProgressBar_0_16x2.png) ![ProgressBar1](https://github.com/Gjorgjevikj/SmoothProgress/blob/main/extras/SmootProgressBar_1_16x2.png)

![Battery6](https://github.com/Gjorgjevikj/SmoothProgress/blob/main/extras/BatteryGauge_6_16x2.png) ![Battery7](https://github.com/Gjorgjevikj/SmoothProgress/blob/main/extras/BatteryGauge_7_16x2.png)

![ProgressBar3](https://github.com/Gjorgjevikj/SmoothProgress/blob/main/extras/SmootProgressBar_1_20x4.png) ![Battery8](https://github.com/Gjorgjevikj/SmoothProgress/blob/main/extras/BatteryGauge_7_20x4.png)

The length of the progress bar can be configured as well as the position on the LCD display. The state of the progress bar can be set as a percentage or absolute value (pixels). Supports user defineable visual styles for the progress bars. Comes with collection of several different progress bar styles - just include the appropriate header file <BarStyleXX.h> and configure the BarDisplay object. The bitmasks can be stored in memory or in flash (PROGMEM) to save space.

Known limitations:
 - at most 4 independent progress bars can be shown (restricted by the limitation of only 8 user definable characters on these displays)
 - all progress bars on the LCD share the same style (due to hardware limitations of only 8 user definable characters on these displays)
 - the progress bars are "drawn" by printing over all the characters defining the progress bar on every call of showProgress

So here it is, hopefully someone else can find a use of it (or make a comment).
Until a better guide is written...
For explanation on the usage:
- see the examples 
- see the comments before the functions
- see the docs in docs/html/index.html



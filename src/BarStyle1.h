#ifndef BAR_STYLE_1
#define BAR_STYLE_1

// Contains the bit masks defining a style for a smooth progress bar 
// to be used with SmoothProgress library
// https://github.com/Gjorgjevikj/SmoothProgress.git
// 
// smooth progressbar in square frame
// 1 pixel frame, 1 pixel margine to frame, square edges

#include <barstyle.h>

#ifdef BAR_STYLE_1_IN_PROGMEM
static const PROGMEM struct barstyle
#else
static const struct barstyle
#endif

barStyle1 = {
    {
        { // leftANDmask  
            0b00000,
            0b00000,
            0b00111,
            0b00111,
            0b00111,
            0b00111,
            0b00000,
            0b00000},
        { // leftORmask  
            0b11111,
            0b10000,
            0b10000,
            0b10000,
            0b10000,
            0b10000,
            0b10000,
            0b11111}
    },
    {
        { // rightANDmask
            0b00000,
            0b00000,
            0b11100,
            0b11100,
            0b11100,
            0b11100,
            0b00000,
            0b00000},
        { // rightORmask
            0b11111,
            0b00001,
            0b00001,
            0b00001,
            0b00001,
            0b00001,
            0b00001,
            0b11111}
    },
    {
        { // middleANDmask
            0b00000,
            0b00000,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b00000,
            0b00000},
        { // middleORmask
            0b11111,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b11111}
    },
    2, // LeftOffset
    2, // RightOffset
    0 // direction...
};


#endif // BAR_STYLE_1

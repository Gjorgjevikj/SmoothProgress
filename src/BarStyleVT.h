#ifndef BAR_STYLE_V_T
#define BAR_STYLE_V_T

// Contains the bit masks defining a style for a smooth progress bar 
// to be used with SmoothProgress library
// https://github.com/Gjorgjevikj/SmoothProgress.git
// 
// Defines a vertical smooth progress bar for temperature gauge
// 1 pixel frame, 1 pixel margin to frame, rounded edges

#include <barstyle.h>

#ifdef BAR_STYLE_V_T_IN_PROGMEM
static const PROGMEM struct barstyle
#else
static const struct barstyle
#endif

barStyleVT = {
    {
        { // bottomANDmask  
            0b00100,
            0b00100,
            0b00100,
            0b00100,
            0b01110,
            0b01110,
            0b01110,
            0b00000},
        { // bottomORmask  
            0b01010, 
            0b01010, 
            0b01010, 
            0b01010, 
            0b10001, 
            0b10001, 
            0b10001, 
            0b01110}
    },
    {
        { // topANDmask
            0b00000,
            0b00100,
            0b00100,
            0b00100,
            0b00100,
            0b00100,
            0b00100,
            0b00100},
        { // topORmask
            0b00100,
            0b01010,
            0b01010,
            0b01010,
            0b01010,
            0b01010,
            0b01010,
            0b01010}
    },
    {
        { // middleANDmask
            0b00100,
            0b00100,
            0b00100,
            0b00100,
            0b00100,
            0b00100,
            0b00100,
            0b00100},
        { // middleORmask
            0b01010,
            0b01010,
            0b01010,
            0b01010,
            0b01010,
            0b01010,
            0b01010,
            0b01010}
    },
    1, // BottomOffset
    1, // TopOffset
    1  // orientation...
};


#endif // BAR_STYLE_V_T

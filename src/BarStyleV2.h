#ifndef BAR_STYLE_V_2
#define BAR_STYLE_V_2

// Contains the bit masks defining a style for a smooth progress bar 
// to be used with SmoothLCDProgressBars library
// https://github.com/Gjorgjevikj/SmoothLCDProgressBars.git
// 
// Defines a vertical smooth progress bar in square frame
// 1 pixel frame, 1 pixel margin to frame, rounded edges

#include <barstyle.h>

#ifdef BAR_STYLE_V_2_IN_PROGMEM
static const PROGMEM struct barstyle
#else
static const struct barstyle
#endif

barStyleV2 = {
    {
        { // bottomANDmask  
            0b01110,
            0b01110,
            0b01110,
            0b01110,
            0b01110,
            0b01110,
            0b01110,
            0b00000},
        { // bottomORmask  
            0b10001,
            0b10001,
            0b10001,
            0b10001,
            0b10001,
            0b10001,
            0b10001,
            0b01110}
    },
    {
        { // topANDmask
            0b00000,
            0b01110,
            0b01110,
            0b01110,
            0b01110,
            0b01110,
            0b01110,
            0b01110},
        { // topORmask
            0b01110,
            0b10001,
            0b10001,
            0b10001,
            0b10001,
            0b10001,
            0b10001,
            0b10001}
    },
    {
        { // middleANDmask
            0b01110,
            0b01110,
            0b01110,
            0b01110,
            0b01110,
            0b01110,
            0b01110,
            0b01110},
        { // middleORmask
            0b10001,
            0b10001,
            0b10001,
            0b10001,
            0b10001,
            0b10001,
            0b10001,
            0b10001}
    },
    1, // BottomOffset
    1, // TopOffset
    1  // orientation...
};


#endif // BAR_STYLE_V_2

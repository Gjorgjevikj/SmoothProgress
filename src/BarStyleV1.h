#ifndef BAR_STYLE_V_1
#define BAR_STYLE_V_1

// Contains the bit masks defining a style for a smooth progress bar 
// to be used with SmoothProgress library
// https://github.com/Gjorgjevikj/SmoothProgress.git
// 
// Defines a vertical smooth progress bar in square frame
// 1 pixel frame, 1 pixel margin to frame, square edges

#include <barstyle.h>

#ifdef BAR_STYLE_V_1_IN_PROGMEM
static const PROGMEM struct barstyle
#else
static const struct barstyle
#endif

barStyleV1 = {
    {
        { // bottomANDmask  
            0b00100,
            0b00100,
            0b00100,
            0b00100,
            0b00100,
            0b00100,
            0b00000,
            0b00000},
        { // bottomORmask  
            0b10001,
            0b10001,
            0b10001,
            0b10001,
            0b10001,
            0b10001,
            0b10001,
            0b11111}
    },
    {
        { // topANDmask
            0b00000,
            0b00000,
            0b00100,
            0b00100,
            0b00100,
            0b00100,
            0b00100,
            0b00100},
        { // topORmask
            0b11111,
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
            0b00100,
            0b00100,
            0b00100,
            0b00100,
            0b00100,
            0b00100,
            0b00100,
            0b00100},
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
    2, // BottomOffset
    2, // TopOffset
    1  // orientation...
};


#endif // BAR_STYLE_V_1

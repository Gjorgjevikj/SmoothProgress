#ifndef BAR_STYLE_V_0
#define BAR_STYLE_V_0

// Contains the bit masks defining a style for a smooth progress bar 
// to be used with SmoothProgress library
// https://github.com/Gjorgjevikj/SmoothProgress.git
// 
// Defines a vertical PLAIN smooth progress bar
// No frame, full height, square edges, plain

#include <barstyle.h>

#if (defined BAR_STYLE_V_0_IN_PROGMEM) || (defined BAR_STYLES_IN_PROGMEM)
static const PROGMEM struct barstyle
#else
static const struct barstyle
#endif

barStyleV0 = {
    {
        { // bottomANDmask  
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111},
        { // bottomORmask  
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000}
    },
    {
        { // topANDmask
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111},
        { // topORmask
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000}
    },
    {
        { // middleANDmask
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111},
        { // middleORmask
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000}
    },
    0, // LeftOffset
    0, // RightOffset
    1  // orientation...
};

#endif // !BAR_STYLE_V_0

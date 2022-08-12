#ifndef BAR_STYLE_0
#define BAR_STYLE_0

// Contains the bit masks defining a style for a smooth progress bar 
// to be used with SmoothProgress library
// https://github.com/Gjorgjevikj/SmoothProgress.git
// 
// Defines a horizontal PLAIN smooth progress bar
// No frame, full height, square edges, plain

#include <barstyle.h>

#ifdef BAR_STYLE_0_IN_PROGMEM
static const PROGMEM struct barstyle 
#else
static const struct barstyle
#endif

barStyle0 = {
    {
        { // leftANDmask  
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111},
        { // leftORmask  
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
        { // rightANDmask
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111},
        { // rightORmask
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
    0  // orientation...
};

#endif // !BAR_STYLE_0

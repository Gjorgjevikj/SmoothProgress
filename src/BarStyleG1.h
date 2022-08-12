#ifndef BAR_STYLE_G_1
#define BAR_STYLE_G_1

// Contains the bit masks defining a style for a smooth progress bar 
// to be used with SmoothProgress library
// https://github.com/Gjorgjevikj/SmoothProgress.git
// 
// Defines a horizontal smooth gauge line
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
            0b00000,
            0b00000,
            0b01111,
            0b01111,
            0b01111,
            0b01111,
            0b01111,
            0b00000},
        { // leftORmask  
            0b00000,
            0b00000,
            0b00000,
            0b10000,
            0b11111,
            0b10000,
            0b00000,
            0b00000}
    },
    {
        { // rightANDmask
            0b00000,
            0b00000,
            0b11110,
            0b11110,
            0b11110,
            0b11110,
            0b11110,
            0b00000},
        { // rightORmask
            0b00000,
            0b00000,
            0b00000,
            0b00001,
            0b11111,
            0b00001,
            0b00000,
            0b00000}
    },
    {
        { // middleANDmask
            0b00000,
            0b00000,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b00000},
        { // middleORmask
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b11111,
            0b00000,
            0b00000,
            0b00000}
    },
    1, // LeftOffset
    1, // RightOffset
    2  // orientation...
};

#endif // !BAR_STYLE_G_1

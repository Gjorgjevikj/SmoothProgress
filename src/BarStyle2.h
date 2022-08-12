#ifndef BAR_STYLE_2
#define BAR_STYLE_2

// Contains the bit masks defining a style for a smooth progress bar 
// to be used with SmoothLCDProgressBars library
// https://github.com/Gjorgjevikj/SmoothLCDProgressBars.git
// 
// Defines a horizontal PLAIN smooth progress bar
// no frame, no margin, rounded edges

#include <barstyle.h>

#ifdef BAR_STYLE_2_IN_PROGMEM
static const PROGMEM struct barstyle
#else
static const struct barstyle
#endif

barStyle2 = {
    {
        { // leftANDmask
            0b01111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b01111},
        { // leftORmask
            0b01111,
            0b10000,
            0b10000,
            0b10000,
            0b10000,
            0b10000,
            0b10000,
            0b01111 }
    },
    {
        { // rightANDmask
            0b11110,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11110 },
        { // rightORmask
            0b11110,
            0b00001,
            0b00001,
            0b00001,
            0b00001,
            0b00001,
            0b00001,
            0b11110 }
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
            0b11111 },
        { // middleORmask
            0b11111,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b11111 }
    },
    1, // left offset
    1, // right offset
    0  // orientation
};

#endif // !BAR_STYLE_2

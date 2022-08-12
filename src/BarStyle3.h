#ifndef BAR_STYLE_3
#define BAR_STYLE_3

// Contains the bit masks defining a style for a smooth progress bar 
// to be used with SmoothProgress library
// https://github.com/Gjorgjevikj/SmoothProgress.git
// 
// Defines a smooth horizontal progress bar rounded style no frame
// 1 pixel frame, no margin (full height), more rounded edges

#include <barstyle.h>

#ifdef BAR_STYLE_3_IN_PROGMEM
static const PROGMEM struct barstyle
#else
static const struct barstyle
#endif

barStyle3 = {
    {
        { // leftANDmask
            0b00111,
            0b01111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b01111,
            0b00111},
        { // leftORmask
            0b00111,
            0b01000,
            0b10000,
            0b10000,
            0b10000,
            0b10000,
            0b01000,
            0b00111 }
    },
    {
        { // rightANDmask
            0b11100,
            0b11110,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11110,
            0b11100},
        { // rightORmask
            0b11100,
            0b00010,
            0b00001,
            0b00001,
            0b00001,
            0b00001,
            0b00010,
            0b11100}
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
            0b11111,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b11111}
    },
    1, // left offset, 
    1, // right offset
    0  // orientation
};

#endif // !BAR_STYLE_3

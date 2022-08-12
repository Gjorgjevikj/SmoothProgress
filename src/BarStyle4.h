#ifndef BAR_STYLE_4
#define BAR_STYLE_4

// Contains the bit masks defining a style for a smooth progress bar 
// to be used with SmoothProgress library
// https://github.com/Gjorgjevikj/SmoothProgress.git
// 
// Defines a smooth horizontal progress bar rounded style no frame
// 1 pixel frame, no margin (full height), more rounded edges

#include <barstyle.h>

#ifdef BAR_STYLE_4_IN_PROGMEM
static const PROGMEM struct barstyle
#else
static const struct barstyle
#endif

barStyle4 = {
    {
        { // leftANDmask
            0b00000,
            0b00000,
            0b00011,
            0b00111,
            0b00111,
            0b00011,
            0b00000,
            0b00000},
        { // leftORmask
            0b00111,
            0b01000,
            0b10000,
            0b10000,
            0b10000,
            0b10000,
            0b01000,
            0b00111}
    },
    {
        { // rightANDmask
            0b00000,
            0b00000,
            0b11000,
            0b11100,
            0b11100,
            0b11000,
            0b00000,
            0b00000},
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
    2, // left offset, 
    2, // right offset
    0  // orientation
};

#endif // !BAR_STYLE_4

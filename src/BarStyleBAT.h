#ifndef BAR_STYLE_BAT
#define BAR_STYLE_BAT

// Contains the bit masks defining a style for a smooth progress bar 
// to be used with SmoothProgress library
// https://github.com/Gjorgjevikj/SmoothProgress.git
// 
// Defines a smooth horizontal progress bar representing a battery
// 1 pixel frame, 1 pixel margin, 5 pixel offsets 

#include <barstyle.h>

#ifdef BAR_STYLE_BAT_IN_PROGMEM
static const PROGMEM struct barstyle
#else
static const struct barstyle
#endif

barStyleBat = {
    {
        { // lANDmask  
            0b00001,
            0b00001,
            0b00001,
            0b00001,
            0b00001,
            0b00001,
            0b00001,
            0b00001},
        { // leftORmask  
            0b00001,
            0b00001,
            0b00001,
            0b00001,
            0b00001,
            0b00001,
            0b00001,
            0b00001},
    },
    {
        { // rightANDmask
            0b10000,
            0b10000,
            0b11100,
            0b11100,
            0b11100,
            0b11100,
            0b10000,
            0b10000},
        { // rightORmask
            0b10000,
            0b10000,
            0b11100,
            0b11100,
            0b11100,
            0b11100,
            0b10000,
            0b10000},
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
            0b11111},
    },
    5, // LeftOffset
    5, // RightOffset
    0  // direction...
};


#endif // !BAR_STYLE_BAT

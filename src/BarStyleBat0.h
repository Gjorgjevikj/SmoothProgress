#ifndef BAR_STYLE_BAT0
#define BAR_STYLE_BAT0

// Contains the bit masks defining a style for a smooth progress bar 
// to be used with SmoothProgress library
// https://github.com/Gjorgjevikj/SmoothProgress.git
// 
// Defines a smooth horizontal progress bar representing a battery
// 1 pixel frame, 1 pixel margin, 2 pixel offsets 

#include <barstyle.h>

#if (defined BAR_STYLE_BAT0_IN_PROGMEM) || (defined BAR_STYLES_IN_PROGMEM)
static const PROGMEM struct barstyle
#else
static const struct barstyle
#endif

barStyleBat0 = {
    {
        { // lANDmask  
            0b00000,
            0b00000,
            0b00111,
            0b00111,
            0b00111,
            0b00111,
            0b00000,
            0b00000},
        { // leftORmask  
            0b11111,
            0b10000,
            0b10000,
            0b10000,
            0b10000,
            0b10000,
            0b10000,
            0b11111},
    },
    {
        { // rightANDmask
            0b00000,
            0b00000,
            0b10000,
            0b10000,
            0b10000,
            0b10000,
            0b00000,
            0b00000},
        { // rightORmask
            0b11100,
            0b00100,
            0b00111,
            0b00111,
            0b00111,
            0b00111,
            0b00100,
            0b11100},
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
    2, // LeftOffset
    4, // RightOffset
    0  // direction...
};


#endif // !BAR_STYLE_BAT0

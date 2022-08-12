#ifndef BAR_STYLE_SS
#define BAR_STYLE_SS

// Contains the bit masks defining a style for a smooth progress bar 
// to be used with SmoothProgress library
// https://github.com/Gjorgjevikj/SmoothProgress.git
// 
// Defines a smooth horizontal progress bar representing a signal strength 
// for fixed 3 characters length no frame, no margin, no offsets 

#include <barstyle.h>

#if (defined BAR_STYLE_SS_IN_PROGMEM) || (defined BAR_STYLES_IN_PROGMEM)
static const PROGMEM struct barstyle
#else
static const struct barstyle
#endif

barStyleSS = {
    {
        { // leftANDmask  
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00011,
            0b01111,
            0b11111},
        { // leftORmask  
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000},
    },
    {
        { // rightANDmask
            0b00011,
            0b01111,
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
            0b00000},
    },
    {
        { // middleANDmask
            0b00000,
            0b00000,
            0b00001,
            0b00111,
            0b11111,
            0b11111,
            0b11111,
            0b11111},
        { // mORmask
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000},
    },
    0, // BootmOffset
    0, // TopOffset
    0  // direction...
};

#endif // !BAR_STYLE_SS

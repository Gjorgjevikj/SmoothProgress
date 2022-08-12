#ifndef BAR_STYLE_BAT_V
#define BAR_STYLE_BAT_V

// Contains the bit masks defining a style for a smooth progress bar 
// to be used with SmoothProgress library
// https://github.com/Gjorgjevikj/SmoothProgress.git
// 
// Defines a smooth vertical progress bar representing a battery
// 1 pixel frame, no margin, 1 pixel offsets 

#include <barstyle.h>

#ifdef BAR_STYLE_BAT_V_IN_PROGMEM
static const PROGMEM struct barstyle
#else
static const struct barstyle
#endif

barStyleBatV = {
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
            0b01110,
            0b01110,
            0b01110,
            0b01110,
            0b01110,
            0b01110},
        { // topORmask
            0b01110,
            0b11111,
            0b10001,
            0b10001,
            0b10001,
            0b10001,
            0b10001,
            0b10001}
    },
    {
        { // middleANDmask
            0b01110,
            0b01110,
            0b01110,
            0b01110,
            0b01110,
            0b01110,
            0b01110,
            0b01110},
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
    1, // BootmOffset
    2, // TopOffset
    1  // direction...
};


#endif // !BAR_STYLE_BAT_V

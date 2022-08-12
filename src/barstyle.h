#ifndef BAR_STYLE_STRUCT
#define BAR_STYLE_STRUCT

// Part of the SmoothLCDProgressBars library for Arduino
// Defines a structure containing bit-masks defining a style for a smooth progress bar 
// to be used with SmoothLCDProgressBars library
// https://github.com/Gjorgjevikj/SmoothLCDProgressBars.git

// some utility functions ...
// creates bit-mask with N LSB bits set to 1 
template <uint8_t N>
constexpr uint8_t MaskLSBs()
{
    return MaskLSBs<N - 1>() << 1 | 1;
}

template <>
constexpr uint8_t MaskLSBs<0>()
{
    return 0;
}

template <>
constexpr uint8_t MaskLSBs<1>()
{
    return 1;
}

/// <summary>
/// Structure holding the bit-masks and other data used for drawing the edges of the progress bar that define the appearance (style) of the progress bar
/// startMask[2][CharPatRows] - AND and OR mask for the first (beginning) character of the progress bar
/// endMask[2][CharPatRows] - AND and OR mask for the last (ending) character of the progress bar
/// middleMask[2][CharPatRows] - AND and OR mask for the advancing (partially filled) character of the progress bar
/// the AND mask defines which pixels to be left on when filling the progress bar (and which should always be off - defining the margin to the frame)
/// the OR mask defines which pixels will always be on - defining the frame of the progress bar
/// startOffset - defines where the filling of the progress bar actually starts (regarding the frame and the margin of the style)
/// endOffset - defines where the filling of the progress bar ends (regarding the frame and the margin of the style)
/// </summary>
struct barstyle
{
    enum dotMatrixDim : byte { CharPatRows = 8, CharPatCols = 5 };
    enum bitMasks : byte { AllRows = MaskLSBs<CharPatRows>(), AllCols = MaskLSBs<CharPatCols>() };
    enum andOrMaskIndex : byte { ANDmask, ORmask };
    enum orientation : byte { Horizontal, Vertical }; // Progress bar orientation 
    uint8_t startMask[2][CharPatRows];  // Left/Bottom-AND+OR mask
    uint8_t endMask[2][CharPatRows];    // Right/Top-AND+OR mask
    uint8_t middleMask[2][CharPatRows]; // Middle-AND+OR mask
    struct bspar // where the filling of the progress bar actually starts/ends considering that some pixels are taken for the frame
    {
        unsigned char startOffset : 3;
        unsigned char endOffset : 3;
        unsigned char dir : 2; //  used for orientation (possibly direction ...)
    } stylePar;
};

// character creator - https://tusindfryd.github.io/screenduino/
// another character creator - https://maxpromer.github.io/LCD-Character-Creator/


#endif //BAR_STYLE_STRUCT
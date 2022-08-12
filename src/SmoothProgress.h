/**
  SmoothProgress library v 1.0.0
  Name: SmoothProgress
  Purpose: Draws up to 4 independent smooth progress bars on the character based LCD displays for Arduino

  @author Dejan Gjorgjevikj
  @version 1.0.0, 8/2022

Smooth LCD progress bar for the character based LCD displays for Arduino
Library for displaying horizontal or vertical progress bar on a character based LCD like Hitachi HD44780 16x2 or 20x4
Relies on the LiquidCrystal.h or LiquidCrystal_I2C.h library (and should work on any platform that supports this library or similar).
Uses the user definable characters of the LCD display and can display up to 4 smooth progress bars simultaneously.
Supports horizontal and vertical progress bars. 
Supports different visual styles for the progress bars (distributed with the library as separate .h files or user defined)
The bit-mask data for the styles in struct bar style (49 bytes) can be stored in RAM or in PROGMEM
Supports progress bars on multiple connected LCD displays - each display with possibly different progress bar style, 4 progress bars per display

Known limitations:
 - at most 4 independent progress bars can be shown (restricted by the limitation of only 8 user definable characters on these displays)
 - all progress bars on the LCD share the same style (due to hardware limitations of only 8 user definable characters on these displays)
 - the progress bars are "drawn" by printing over all the characters defining the progress bar on every call of showProgress

This library is distributed in the hope that it will be useful, but
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE either express or implied.
Released into the public domain.
Distributed under: GPL 3.0 License

https://github.com/Gjorgjevikj/SmoothProgress.git

*/

#ifndef SMOOTH_PROGRESS_H
#define SMOOTH_PROGRESS_H

#define SMOOTH_PROGRESS_VER 1.0.0

#include <barstyle.h>

//try to determine the LCD library included
#if defined(LiquidCrystal_I2C_h) 
#define LCD_OBJ LiquidCrystal_I2C
//#if defined(hd44780_h) 
#elif defined(hd44780_I2Cexp_h)
#define LCD_OBJ hd44780_I2Cexp
#elif defined(hd44780_HC1627_I2C_h)
#define LCD_OBJ hd44780_HC1627_I2C
#elif defined(hd44780_I2Clcd_h)
#define LCD_OBJ hd44780_I2Clcd 
#elif defined(FDB_LIQUID_CRYSTAL_I2C_H)
#define LCD_OBJ LiquidCrystal_I2C
#elif defined(LiquidCrystal_h)
#define LCD_OBJ LiquidCrystal
#else
#define LCD_OBJ ERROR_NO_LCD_OBJ
#error "No supported LiquidCrystal library included. Please check that the LiquidCrystal library is included BEFORE SmoothProgress.h"
#endif

// constants to specify where there the data for the progress bar style (bit-masks) are stored in memory (SRAM) or in flash (PROGMEM)
enum MemoryType { RAM = 0, FLASH = 1, DATA = 0, PROG = 1 };

class __FlashBarStyleHelper;
#define FBS(style) (reinterpret_cast<const __FlashBarStyleHelper *>(style))

/// <summary>
/// Helper class to wrap the barstyle structure when passing the structure "object" to a function
/// so that a distinction can be made where it is stored in RAM or in FLASH
/// if the progress bar style holding the bitmasks is defined to be stored in FLASH
/// using static const PROGMEM struct barstyle styleName = ...
/// wrap it up with inPROGMEM when passing it as an argument (as const reference) to the functions / constructors
/// </summary>
class inPROGMEM
{
public:
    /// <summary>
    /// Wrapper to be used when passing the barstyle structure (as const reference) to the functions / constructors
    /// </summary>
    /// <param name="bs">const reference to the structure ("object") stored in FLASH (PROGMEM) holding the style definition</param>
    /// <seealso cref="struct barstyle"/>
    inPROGMEM(const barstyle& bs) : bsp(&bs) {}
    inline const barstyle* unwrap() const { return bsp; }
private:
    const barstyle* bsp;
};

template <class DISP = LCD_OBJ>
class BarDisplay
{
public:
    // constants defining which character positions for the user definable characters will be used for what purpose when drawing the progress bar
    enum UDCharCode : byte { ProgBarCharBlank = 0, ProgBarCharFull, ProgBarCharBegin, ProgBarCharEnd, ProgBarCharPartial };

    /// <summary>
    /// BarDisplay constructor
    /// creates the object that bounds the LCD display to the bar style defined in the barstyle struct
    /// the style is common for all progress bars on that display (hardware limitations of the LCD displays that have only 8 user definable characters)
    /// </summary>
    /// <param name="displ">the object (as created by the LiquidCrystal library) used to access the particular LCD display</param>
    /// <param name="bs">the structure defining the masks for the progress bar style stored in RAM</param>
    BarDisplay(DISP& displ, const barstyle& bs) : disp(displ), barStyle(&bs), styleMemPlacement(RAM) { }

    /// <summary>
    /// BarDisplay constructor
    /// creates the object that bounds the LCD display to the bar style defined in the barstyle struct
    /// the style is common for all progress bars on that display (hardware limitations of the LCD displays that have only 8 user definable characters)
    /// </summary>
    /// <param name="displ">the object (as created by the LiquidCrystal library) used to access the LCD display</param>
    /// <param name="wraped">inPROGMEM wrapper object for the structure defining the masks for the progress bar style stored in FLASH</param>
    BarDisplay(DISP& displ, const inPROGMEM& wraped) : disp(displ), barStyle(wraped.unwrap()), styleMemPlacement(FLASH) { }

    BarDisplay(DISP& displ, const barstyle* bsp) : disp(displ), barStyle(bsp), styleMemPlacement(RAM) { }
    BarDisplay(DISP& displ, const __FlashBarStyleHelper* bspf) : disp(displ), barStyle(bspf), styleMemPlacement(FLASH) { }

    BarDisplay(const BarDisplay&) = delete;
    BarDisplay& operator=(const BarDisplay&) = delete;

    /// <summary>
    /// Access to the display object for low level functions of the LCD
    /// </summary>
    /// <returns>a pointer to the LCD display object</returns>
    inline DISP & dsplay() const
    {
        return disp;
    }

    /// <summary>
    /// Access to the bar style structure 
    /// </summary>
    /// <returns>reference to barstyle structure defining the style of the progress bars on the display</returns>
    inline const barstyle& getStyle() const
    {
        return *barStyle;
    }

    /// <summary>
    /// Sets the style of the progress bars on the display
    /// </summary>
    /// <param name="bs">barstyle structure (stored in RAM) holding the definition of the style</param>
    void setStyle(const barstyle& bs)
    {
        barStyle = &bs;
        styleMemPlacement = RAM;
        begin();
    }

    /// <summary>
    /// Sets the style of the progress bars on the display
    /// </summary>
    /// <param name="bs">barstyle structure (stored in FLASH wrap it up using inPROGMEM(.) !) holding the definition of the style</param>
    void setStyle(const inPROGMEM& wraped)
    {
        barStyle = wraped.unwrap();
        styleMemPlacement = FLASH;
        begin();
    }

    /// <summary>
    /// Access to the parameters of the style 
    /// </summary>
    /// <returns>reference to the nested structure bspar defining the offsets and the orientation of the progress bars</returns>
    barstyle::bspar stylePar() const
    {
        if (styleMemPlacement == RAM)
        {
            return(barStyle->stylePar);
        }
        else
        {
            uint8_t m = pgm_read_byte(&(barStyle->stylePar));
            return *(reinterpret_cast<struct barstyle::bspar*>(&m));
        }
    }

    /// <summary>
    /// Returns the start offset (in pixels) of the progress bars
    /// </summary>
    /// <returns>start offset (in pixels)</returns>
    inline int styleStartOffset() const
    {
        return stylePar().startOffset;
    }

    /// <summary>
    /// Returns the end offset (in pixels) of the progress bars
    /// </summary>
    /// <returns>end offset (in pixels)</returns>
    inline int styleEndOffset() const
    {
        return stylePar().endOffset;
    }

    /// <summary>
    /// Returns the orientation of the progress bar
    /// </summary>
    /// <returns>orientation 0:Horizontal==0 or 1:Vertical</returns>
    inline uint8_t styleOrientation() const
    {
        return stylePar().dir;
    }

    /// <summary>
    /// Initializes the BarDisplay object with the progress bar style 
    /// </summary>
    void begin() const
    {
        // create the blank piece in the middle 
        createChar(ProgBarCharBlank, (barStyle->middleMask[barstyle::ORmask]));
        // create the completely filled piece in the middle 
        createChar(ProgBarCharFull, barStyle->middleMask);
        // create the full piece at the beginning (left edge of the frame when filled, bottom on vertical progress bar)
        createChar(ProgBarCharBegin, barStyle->startMask);
        // create the blank piece at the end (right edge of the frame when blank, top on vertical progress bar)
        createChar(ProgBarCharEnd, (barStyle->endMask[barstyle::ORmask])); 
    }

    /// <summary>
    /// Creates a user defined character in the CGRAM of the LCD display 
    /// </summary>
    /// <param name="udChr">character code position 0-7</param>
    /// <param name="xMask">pointer to masks (AND and OR in PROGMEM) to be used when defining the character</param>
    /// <param name="mask">mask (left filled with 1's) defining how much the character will be filled</param>
    void makeChar(byte udChr, const uint8_t xMask[2][barstyle::CharPatRows], uint8_t mask) const
    {
        uint8_t t[barstyle::CharPatRows];
        if (styleMemPlacement == RAM) 
        {
            makeCharMask(t, xMask, mask);
        }
        else // in FLASH
        {
            uint8_t tao[2][barstyle::CharPatRows];
            memcpy_P(tao, xMask, barstyle::CharPatRows << 1);
            makeCharMask(t, tao, mask);
        }
        disp.createChar(udChr, t);
    }

protected:
    /// <summary>
    /// Prepares the bitmap for making the user defined character
    /// </summary>
    /// <param name="out">pointer to array to hold the output bitmap</param>
    /// <param name="xMask">pointer to the AND and OR masks defining the style - the bits that always be off (margin) and the bits that will always be on (frame)</param>
    /// <param name="mask">mask (left filled with 1's) defining how much the character will actually be filled with pixels</param>
    void makeCharMask(uint8_t out[barstyle::CharPatRows], const uint8_t xMask[2][barstyle::CharPatRows], uint8_t mask) const
    {
        if (styleOrientation() == barstyle::Vertical)
        {
            for (byte i = 0; i < barstyle::CharPatRows; i++, mask >>= 1)
            {
                out[i] = (mask & 1) ? (xMask[0][i] | xMask[1][i]) : xMask[1][i];
            }
        }
        else // Horizontal
        {
            for (byte i = 0; i < barstyle::CharPatRows; i++)
            {
                out[i] = (mask & xMask[0][i]) | xMask[1][i];
            }
        }
    }

    /// <summary>
    /// Creates a user defined character in the CGRAM of the LCD display 
    /// using the bitmap stored in bitMask argument
    /// </summary>
    /// <param name="udChr">character code position 0-7</param>
    /// <param name="bitMask">pointer to the array holding the bitmap of the character</param>
    void createChar(byte udChr, const uint8_t bitMask[barstyle::CharPatRows]) const
    {
        if (styleMemPlacement == RAM)
        {
            disp.createChar(udChr, const_cast<uint8_t*>(bitMask));
        }
        else // in FLASH
        {
            uint8_t ta[barstyle::CharPatRows];
            memcpy_P(ta, bitMask, barstyle::CharPatRows);
            disp.createChar(udChr, ta);
        }
    }

    /// <summary>
    /// Creates a user defined character in the CGRAM of the LCD display 
    /// using the bitmaps stored in xMask argument
    /// </summary>
    /// <param name="udChr">character code position 0-7</param>
    /// <param name="xMask">2x8 matrix holding the bitmaps (AND and OR mask) that are OR-ed together to get the character bitmap</param>
    void createChar(byte udChr, const uint8_t xMask[2][barstyle::CharPatRows]) const
    {
        if (styleMemPlacement == RAM)
        {
            uint8_t t[barstyle::CharPatRows];
            for (byte i = 0; i < barstyle::CharPatRows; i++)
            {
                t[i] = xMask[0][i] | xMask[1][i];
            }
            disp.createChar(udChr, t);
        }
        else // in FLASH
        {
            uint8_t tao[2][barstyle::CharPatRows];
            memcpy_P(tao, xMask, barstyle::CharPatRows << 1);
            for (byte i = 0; i < barstyle::CharPatRows; i++)
            {
                tao[0][i] |= tao[1][i];
            }
            disp.createChar(udChr, tao[0]);
        }
    }

    DISP & disp; // pointer to the display object
    const barstyle* barStyle; // pointer to the bar style struct
    MemoryType styleMemPlacement; // where the bitmaps defining the style (barstyle*) are stored, RAM or FLASH
};

/// <summary>
/// Class defining the position and the size of the progress bar on the display 
/// </summary>
class BarPos
{
public:
    /// <summary>
    /// Constructs the BarPos object representing the position and the size of the progress bar on the display 
    /// </summary>
    /// <param name="_len">length of the progress bar in characters</param>
    /// <param name="_row">the row in which the progress bar starts</param>
    /// <param name="_col">the column in which the progress bar starts</param>
    /// <param name="_id">id of the progress bar 0-4 (as at most 4 can be supported simultaneously)</param>
    BarPos(byte _len, byte _col, byte _row, byte _id = 0)
        : par(ProgBarPar{ _col, _row, _len, _id }) { }
 
    /// <summary>
    /// Sets the length of the progress bar
    /// </summary>
    /// <param name="_len">length of the progress bar in characters</param>
    inline void setLength(int _len) // in characters 
    {
        par.len = _len;
    }

    /// <summary>
    /// Gets the length of the progress bar (in characters)
    /// </summary>
    /// <returns>the length of the progress bar in characters</returns>
    inline int getLength() const 
    {
        return par.len;
    }

    /// <summary>
    /// Sets the position of the progress bar on the display
    /// the row and the column represents the position of the start character of the progress bar 
    /// (leftmost of the horizontal progress bar and the bottom one on a vertical progress bar)
    /// </summary>
    /// <param name="_row">the row in which the progress bar starts</param>
    /// <param name="_col">the column in which the progress bar starts</param>
    inline void setPosition(byte _col, byte _row)
    {
        par.col = _col;
        par.row = _row;
    }

    /// <summary>
    /// Returns the position of the progress bar on the display
    /// </summary>
    /// <returns>the column of the progress bar</returns>
    inline uint8_t col() const 
    {
        return par.col;
    }

    /// <summary>
    /// Returns the position of the progress bar on the display
    /// </summary>
    /// <returns>the row of the progress bar</returns>
    inline uint8_t row() const
    {
        return par.row;
    }

protected:
    struct ProgBarPar
    {
        byte col : 6; // column position of the progress bar
        byte row : 2; // row position of the progress bar
        byte len : 6; // progress bar length in characters
        const byte id  : 2; // progress bar number 0-3 
    } par;
};

/// <summary>
/// Class representing a smooth progress bar
/// </summary>
/// <typeparam name="DISP">BarDisplay class</typeparam>
template < class DISP >
class ProgressBar : public BarPos
{
private:
    ProgressBar(byte _len, byte _col, byte _row, byte _id = 0)
        : BarPos(_len, _col, _row, _id) { }

public:
    /// <summary>
    /// Creates horizontal ProgressBar object
    /// </summary>
    /// <typeparam name="DISP">the display on which it will be shown</typeparam>
    /// <typeparam name="len">the length of the progress bar in characters, has to be 2 or more</typeparam>
    /// <typeparam name="row">position: the row of the start end of the progress bar</typeparam>
    /// <typeparam name="col">position: the column of the start end of the progress bar</typeparam>
    /// <typeparam name="id">the id of the progress bar (4 supported: 0-3)</typeparam>
    ProgressBar(DISP& disp, byte _width, byte _col, byte _row, byte _pbn = 0)
        : BarPos(_width, _col, _row, _pbn), barDisp(disp) { }

    /// <summary>
    /// Returns the size of the progress bar in pixels (height for vertical, width for horizontal)
    /// </summary>
    /// <returns>the size of the progress bar in pixels (to be filled - without the possible frame and he margin)</returns>
    unsigned int size() const
    {
        const barstyle::bspar & barStylePar = barDisp.stylePar();
        return par.len * (barStylePar.dir ? barstyle::CharPatRows : barstyle::CharPatCols) - barStylePar.startOffset - barStylePar.endOffset;
    }

    /// <summary>
    /// Draws the progress bar on the LCD display
    /// </summary>
    /// <param name="val">at what extent it is filled (left to right) in pixels : 0 to (including) size() </param>
    /// <remarks>The progress bar is "drawn" printing over all the characters occupied by the progress bar on every call< / remarks>
    void showProgress(int val)
    {
        //const barstyle::bspar& barStylePar = barDisp.stylePar();
        //showProg(val + barStylePar.startOffset, par.id);
        showProg(val + barDisp.styleStartOffset(), par.id);
    }

    /// <summary>
    /// Draws the progress bar on the LCD display
    /// </summary>
    /// <param name="val">at what extent it is filled (left to right) in percents : 0 to 100 </param>
    /// <remarks>The progress bar is "drawn" printing over all the characters occupied by the progress bar on every call< / remarks>
    void showProgressPct(int val) { showProgress((val * size()) / 100); }

protected:
    /// <summary>
    /// Draws the horizontal progress bar on the LCD display
    /// </summary>
    /// <param name="val">at what extent it is filled in pixels</param>
    /// <param name="n">the id of the progress bar : 0-3</param>
    void showProg(int val, byte n)
    {
        const barstyle::bspar& barStylePar = barDisp.stylePar();
        const byte cellDim = barStylePar.dir ? barstyle::CharPatRows : barstyle::CharPatCols;
        const byte rem = (cellDim - (val % cellDim));
        uint8_t mask = barStylePar.dir ?
            (barstyle::AllRows << rem) :
            ((barstyle::AllCols << rem));
        byte full = min(max(0, val / cellDim - 1), par.len - 2);
        const byte partial = (val > cellDim && val < (par.len - 1) * cellDim);
        byte blank = max(0, par.len - full - 2 - partial);
        
        // determine and prepare the user defined characters
        if (val < cellDim) // still filling the first block, create and use the middle char
        {
            barDisp.makeChar(DISP::ProgBarCharPartial + n, barDisp.getStyle().startMask, mask);
        }
        if (partial)
        {
            barDisp.makeChar(DISP::ProgBarCharPartial + n, barDisp.getStyle().middleMask, mask);
        }
        if (val > (par.len - 1) * cellDim) // last block partially (or fully) filled, create and use the middle char
        {
            if (val >= par.len * cellDim) // special case val == size() - last block completely full
            {
                mask = (barStylePar.dir ? barstyle::AllRows : barstyle::AllCols);
            }
            barDisp.makeChar(DISP::ProgBarCharPartial + n, barDisp.getStyle().endMask, mask);
        }

        barDisp.dsplay().setCursor(par.col, par.row);
        barDisp.dsplay().write((val < cellDim) ? (DISP::ProgBarCharPartial + n) : DISP::ProgBarCharBegin);

        // show on the display 
        byte crow = par.row;
        while (full--)
        {
            if (barStylePar.dir)
            {
                barDisp.dsplay().setCursor(par.col, --crow);
            }
            barDisp.dsplay().write(DISP::ProgBarCharFull);
        }
        if (partial)
        {
            if (barStylePar.dir)
            {
                barDisp.dsplay().setCursor(par.col, --crow);
            }
            barDisp.dsplay().write(DISP::ProgBarCharPartial + n);
        }
        while (blank--)
        {
            if (barStylePar.dir)
            {
                barDisp.dsplay().setCursor(par.col, --crow);
            }
            barDisp.dsplay().write(DISP::ProgBarCharBlank);
        }
        if (barStylePar.dir)
        {
            barDisp.dsplay().setCursor(par.col, --crow);
        }
        barDisp.dsplay().write((val > (par.len - 1) * cellDim) ? (DISP::ProgBarCharPartial + n) : DISP::ProgBarCharEnd);
    }
    
    //data
    const DISP& barDisp; // reference to the display wrapper object
};

typedef BarDisplay < LCD_OBJ > LCD;
typedef ProgressBar < BarDisplay < LCD_OBJ > > SmoothProgressBar;


#endif // SMOOTH_PROGRESS_H
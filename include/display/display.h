#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "display/display_align.h"
#include "display/display_text.h"
#include "display/display_margin.h"


/**
 * @brief A wrapper class for the Adafruit_SSD1306, for interacting with small OLED screens
*/
class Display
{
  private:
    Adafruit_SSD1306 mDisplay;  ///< The actual display screen

    uint8_t mScreenWidth;       ///< The width of the screen
    uint8_t mScreenHeight;      ///< The height of the screen
    uint8_t mAddress;           ///< The address of the screen (default is 0x3C, but if that doesn't work, try 0x3D)
    int8_t mOledReset;          ///< The reset pin for the screen (-1 for no reset pin)

    uint8_t mPrintSize;         ///< The size at which the text is printed
    DisplayAlign mAlignment;    ///< The alignment of the printed text
    DisplayMargin mMargin;      ///< The margins which will leave a gap between the edge of the screen and the text

  public:
    /**
     * @brief Constructs a Display object.
     * @param width The width of the screen in pixels.
     * @param height The height of the screen in pixels.
     * @param oledReset The reset pin for the OLED screen. If there is no reset pin, use `-1`
     * @param address The memory address of the screen. Default is `0x3C`, but if that doesn't work try `0x3D`
    */
    Display(uint8_t width, uint8_t height, int8_t oledReset, uint8_t address=0x3C)
    : mScreenWidth(width), mScreenHeight(height), 
      mOledReset(oledReset), mAddress(address),
      mPrintSize(2), mMargin(0), mAlignment(DisplayAlign{}),
      mDisplay(Adafruit_SSD1306{width, height, &Wire, oledReset})
    {}

    /**
     * @brief Constructs a Display object with not reset pin (set to `-1`).
     * @param width The width of the screen in pixels.
     * @param height The height of the screen in pixels.
     * @param address The memory address of the screen. Default is `0x3C`, but if that doesn't work try `0x3D`
    */
    Display(uint8_t width, uint8_t height, uint8_t address=0x3C)
    : Display(width, height, -1, address)
    {}


    /**
     * @brief Starts the Adafruit display to be able to print
     * @return If the screen was able to start
     * @note This function should be called first, otherwise you will be calling a display that is not on
    */
    bool start();

    /**
     * @brief Sets the display screen to black
     */
    void clear();

    /**
     * @brief Prints a string to the screen
     * @param text The string that will be printed
     * @note If `Display::clear()` is not called, characters will overlap
     */
    void print(DisplayText text);


    // Getters
    /// @return The width of the screen in pixels.
    uint8_t getScreenWidth() const { return mScreenWidth; }

    /// @return The height of the screen in pixels.
    uint8_t getScreenHeight() const { return mScreenHeight; }

    /// @return The memory address of the OLED display
    uint8_t getAddress() const { return mAddress; }

    /// @return The OLED reset pin (`-1` if there is none)
    int8_t getOledReset() const { return mOledReset; }


    /// @return The size of the text that is printed
    uint8_t getPrintSize() const { return mPrintSize; }

    /// @return The width in pixels of a character
    /// @note This assumes the default Adafruit character width (`x * 6`)
    uint16_t getCharWidth() const { return mPrintSize * 6; }

    /// @return The height in pixels of a character
    /// @note This assumes the default Adafruit character height (`x * 8`)
    uint16_t getCharHeight() const { return mPrintSize * 8; }

    /// @return The alignment of the text of the screen
    DisplayAlign& getAlignment() { return mAlignment; }

    /// @return The margins which will leave a gap between the edge of the screen and the text
    DisplayMargin& getMargin() { return mMargin; }


    // Setters
    /// @param size Sets the text size of characters that are printed to the screen
    /// @note Any size larger than 5 may cause the letters to be too big
    void setPrintSize(uint8_t size) { mPrintSize = size; }

    /// @param alignment Sets the alignment of the printed text
    void setAlignment(const DisplayAlign& alignment) { mAlignment = alignment; }

    /// @param margin Sets the margins of the screen
    /// @note Any size larger than 5 may create too little room for characters
    void setMargin(const DisplayMargin& margin) { mMargin = margin; }

};


#endif//DISPLAY_H
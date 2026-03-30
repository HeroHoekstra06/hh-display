#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "display/display_text.h"


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


    // Getters
    /// @return The width of the screen in pixels.
    uint8_t getScreenWidth() const { return mScreenWidth; }

    /// @return The height of the screen in pixels.
    uint8_t getScreenHeight() const { return mScreenHeight; }

    /// @return The memory address of the OLED display
    uint8_t getAddress() const { return mAddress; }

    /// @return The OLED reset pin (`-1` if there is none)
    int8_t getOledReset() const { return mOledReset; }
    
};


#endif//DISPLAY_H
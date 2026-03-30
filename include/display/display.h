#ifndef DISPLAY_H
#define DISPLAY_H

#include "display/display_text.h"


class Display
{
  private:
    uint8_t mScreenWidth;   ///< The width of the screen
    uint8_t mScreenHeight;  ///< The height of the screen
    uint8_t mAddress;       ///< The address of the screen (default is 0x3C, but if that doesn't work, try 0x3D)
    int8_t mOledReset;      ///< The reset pin for the screen (-1 for no reset pin)

  public:
    Display(uint8_t width, uint8_t height, int8_t oledReset, uint8_t address=0x3C)
    : mScreenWidth(width), mScreenHeight(height), 
      mOledReset(oledReset), mAddress(address)
    {}

};


#endif//DISPLAY_H
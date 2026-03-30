#ifndef DISPLAY_TEXT_H
#define DISPLAY_TEXT_H

#include <Wire.h> // Include for String


/**
 * @brief A simple wrapper class for `Wire.h`'s `String` meant to be displayed on screens.
 */
class DisplayText
{
  private:
    const String mText; ///< Stored text to be displayed

  public:
    DisplayText(String text)
      : mText(text)
    {}

};


#endif//DISPLAY_TEXT_H
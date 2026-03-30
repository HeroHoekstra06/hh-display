#ifndef DISPLAY_TEXT_H
#define DISPLAY_TEXT_H

#include <string>


/**
 * @brief A simple strin wrapper class meant to be displayed to a screen.
 */
class DisplayText
{
  private:
    const std::string mText;  ///< Stored text for later use.
    const char *mRawString;   ///< Stored text as a raw string.

  public:
    DisplayText(std::string text)
      : mText(text), mRawString(mText.c_str())
    {}

};


#endif//DISPLAY_TEXT_H
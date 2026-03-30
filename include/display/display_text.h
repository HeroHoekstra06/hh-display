#ifndef DISPLAY_TEXT_H
#define DISPLAY_TEXT_H

#include <string>


/**
 * @brief A simple strinh wrapper class meant to be displayed to a screen.
 */
class DisplayText
{
  private:
    const std::string mText;  ///< Stored text for later use.
    const char *mRawString;   ///< Stored text as a raw string.

  public:
    /**
     * @brief Constructs a DisplayText object from a standard string.
     * * @param text The string to be stored and displayed.
     * @note Memory management and conversions are handled by the 
     * standard string library.
     * @see https://cplusplus.com/reference/string/string/
     */
    DisplayText(const std::string& text)
    : mText(text), mRawString(mText.c_str())
    {}

};


#endif//DISPLAY_TEXT_H
#ifndef DISPLAY_TEXT_H
#define DISPLAY_TEXT_H

#include <string>


/**
 * @brief A simple string wrapper class meant to be displayed to a screen.
 */
class DisplayText
{
  private:
    const std::string mText;  ///< Stored text for later use.
    const char *mRawString;   ///< Stored text as a raw string.

    const uint16_t mLength;   ///< The size of the stored string.
    uint16_t mCurrentPos;     ///< The current position for the `DisplayText::getLine()` function.

  public:
    /**
     * @brief Constructs a DisplayText object from a standard string.
     * @param text The string to be stored and displayed.
     * @note Memory management and conversions are handled by the 
     * standard string library.
     * @see https://cplusplus.com/reference/string/string/
     */
    DisplayText(const std::string& text)
    : mText(text), mRawString(mText.c_str()), mLength(text.length())
    {}


    /**
     * @brief Gets a specific line to a buffer. Meant to be used in `while` loops
     * @param buffer The memory address of a buffer to which the line will be send
     * @param lineSize The amount of characters per line
     * @return If this is the last step, or if there should be another loop
     */
    bool getLine(char* buffer, uint16_t lineSize);


    // Getters
    /// @return The stored string
    const std::string& getText() const { return mText; }

    /// @return The raw stored string
    const char *getRawString() const { return mRawString; }

    /// @return The amount of characters of the stored text
    const uint16_t getLength() const { return mLength; }

};


#endif//DISPLAY_TEXT_H
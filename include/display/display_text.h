#ifndef DISPLAY_TEXT_H
#define DISPLAY_TEXT_H

#include <string>
#include <vector>


/**
 * @brief A simple string wrapper class meant to be displayed to a screen.
 */
class DisplayText
{
  private:
    const std::string mText;          ///< Stored text for later use.
    const char *mRawString;           ///< Stored text as a raw string.

    const uint16_t mLength;           ///< The size of the stored string.
    uint16_t mCurrentPos;             ///< The current position for the `DisplayText::getLine()` function.
    uint16_t mLineAmount;             ///< The amount of lines that are send to the screen

    std::vector<uint16_t> mLineSizes; ///< The calculated line sizes
    uint16_t mLineAmount;             ///< The amount of lines

  public:
    /**
     * @brief Constructs a DisplayText object from a standard string.
     * @param text The string to be stored and displayed.
     * @note Memory management and conversions are handled by the 
     * standard string library.
     * @see https://cplusplus.com/reference/string/string/
     */
    DisplayText(const std::string& text)
    : mText(text), mRawString(mText.c_str()), 
      mLength(text.length()), mCurrentPos(0), mLineAmount(0)
    {}


    /**
     * @brief Gets a specific line to a buffer. Meant to be used in `while` loops
     * @param buffer The memory address of a buffer to which the line will be send
     * @param lineSize The amount of characters per line
     * @return If this is the last step, or if there should be another loop
     */
    bool getLine(char* buffer, uint16_t lineSize);

    /**
     * @brief Gets the amount of lines that this text will create
     * @param lineSize The amount of characters per line
     * @return The amount of lines
     * @note Once this function has been called, the line amount will be stored and returned the next time this function is called.
     * If the text somehow got altered the line amount may be incorrect.
    */
    uint16_t getLineAmount(uint16_t lineSize);

    /**
     * @brief Gets the amount of characters in one line
     * @param line The line index
     * @return The amount of characters
     */
    uint16_t getLineSize(uint16_t line);


    // Getters
    /// @return The stored string
    const std::string& getText() const { return mText; }

    /// @return The raw stored string
    const char *getRawString() const { return mRawString; }

    /// @return The amount of characters of the stored text
    const uint16_t getLength() const { return mLength; }

};


#endif//DISPLAY_TEXT_H
#ifndef DISPLAY_TYPOGRAPHY_H
#define DISPLAY_TYPOGRAPHY_H

#include <stdint.h>


/**
 * @brief A helper class for `Display` which determines the gap between lines and characters
*/
class DisplayTypography
{
  private:
    uint8_t mLineHeight;  ///< The height of each line in pixels
    uint8_t mCharGap;     ///< The gap between each character in pixels

  public:
    /**
     * @brief Constructs a DisplayTypography object, which determines the gap between characters
     * @param lineHeight The amount that the Y position of the cursor is incremented with
     * @param charGap The amount of pixels between each character
     * @note `lineHeight` is the total line height. 
     * This means that if a characters height is 8, and the line height is 4, the characters will overlap.
     * @note `charGap` is only for the X gap between characters, not Y. 
     * To change the gap between the characters on the Y axis, call `Display::getCharHeight() + desiredGapSize`.
    */
    DisplayTypography(uint8_t lineHeight, uint8_t charGap)
    : mLineHeight(lineHeight), mCharGap(charGap)
    {}

    /**
     * @brief Constructs a DisplayTypography object, which determines the gap between characters
     * @note This constructor assumes the default Adafruit character sizes, which means a 
     * `lineHeight` of 9 pixels (8 is the character height + 1 as a small gap) and `charGap` is 1
     */
    DisplayTypography()
    : DisplayTypography(9, 1)
    {}

};


#endif//DISPLAY_TYPOGRAPHY_H
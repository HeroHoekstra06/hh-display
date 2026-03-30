#ifndef DISPLAY_MARGIN_H
#define DISPLAY_MARGIN_H

#include <stdint.h>


/**
 * @brief A class to add a pixel amount of margin to a display screen
 */
class DisplayMargin
{
  private:
    int8_t mLeft;   ///< The left margin in pixels
    int8_t mTop;    ///< The top margin in pixels
    int8_t mRight;  ///< The right margin in pixels
    int8_t mBottom; ///< The bottom margin in pixels

  public:
    /**
     * @brief Constructs the margins which will be used on the screen
     * @param left The left margin in pixels
     * @param top The top margin in pixels
     * @param right The right margin in pixels
     * @param bottom The bottom margin in pixels
     * @note Use negative numbers to move the text off-screen
     */
    DisplayMargin(int8_t left, int8_t top, int8_t right, int8_t bottom)
    : mLeft(left), mTop(top), mRight(right), mBottom(bottom)
    {}

    /**
     * @brief Constructs the margins which will be used on the screen
     * @param horizontal The horizontal margin (left and right)
     * @param vertical The vertical margin (top and bottom)
     * @note The input is NOT the sum of the margins; so a horizontal margin of `4px` would be `4px + 4px` is a total margin of 8 pixels
     * @note Use negative numbers to move the text off-screen
     */
    DisplayMargin(int8_t horizontal, uint8_t vertical)
    : DisplayMargin(horizontal, vertical, horizontal, vertical)
    {}

    /**
     * @brief Constructs the margins which will be used on the screen
     * @param horizontal The horizontal margin (left and right)
     * @param vertical The vertical margin (top and bottom)
     * @note The input is NOT the sum of the margins; so a margin of 2px would be 2px left, 2px top, etc.
     * @note Use negative numbers to move the text off-screen
     */
    DisplayMargin(int8_t margin)
    : DisplayMargin(margin, margin, margin, margin)
    {}

};


#endif//DISPLAY_H
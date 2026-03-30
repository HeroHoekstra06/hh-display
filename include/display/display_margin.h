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
     */
    DisplayMargin(int8_t left, int8_t top, int8_t right, int8_t bottom)
    : mLeft(left), mTop(top), mRight(right), mBottom(bottom)
    {}

};


#endif//DISPLAY_H
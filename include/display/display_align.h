#ifndef DISPLAY_ALIGN_H
#define DISPLAY_ALIGN_H

#include "display/display_margin.h"
#include "display/display_text.h"


/**
 * @brief A horizontal alignment flag for the `DisplayAlign` class
*/
enum class HAlignFlag
{
  Left,
  Center,
  Right
};

/**
 * @brief A vertical alignment flag for the `DisplayAlign` class
*/
enum class VAlignFlag
{
  Top,
  Center,
  Bottom
};


/**
 * @brief A class to align text on a display using the `Display` class
*/
class DisplayAlign
{
  private:
    HAlignFlag mHFlag;   ///< Horizontal alignment flag
    VAlignFlag mVFlag;   ///< Vertical alignment flag

  public:
    /**
     * @brief Constructs a `DisplayAlign` class
     * @param hFlag The horizontal alignment flag
     * @param vFlag The vertical alignment flag
    */
    DisplayAlign(HAlignFlag hFlag, VAlignFlag vFlag)
    : mHFlag(hFlag), mVFlag(vFlag)
    {}

    /**
     * @brief Constructs a `DisplayAlign` class
     * @param hFlag The horizontal alignment flag
    */
    DisplayAlign(HAlignFlag hFlag)
    : DisplayAlign(hFlag, VAlignFlag::Top)
    {}

    /**
     * @brief Constructs a `DisplayAlign` class
     * @param vFlag The vertical alignment flag
    */
    DisplayAlign(VAlignFlag vFlag)
    : DisplayAlign(HAlignFlag::Left, vFlag)
    {}

    /**
     * @brief Constructs a `DisplayAlign` class
    */
    DisplayAlign()
    : DisplayAlign(HAlignFlag::Left, VAlignFlag::Top)
    {}


    /**
     * @brief Calculates the starting X so that the text is properly aligned
     * @param text The display text used to calculate the total width
     * @param margin The margin which will be added to the start X
     * @return The X coordinate where the text needs to start
    */
    int16_t findStartX(char *text, const DisplayMargin& margin, uint8_t screenWidth, uint8_t printSize);


    // Getters
    /// @return The horizontal alignment flag
    HAlignFlag getHFlag() { return mHFlag; }

    /// @return The vertical alignment flag
    VAlignFlag getVFlag() { return mVFlag; }


    // Setters
    /// @param flag The horizontal alignment flag
    void setHFlag(HAlignFlag flag) { mHFlag = flag; }

    /// @param flag The vertical alignment flag
    void setVFlag(VAlignFlag flag) { mVFlag = flag; }

};


#endif//DISPLAY_ALIGN_H
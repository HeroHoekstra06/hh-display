#ifndef DISPLAY_ALIGN_H
#define DISPLAY_ALIGN_H


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


    // Getters
    /// @return The horizontal alignment flag
    HAlignFlag getHFlag() { return mHFlag; }

    /// @return The vertical alignment flag
    VAlignFlag getVFlag() { return mVFlag; }


    // Setters
    void setHFlag(HAlignFlag flag) { mHFlag = flag; }

    void setVFlag(VAlignFlag flag) { mVFlag = flag; }

};


#endif//DISPLAY_ALIGN_H
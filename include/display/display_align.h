#ifndef DISPLAY_ALIGN_H
#define DISPLAY_ALIGN_H


/**
 * @brief An alignment flag for the `DisplayAlign` class
 * @note Items prefixed with 'H' are for the horizontal alignment
*/
enum class HAlignFlag
{
  Left,
  Center,
  Right
};


/**
 * @brief A class to align text on a display using the `Display` class
*/
class DisplayAlign
{
  private:
    HAlignFlag mFlag;   ///< Stored enum for later reference

  public:
    /**
     * @brief Constructs a `DisplayAlign` class
     * @param flag The alignment which will be used on a display
    */
    DisplayAlign(HAlignFlag flag)
    : mFlag(flag)
    {}

    /**
     * @brief Constructs a `DisplayAlign` class with `DisplayAlignFlag::H_ALIGN_LEFT` as the default
    */
    DisplayAlign()
    : DisplayAlign(HAlignFlag::Left)
    {}


    // Getters
    /// @return The alignment flag
    HAlignFlag getFlag() { return mFlag; }


    // Setters
    void setFlag(HAlignFlag flag) { mFlag = flag; }

};


#endif//DISPLAY_ALIGN_H
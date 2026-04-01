#ifndef DISPLAY_ALIGN_H
#define DISPLAY_ALIGN_H


/**
 * @brief An alignment flag for the `DisplayAlign` class
 * @note Items prefixed with 'H' are for the horizontal alignment
*/
enum DisplayAlignFlag
{
  H_ALIGN_LEFT,
  H_ALIGN_CENTER,
  H_ALIGN_RIGHT
};


/**
 * @brief A class to align text on a display using the `Display` class
*/
class DisplayAlign
{
  private:
    DisplayAlignFlag mFlag;   ///< Stored enum for later reference

  public:
    /**
     * @brief Constructs a `DisplayAlign` class
     * @param flag The alignment which will be used on a display
    */
    DisplayAlign(DisplayAlignFlag flag)
    : mFlag(flag)
    {}

    /**
     * @brief Constructs a `DisplayAlign` class with `DisplayAlignFlag::H_ALIGN_LEFT` as the default
    */
    DisplayAlign()
    : DisplayAlign(DisplayAlignFlag::H_ALIGN_LEFT)
    {}

};


#endif//DISPLAY_ALIGN_H
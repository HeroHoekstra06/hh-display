#include <cstring>

#include "display/display_align.h"
#include "display/display_margin.h"


int16_t DisplayAlign::findStartX(char *text, const DisplayMargin& margin, uint8_t screenWidth, uint8_t charSize)
{
  uint16_t stringWidth = strlen(text) * charSize;
  
  int16_t innerWidth = screenWidth - margin.getLeft() - margin.getRight();
  int16_t useableSpace = innerWidth - stringWidth;

  if (mHFlag == HAlignFlag::Left)
  {
    return margin.getLeft();
  }
  else if (mHFlag == HAlignFlag::Right)
  {
    return margin.getLeft() + useableSpace;
  }
  else // HAlignFlag::Center
  {
    return margin.getLeft() + (useableSpace / 2);
  }
}
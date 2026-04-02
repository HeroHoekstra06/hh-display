#include <cstring>

#include "display/display_align.h"
#include "display/display_margin.h"

// Temp for testing
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


int16_t DisplayAlign::findStartX(char *text, const DisplayMargin& margin, uint8_t screenWidth, uint8_t charSize)
{
  uint16_t stringWidth = strlen(text) * charSize;
  
  int16_t innerWidth = screenWidth - margin.getHorizontal();
  int16_t useableSpace = innerWidth - stringWidth;

  if (mHFlag == HAlignFlag::Left)
  {
    return margin.getLeft();
  }
  else if (mHFlag == HAlignFlag::Right)
  {
    return (margin.getLeft() + useableSpace) - margin.getRight();
  }
  else // HAlignFlag::Center
  {
    return (margin.getLeft() + useableSpace) / 2 - margin.getRight();
  }
}


int16_t DisplayAlign::findStartY(const DisplayMargin& margin, uint8_t screenHeight, uint8_t lineAmount, uint8_t charSize)
{
  int16_t innerHeight = screenHeight - margin.getVertical();
  int16_t totalSize = lineAmount * charSize;
  int16_t useableSpace = innerHeight - totalSize;

  if (mVFlag == VAlignFlag::Top)
  {
    return margin.getTop();
  }
  else if (mVFlag == VAlignFlag::Bottom)
  {
    return (margin.getTop() + useableSpace) / 2 - margin.getBottom();
  }
  else // VAlignFlag::Center
  {
    return (margin.getTop() + useableSpace) / 4 - margin.getBottom();
  }
}

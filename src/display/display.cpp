#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "display/display.h"


bool Display::start()
{
  if (!mDisplay.begin(SSD1306_SWITCHCAPVCC, mAddress))
  {
    return false;
  }

  mDisplay.setTextColor(SSD1306_WHITE); // Assuming the screen is only capable of black and white
  mDisplay.setTextSize(mPrintSize);
  mDisplay.setTextWrap(false);

  return true;
}


void Display::clear()
{
  mDisplay.clearDisplay();
}


void Display::print(DisplayText text)
{
  if (getScreenWidth() <= mMargin.getHorizontal())
  {
    // Right now I use `Serial.println()`, but later it should probably use a propper logger
    Serial.println("Warning: The margin exceeds the screen width. Nothing will be printed.");
    return;
  }

  uint8_t maxCharsX = (getScreenWidth() - mMargin.getHorizontal()) / getCharWidth();
  int16_t cursorX = mMargin.getLeft();
  int16_t cursorY = mMargin.getTop();
  
  char buffer[maxCharsX + 1];
  while (text.getLine(buffer, sizeof(buffer)))
  {
    mDisplay.setCursor(cursorX, cursorY);
    mDisplay.print(buffer);
    cursorY += getCharHeight();
  }

  mDisplay.display();
}
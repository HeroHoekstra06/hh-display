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

  uint8_t useableSpace = getScreenWidth() - mMargin.getHorizontal();
  uint8_t charWidth = getCharWidth();
  uint8_t charGap = mTypography.getCharGap();

  uint8_t maxCharsX = (useableSpace + charGap) / (charWidth + charGap);
  
  char buffer[maxCharsX + 1];
  uint16_t lineSize = sizeof(buffer);

  int16_t cursorY = mAlignment.findStartY(mMargin, mScreenHeight, text.getLineAmount(lineSize), getCharHeight());

  while (text.getLine(buffer, lineSize))
  {
    int16_t cursorX = mAlignment.findStartX(buffer, mMargin, mScreenWidth, charWidth);

    for (char c : buffer)
    {
      mDisplay.setCursor(cursorX, cursorY);
      mDisplay.print(c);
      cursorX += (charWidth + charGap);
    }

    cursorY += getCharHeight();
  }

  mDisplay.display();
}


void Display::println(DisplayText text)
{
  const char *rawString = text.getRawString();
  uint8_t charWidth = getCharWidth() + mTypography.getCharGap();
  uint16_t lineAmount = text.getLineAmount(UINT16_MAX);

  int16_t cursorX = mAlignment.findStartX(rawString, mMargin, mScreenWidth, charWidth);
  int16_t cursorY = mAlignment.findStartY(mMargin, mScreenHeight, lineAmount, mTypography.getLineHeight());

  uint16_t i = 0;
  while (rawString[i] != '\0')
  {
    char c = rawString[i++];
    if (c == '\n')
    {
      cursorY += mTypography.getLineHeight();
      continue;
    }

    mDisplay.setCursor(cursorX, cursorY);
    mDisplay.print(c);

    cursorX += charWidth;
  }
}
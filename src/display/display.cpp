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

  // Avoid devide by 0 error
  if (charWidth + charGap == 0) return;

  uint8_t maxCharsX = (useableSpace + charGap) / (charWidth + charGap);
  if (maxCharsX == 0)
  {
    Serial.println("Warning: Screen space too small for text. Nothing will be printed.");
    return;
  }
  
  char buffer[256];

  uint16_t bufferLimit = maxCharsX + 1;
  uint16_t lineSize = bufferLimit;

  int16_t cursorY = mAlignment.findStartY(mMargin, mScreenHeight, text.getLineAmount(lineSize), getCharHeight());

  while (text.getLine(buffer, bufferLimit))
  {
    int16_t cursorX = mAlignment.findStartX(strlen(buffer), mMargin, mScreenWidth, charWidth + charGap);

    for (uint8_t i = 0; buffer[i] != '\0'; i++)
    {
      mDisplay.setCursor(cursorX, cursorY);
      mDisplay.print(buffer[i]);
      cursorX += (charWidth + charGap);
    }

    cursorY += getCharHeight();
  }

  mDisplay.display();
}


void Display::println(DisplayText text)
{
  const char *rawString = text.getRawString();

  uint16_t charWidth = getCharWidth() + mTypography.getCharGap();
  uint16_t cursorX = mAlignment.findStartX(text.getLineSize(0), mMargin, mScreenWidth, charWidth);
  uint16_t cursorY = 0;

  uint16_t currentLine = 0;

  for (uint16_t i = 0; rawString[i] != '\0'; i++)
  {
    char c = rawString[i];

    if (c == '\n')
    {
      cursorY += mTypography.getLineHeight();
      cursorX = mAlignment.findStartX(text.getLineSize(++currentLine), mMargin, mScreenWidth, charWidth);
      continue;
    }

    mDisplay.setCursor(cursorX, cursorY);
    mDisplay.print(c);

    cursorX += charWidth;
  }

  mDisplay.display();
}
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

  return true;
}
#include "display/display_text.h"


bool DisplayText::getLine(char* buffer, uint16_t bufferSize)
{
  if (mCurrentPos >= mLength) return false;

  uint16_t i = 0;
  while (i < (bufferSize - 1) && mCurrentPos < mLength)
  {
    char c = mRawString[mCurrentPos];

    if (c == '\n')
    {
      mCurrentPos++;
      break;
    }
    else if (c == '\0')
    {
      mCurrentPos = mLength;
      break;
    }

    buffer[i++] = c;
    mCurrentPos++;
  }
  buffer[i] = '\0';

  if (i == 0 && mCurrentPos >= mLength) return false;

  return true;
}


uint16_t DisplayText::getLineAmount(uint16_t lineSize)
{
  if (mLineAmount != 0) return mLineAmount;

  char *buffer;
  uint16_t i = 0;
  while (getLine(buffer, lineSize)) i++;

  mLineAmount = i;
  return i;
}
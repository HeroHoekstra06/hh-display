#include "display/display_text.h"


bool DisplayText::getLine(char*& buffer, uint16_t lineSize)
{
  if (mCurrentPos >= mLength)
  {
    return false;
  }

  buffer = const_cast<char*>(mRawString + mCurrentPos);
  int start = mCurrentPos;

  while (mCurrentPos < mLength)
  {
    if (mRawString[mCurrentPos] == '\n' || (mCurrentPos - start) == lineSize)
    {
      mCurrentPos++;
      break;
    }
    mCurrentPos++;
  }

  return true;
}
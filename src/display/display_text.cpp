#include "display/display_text.h"


void DisplayText::initializeLines()
{
  std::string buffer = "";

  for (char c : mText)
  {
    if (c == '\n')
    {
      // Push the buffer to `mLines` and make it an empty string again
      mLines.push_back(buffer);
      mLineSizes.push_back(buffer.size());
      buffer = "";
      continue;
    }

    buffer += c;
  }

  // Push the last line to the buffer, as it won't trigger the `if` in the loop
  mLines.push_back(buffer);
  mLineSizes.push_back(buffer.size());
}


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
  if (mLineAmount > 0) return mLineAmount;

  uint16_t savedPos = mCurrentPos;
  mCurrentPos = 0;

  char buffer[lineSize];
  uint16_t i = 0;
  while (getLine(buffer, lineSize)) i++;

  mCurrentPos = savedPos;
  mLineAmount = i;
  return i;
}

uint16_t DisplayText::getLineSize(uint16_t line)
{
  // Check if this function has already been done
  if (mLineSizes.size() > 0)
  {
    if (line > mLineAmount) return 0;
    else return mLineSizes[line];
  }
  
  // Only end up here if mLineSizes has not been "initialized" yet
  uint16_t lineSize = 0;
  for (char c : mText)
  {
    if (c == '\n')
    {
      mLineSizes.push_back(lineSize);
      lineSize = 0;
    }
    
    lineSize++;
  }
}

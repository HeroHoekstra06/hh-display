#include "display/display_text.h"

#include <cstring>


// Private
void DisplayText::initializeLines()
{
  std::string buffer = "";

  for (char c : mText)
  {
    if (c == '\n')
    {
      // Push the buffer to `mLines` and make it an empty string again
      uint16_t size = buffer.size();

      mLines.push_back(buffer);
      mLineSizes.push_back(size);

      if (mLongestLine < size) mLongestLine = size;

      buffer = "";

      continue;
    }

    buffer += c;
  }

  // Push the last line to the buffer, as it won't trigger the `if` in the loop
  uint16_t size = buffer.size();
  mLines.push_back(buffer);
  mLineSizes.push_back(size);

  if (mLongestLine < size) mLongestLine = size;

  mLineAmount = mLines.size();
}


// Public
bool DisplayText::getLine(char* buffer, uint16_t bufferSize)
{
  if (mCurrentPos >= mLineAmount) return false;

  // If the string size fits in the buffer, just return that
  if (mLongestLine < bufferSize)
  {
    strcpy(buffer, mLines[mCurrentPos++].c_str());
    return true;
  }

  std::string str = mLines[mCurrentPos];
  if (mLineSizes[mCurrentPos] < bufferSize)
  {
    strcpy(buffer, str.c_str());
    return true;
  }
  else
  {
    uint16_t i = 0;
    while (i++ < bufferSize || mCurrentPart == mLineSizes[mCurrentPos])
    {
      buffer[i] = str[mCurrentPart++];
    }
    buffer[bufferSize] = '\0';
  }
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

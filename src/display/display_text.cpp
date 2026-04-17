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

  const std::string& currentStr = mLines[mCurrentPos];

  uint16_t remainingChars = currentStr.length() - mCurrentPart;
  uint16_t charsToCopy = std::min<uint16_t>(bufferSize - 1, remainingChars);

  memcpy(buffer, currentStr.c_str() + mCurrentPart, charsToCopy);
  buffer[charsToCopy] = '\0';

  mCurrentPart += charsToCopy;

  if (mCurrentPart >= currentStr.length())
  {
    mCurrentPart = 0;
    mCurrentPos++;
  }

  return true;
}


uint16_t DisplayText::getLineAmount(uint16_t lineSize)
{
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

  return mLineSizes[line];
}

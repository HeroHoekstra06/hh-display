#ifndef DISPLAY_ALIGN_H
#define DISPLAY_ALIGN_H


enum DisplayAlignFlag
{
  H_ALIGN_LEFT,
  H_ALIGN_CENTER,
  H_ALIGN_RIGHT
};


class DisplayAlign
{
  private:
    DisplayAlignFlag mFlag;

  public:
    DisplayAlign()
    : mFlag(DisplayAlignFlag::H_ALIGN_LEFT)
    {}

};


#endif//DISPLAY_ALIGN_H
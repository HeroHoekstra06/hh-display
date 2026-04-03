#include "display/display.h"
#include "display/display_align.h"
#include "display/display_text.h"


void setup() 
{
  Serial.begin(115200);
  delay(1500);
  
  Display display{128, 64};
  display.start();
  display.clear();

  display.getAlignment().setHFlag(HAlignFlag::Left);
  display.getAlignment().setVFlag(VAlignFlag::Center);
  display.getTypography().setCharGap(3);

  display.print({"Hello,\nWorld!"});
}

void loop() 
{
}

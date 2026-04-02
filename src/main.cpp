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

  display.getAlignment().setHFlag(HAlignFlag::Right);
  display.getAlignment().setVFlag(VAlignFlag::Center);

  display.print({"Hello,\nWorld!"});
  
  display.getAlignment().setHFlag(HAlignFlag::Left);
  display.print({"2nd:"});
}

void loop() 
{
}

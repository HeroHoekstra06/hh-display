#include "display/display.h"
#include "display/display_text.h"


void setup() 
{
  Serial.begin(115200);
  delay(1500);
  
  Display display{128, 64};
  display.start();
  display.clear();

  display.setMargin({4, 4});

  display.print({"Hello,\nWorld!"});
}

void loop() 
{
}

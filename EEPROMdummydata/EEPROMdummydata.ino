
#include <EEPROM.h>

void setup()
{
  for (int i = 1; i < 48; i++)
    EEPROM.write(i, 0);
}

void loop()
{
}

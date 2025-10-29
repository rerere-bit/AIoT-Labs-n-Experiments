#include <Arduino.h>
#include "LITTLEFS.h"

void setup()
{
  Serial.begin(9600);

  if (!LITTLEFS.begin(true))
  {
    Serial.println("An error has occurred while mounting LittleFS.");
    return;
  }

  File file = LITTLEFS.open("/sample.txt", "r", false);
  if (!file)
  {
    Serial.println("Failed to open file for reading.");
    return;
  }

  Serial.println("File content: ");
  while (file.available())
  {
    Serial.write(file.read());
  }
  file.close();
}

void loop()
{
}

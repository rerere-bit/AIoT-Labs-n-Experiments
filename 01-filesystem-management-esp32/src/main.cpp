#include <Arduino.h>
#include "LITTLEFS.h"

void listDir(const char *dirname, uint8_t levels = 0){
  Serial.printf("Listing directory %s\n", dirname);
  File root = LITTLEFS.open(dirname);
  if (!root){
    Serial.println("Failed to open directory.");
    return;
  }
  if(!root.isDirectory()){
    Serial.println("Not a directory.");
    return;
  }

  File file = root.openNextFile();
  while (file){
    Serial.println("DIR: ");
    Serial.println(file.name());
    if(levels){
      listDir(file.name(), levels-1);
    }
    else{
      Serial.print("File: ");
      Serial.println(file.name());
      Serial.print("\t Size: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}
void setup()
{
  Serial.begin(9600);

  if (!LITTLEFS.begin(true))
  {
    Serial.println("An error has occurred while mounting LittleFS.");
    return;
  }

  listDir("/");

  File file = LITTLEFS.open("/sample.txt", "r", false);
  if (!file)
  {
    Serial.println("Failed to open file for reading.");
    return;
  }

  Serial.println("File content of /sample.txt: ");
  while (file.available())
  {
    Serial.write(file.read());
  }
  file.close();
}

void loop()
{
}

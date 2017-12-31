
#include <SPI.h>
#include <SD.h>
#include "string.h"

const int chipSelect = 4;

File dataFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");


  // open the file in MicroSD card
  dataFile = SD.open("datalog.csv", FILE_WRITE);
  dataFile.println("This is a data log test code!");
  dataFile.close();
  
}

void loop() {
  
  // make a string for assembling the data to log:
  String dataString = "";

//************************************************************

  static unsigned int value = 0;
  value = random(0,100);
  
  // read three sensors and append to the string:
  for (int i = 0; i < 3; i++) {
    dataString += String(value);
    if (i < 2) {
      dataString += ",";
    }
  }

//************************************************************


  dataFile = SD.open("datalog.csv", FILE_WRITE);
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.csv");
  }

  //delay(1000); // write data once per second
  
}










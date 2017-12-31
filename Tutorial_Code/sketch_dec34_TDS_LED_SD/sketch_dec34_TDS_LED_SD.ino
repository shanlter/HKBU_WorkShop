
#include <SPI.h>
#include <SD.h>
#include "string.h"

#define TdsSensorPin A1
#define VREF 5.0      // analog reference voltage(Volt) of the ADC
#define SCOUNT  30           // sum of sample point
int analogBuffer[SCOUNT];    // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0,copyIndex = 0;
float averageVoltage = 0,tdsValue = 0,temperature = 25;
const int chipSelect = 4;
const int LEDPin=10; 

File dataFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(TdsSensorPin,INPUT);
  pinMode(LEDPin,OUTPUT);                                                         //设置LED针脚

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
  dataFile.print("TDS");                                                        //在文件中输入首行各项“TDS”及“BLABLA”  通过 ", " 分隔
  dataFile.print(",");
  dataFile.println("BLABLA");
  dataFile.close();
  
}

void loop() {
  int value;                                                                    //设定变量获取TDS传感器读取到值

  value=tdssensing();

  if(value>=200){                                                               //判断，当TDS传感器读数大于200时点亮LED否则熄灭,延时1s
  digitalWrite(LEDPin, HIGH);
  //delay(1000);
}else{
  digitalWrite(LEDPin, LOW);
  //delay(1000);
}

  
  // make a string for assembling the data to log:
  String dataString = "";

  dataString += String(value);                                                     //向String类型变量写入数据，数据间用 ", " 分隔

  dataString += ",";

  dataString += String("lalala");

//************************************************************
/*
  static unsigned int value = 0;
  value = random(0,100);
  
  // read three sensors and append to the string:
  for (int i = 0; i < 3; i++) {
    dataString += String(value);
    if (i < 2) {
      dataString += ",";
    }
  }
*/
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




int getMedianNum(int bArray[], int iFilterLen) 
{
      int bTab[iFilterLen];
      for (byte i = 0; i<iFilterLen; i++)
    bTab[i] = bArray[i];
      int i, j, bTemp;
      for (j = 0; j < iFilterLen - 1; j++) 
      {
    for (i = 0; i < iFilterLen - j - 1; i++) 
          {
      if (bTab[i] > bTab[i + 1]) 
            {
    bTemp = bTab[i];
          bTab[i] = bTab[i + 1];
    bTab[i + 1] = bTemp;
       }
    }
      }
      if ((iFilterLen & 1) > 0)
  bTemp = bTab[(iFilterLen - 1) / 2];
      else
  bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
      return bTemp;
}


int tdssensing(){
  static unsigned long analogSampleTimepoint = millis();
   if(millis()-analogSampleTimepoint > 40U)     //every 40 milliseconds,read the analog value from the ADC
   {
     analogSampleTimepoint = millis();
     analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);    //read the analog value and store into the buffer
     analogBufferIndex++;
     if(analogBufferIndex == SCOUNT) 
         analogBufferIndex = 0;
   }   
   static unsigned long printTimepoint = millis();
   if(millis()-printTimepoint > 800U)
   {
      printTimepoint = millis();
      for(copyIndex=0;copyIndex<SCOUNT;copyIndex++)
        analogBufferTemp[copyIndex]= analogBuffer[copyIndex];
      averageVoltage = getMedianNum(analogBufferTemp,SCOUNT) * (float)VREF / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
      float compensationCoefficient=1.0+0.02*(temperature-25.0);    //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
      float compensationVolatge=averageVoltage/compensationCoefficient;  //temperature compensation
      tdsValue=(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 255.86*compensationVolatge*compensationVolatge + 857.39*compensationVolatge)*0.5; //convert voltage value to tds value
      return tdsValue;
  }
}


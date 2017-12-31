#include "GravityRtc.h"
#include "Wire.h"  

GravityRtc rtc;     //RTC Initialization//初始化 新建GravityRtc类的rtc对象

void setup() {
  Serial.begin(9600);
  rtc.setup();

  //rtc.initRtc(2017,12,30,6,12,7,0);  //设置时间;2017/12/30，周六，12点07分0秒
  //设置完时间后，请注释掉此行，以保证下次启动时，不会重置时间！！！！！！！

}

void loop() {
  rtc.update();
  //*************************Time********************************
  Serial.print("   Year = ");//year
  Serial.print(rtc.year);
  Serial.print("   Month = ");//month
  Serial.print(rtc.month);
  Serial.print("   Day = ");//day
  Serial.print(rtc.day);
  Serial.print("   Week = ");//week
  Serial.print(rtc.week);
  Serial.print("   Hour = ");//hour
  Serial.print(rtc.hour);
  Serial.print("   Minute = ");//minute
  Serial.print(rtc.minute);
  Serial.print("   Second = ");//second
  Serial.println(rtc.second);
  delay(1000);

}
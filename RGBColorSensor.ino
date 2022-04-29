#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <swRTC.h>
swRTC rtc;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  rtc.stopRTC();
  rtc.setTime(0,0,0);
  rtc.setDate(4,28,2022);
  rtc.startRTC();
  Serial.begin(9600);
}

void loop() {
    uint16_t r, g, b, c, colorTemp, lux;
    
    tcs.getRawData(&r, &g, &b, &c);
    colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c); // 색온도
    lux = tcs.calculateLux(r, g, b); // 조도

    Serial.print(rtc.getHours(),DEC);
    Serial.print(":");
    Serial.print(rtc.getMinutes(),DEC);
    Serial.print(":");
    Serial.print(rtc.getSeconds(),DEC);
    Serial.print("   ");
    Serial.print("CCT: "); Serial.print(colorTemp, DEC);
    Serial.print(" K   ");
    Serial.print("Lux: "); Serial.print(lux, DEC);
    Serial.print("   R: "); Serial.print(r);
    Serial.print("   G: "); Serial.print(g);
    Serial.print("   B: "); Serial.print(b);
    Serial.println(); 
    delay(1000);
}

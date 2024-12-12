#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

// display connected to the HW I2C (this is the best option)
U8G2_SH1107_SEEED_128X128_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
//U8G2_SH1107_SEEED_128X128_F_SW_I2C u8g2(U8G2_R0, /* clock SCL GUL=*/ 19, /* data SDA VIT=*/ 18, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  u8g2.begin();
}

void loop(void) {
  u8g2.clearBuffer();                 // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB12_tr); // choose a suitable font and size
  u8g2.drawStr(0,14,"Hello World!");  // write something to the internal memory
  u8g2.sendBuffer();                  // transfer internal memory to the display
  delay(1000);  
}
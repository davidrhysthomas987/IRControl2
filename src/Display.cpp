#include <Arduino.h>
#include "arduinoGlue.h" 

void midText(char title[]){
 u8g2.clearBuffer();         // clear the internal memory
 u8g2.setFont(u8g2_font_fub35_tr); // choose a suitable font
  //u8g2.setFont(u8g2_font_inb38_mn); // choose a suitable font
  u8g2.drawStr(0,62,title); // write something to the internal memory
  u8g2.sendBuffer();          // transfer internal memory to the display
 
}
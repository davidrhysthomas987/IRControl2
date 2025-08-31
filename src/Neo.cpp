#include "Neo.h"
Adafruit_NeoPixel pixels(NUMPIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);
void allRed(){
   for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    pixels.setPixelColor(i, pixels.Color(100,0,0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    
  }
}

void allYellow(){
   for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    pixels.setPixelColor(i, pixels.Color(20,20,0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    
  }
}
void posOK(int pos){
    pixels.clear(); // Set all pixel colors to 'off'
    pixels.setPixelColor(pos, pixels.Color(0,150,0));
    pixels.show();   // Send the updated pixel colors to the hardware.
 
}
void moveing(int st, int fin){
 
   for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

   // pixels.setPixelColor(i, pixels.Color(20,20,20));
     //pixels.show();   // Send the updated pixel colors to the hardware.
      
  }
  pixels.setPixelColor(st, pixels.Color(150,0,0));
  pixels.setPixelColor(fin, pixels.Color(0,0,150));
  pixels.show();   // Send the updated pixel colors to the hardware.
}
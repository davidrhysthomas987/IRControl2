#include "INOUTBits.h"

void setout(int outvalue){
  //set four bits of the port ro the current value of Traverser anyother value but 0-9 sets all off

  if (outvalue >= 0 && outvalue <= 9){
     digitalWrite(OUTP0, (outvalue & 1) ? HIGH : LOW); 
     digitalWrite(OUTP1, (outvalue & (1 << 1)) ? HIGH : LOW); 
     digitalWrite(OUTP2, (outvalue & (1 << 2)) ? HIGH : LOW); 
     digitalWrite(OUTP3, (outvalue & (1 << 3)) ? HIGH : LOW); 
  }else{
    digitalWrite(OUTP0,HIGH);
    digitalWrite(OUTP1,HIGH);
    digitalWrite(OUTP2,HIGH);
    digitalWrite(OUTP3,HIGH);
  }
  
}

void getinSetting(){

  //Input 1-10 binary 0 is not used
  //  12 emergency stop
  //  13 reset travserer
 if (digitalRead(INCONTROL)){  //A valid change in traverser position
        uint8_t result;
        result = 0;
        delay(300);
        //Input 1-10 binary 0 is not used
        //  12 emergency stop
        //  13 reset travserer
      do {
      }while(digitalRead(INCONTROL)==true); 
        result = digitalRead(INP0) + (digitalRead(INP1)<<1) + (digitalRead(INP2)<<2) + (digitalRead(INP3)<<3);
        Serial.print("CBUSIN ");
        Serial.println(result);
        //if result is the same as current value do nothing
        if (result == currentPos){
          return;
        }
         if (result >= 0 & result <=9){
                 Serial.println(result);
                movePos(result);
              }
        if (result == 12){
                ESTOP = true;  
                midText("*E*");
                
        }
        if (result == 13){
          calibrateTable();
        }
  }
}
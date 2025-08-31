#include "Inputs.h"
void EstopTest(){
  //Emergency stop check both endstops and abort any movement
      if (digitalRead(mswitchA)==LOW||digitalRead(mswitchB)==LOW||digitalRead(ESTOPPin)==LOW){
        //stop traverser and signal error
         #if DEBUG
            Serial.println("ESTop");
          #endif
           txtoled[0]='*';
  txtoled[1]=('E');
  txtoled[2]='*';
  midText(txtoled);
          ESTOP = true;
       
      }
     
}

void EstopDisplay(){
    txtoled[0]='*';
  txtoled[1]=('E');
  txtoled[2]='*';
  midText(txtoled);
    allRed();
}
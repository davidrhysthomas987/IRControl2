#include "Serial.h"
void processSerial(){
  int valString = Serial.read();
    //Serial.println(valString);
    switch (valString) {
        case 97:  //a
         moveTable(trackJump,currentSpd,true);
         break;
       case 115:  //s
         moveTable(trackJump,currentSpd,false);
         break; 
       case 105:  //i  
         moveTable(5,currentSpd,true);
         break;    
       case 117:  //u  
         moveTable(20,currentSpd,true);
         break;
       case 112:  //p
         moveTable(20,currentSpd,false);
         break;    
       case 111:  //0  
         moveTable(5,currentSpd,false);
         break;
               
       case 122:  //z
         calibrateTable();
         break;
       default:
        if (valString > 47 && valString < 58){
           Serial.println(valString);
          movePos(valString - 48);
        }
        
}
}
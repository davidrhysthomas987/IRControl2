#include "IR.h"

int keys[]={25,69,70,71,68,64,67,7,21,9};
void processIR(int IRIN){
 
    switch (IRIN) {
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
               
       case 28:  //z
         calibrateTable();
         break;
       default:
       //Process input to get number 0-9
       for (int n=0; n<10;n++){
        if (keys[n] == IRIN){
          IRIN = n;
          exit;
        }
       }
        if (IRIN >= 0 & IRIN <=9){
           Serial.println(IRIN);
          movePos(IRIN);
        }
        
}

}
#include "STEPS.h"

void moveTable(int TurnNum,int TurnSpeed, boolean TurnDir){
       // Set the spinning direction clockwise:
      if (TurnDir == true){  //Forward
            //Do we need extra steps for backlash
            if (lastDir == 2) TurnNum = TurnNum + backlashFor;
            digitalWrite(dirPin, HIGH);
            lastDir =1;
      }else{  //Reverse
        //Do we need extra steps for backlash
            if (lastDir == 1) TurnNum = TurnNum + backlashRev;
            lastDir =2;
            digitalWrite(dirPin, LOW);
      }
      //digitalWrite(sleepPin, 1);
      
      for (int i = 0; i < TurnNum; i++) {
        // These four lines result in 1 step:
          onestep(TurnSpeed);
          if (ESTOP == true){
           
            break;
           }
      }
      //digitalWrite(sleepPin, 0);
      
    }

    void moveTable2(int TurnNum,int TurnSpeed, boolean TurnDir){
       // Calibrate with no estop function:
      if (TurnDir == true){  //Forward
            //Do we need extra steps for backlash
            if (lastDir == 2) TurnNum = TurnNum + backlashFor;
            digitalWrite(dirPin, HIGH);
            lastDir =1;
      }else{  //Reverse
        //Do we need extra steps for backlash
            if (lastDir == 1) TurnNum = TurnNum + backlashRev;
            lastDir =2;
            digitalWrite(dirPin, LOW);
      }
      //digitalWrite(sleepPin, 1);
      
      for (int i = 0; i < TurnNum; i++) {
        // These four lines result in 1 step:
          onestepNoE(TurnSpeed);
          
      }
      //digitalWrite(sleepPin, 0);
      
    }
 

 void onestep(int speed){

 //just move one step
   // These four lines result in 1 step:
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(speed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(speed);
        EstopTest();
 }

void onestepNoE(int speed){

 //just move one step
   // These four lines result in 1 step:
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(speed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(speed);
        //EstopTest();
 }
 
 void calibrateTable(){
  //calibrate the table
  //Move forward to sensor then align and set counter = 0

  
   //Check microswitch is not on
  //Move backwards until microswitch trips
  //Move slowly forwatd until microswitch releases
  //Move to base position
  detachInterrupt(mswitchA);  //stop interupt
   ESTOP = false;  //clear the stop otherwise nothing will move
   allYellow();                  
   setout(15);
  txtoled[0]='*';
  txtoled[1]=('C');
  txtoled[2]='*';
  midText(txtoled);
  do
  {
    //Not at microswitch point yet
    moveTable2(5,currentSpd,REVERSE);
    
  }while (digitalRead(mswitchA)==HIGH);
  //Switch closed
  do
  {
    //Not at microswitch point yet
    moveTable2(5,currentSpd,FORWARD);
    
  }while (digitalRead(mswitchA)==LOW);
  //At set point
  //Move to start point
  moveTable(stepsToZero,currentSpd,FORWARD);
  currentPos = 0;  //start pos
  setout(currentPos);txtoled[0]='<';
  txtoled[1]=(currentPos+48);
  txtoled[2]='>';
  midText(txtoled);
  posOK(currentPos);
  attachInterrupt(mswitchA,EstopInt,FALLING);  //reattach interupt
 
}

void movePos(int target){
  //move table to selected position
  int moveNo;
  if (target < 0 || target >maxPositions) return;  //invalid selection
  if (target == currentPos) return;  //invalid selection
  //Inform CBUS sensors position is not valid
  setout(15);
txtoled[0]='*';
  txtoled[1]=('W');
  txtoled[2]='*';
  midText(txtoled);
  moveing(currentPos,target);
  if (target < currentPos){
      moveNo = currentPos -target;
      for (int n=0; n<moveNo; n++){
           moveTable(trackJump,currentSpd,false);
           if (ESTOP == true){
             break;
           }
      }
         
  }else{
      moveNo = target- currentPos;
      for (int n=0; n<moveNo; n++){
          moveTable(trackJump,currentSpd,true);
          if (ESTOP == true) break;
      }
  }
  currentPos = target;
  setout(target);
  txtoled[0]='<';
  txtoled[1]=(currentPos+48);
  txtoled[2]='>';
  midText(txtoled);
  posOK(currentPos);
  
  
}
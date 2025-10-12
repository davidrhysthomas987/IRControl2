#include <Arduino.h>
#include "arduinoGlue.h"
//#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp> // include the library
//include <SPI.h>                                  		//-- moved to arduinoGlue.h

//#include <Wire.h>                                 		//-- moved to arduinoGlue.h

//#include <U8g2lib.h>                              		//-- moved to arduinoGlue.h
//#include <Adafruit_NeoPixel.h>                    		//-- moved to arduinoGlue.h
//#include <Preferences.h>                          		//-- moved to arduinoGlue.h

//Preferences preferences;


   
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of th


 bool   FORWARD;                           		//-- from IRControl2
 bool   REVERSE;                           		//-- from IRControl2
 int          currentPos;                        		//-- from IRControl2
 int          currentSpd;                        		//-- from IRControl2
 int          lastDir;                           		//-- from IRControl2
 int          maxPositions;                      		//-- from IRControl2

//extern Adafruit_NeoPixel pixels;                            		//-- from IRControl2
 Preferences     preferences;                       		//-- from IRControl2
 bool            runFlag;                           		//-- from IRControl2
 int             stepsPerClick;                     		//-- from IRControl2
                         		//-- from IRControl2
//extern U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2;                              		//-- from IRControl2
 unsigned int stepsToZeroBase = 322;  //move from calibration point to centre
 unsigned int trackJumpBase = 647;   //move between tracks
 unsigned int stepsToZero;  //move from calibration point to centre
 unsigned int trackJump;   //move between tracks
 int targetPos = 0;    // where do we want to go

 bool tpos;  //position of traverser
 int turns = 1000;  //to move 26,5mm

 boolean ESTOP;   //flag to record Emergency stop condition   

    //flag to say we are in run or calibrate
 char txtoled[3];
   

    

void IRAM_ATTR EstopInt(){
  //Emergency stop button abort any movement
        //stop traverser and signal error
        
            ESTOP = true;
            
               
            
}
void setup() {
     Serial.begin(115200);
       while (!Serial) {
     // wait for serial port to connect. Needed for native USB port only
      }
  Wire.begin( );

    FORWARD = true;
    REVERSE = false;
    //stepsToZeroBase = 322;  //move from calibration point to centre
    
    stepsToZero = stepsToZeroBase;  //move from calibration point to centre
    trackJump = trackJumpBase;   //move between tracks

    //Positioanl info
    
    // targetPos = 0;    // where do we want to go
     currentPos = 0;   //where is the Traverser now 0 = not known
     maxPositions = 9;  //number of stops on the turntable
     stepsPerClick = 1;
     tpos = false;  //position of traverser
     lastDir = 0;  //last direction moved 1= forward 2= reverse 0 =unkown
   

    ESTOP = false;   //flag to record Emergency stop condition   
    //IrReceiver.begin(irReceiverPin, ENABLE_LED_FEEDBACK);
    //flag to say we are in run or calibrate
    runFlag = true;  //true = run false = calibrate
    currentSpd = fastSpd;  //setup speed used later
    
  // Declare pins as output:
      pinMode(stepPin, OUTPUT);
      pinMode(dirPin, OUTPUT);
      pinMode(ESTOPPin,INPUT_PULLUP); 
      pinMode(mswitchA, INPUT_PULLUP);
      pinMode(mswitchB, INPUT_PULLUP);
          
   //attachInterrupt(ESTOPPin,EstopInt,FALLING);  //  
   //attachInterrupt(mswitchA,EstopInt,FALLING);  //
   //attachInterrupt(mswitchB,EstopInt,FALLING);  //  
  //Setup in out control pins
   pinMode(OUTP0, OUTPUT);
   pinMode(OUTP1, OUTPUT);
   pinMode(OUTP2, OUTPUT);
   pinMode(OUTP3, OUTPUT);

   pinMode(INP0,INPUT);
   pinMode(INP1,INPUT);
   pinMode(INP2,INPUT);
   pinMode(INP3,INPUT);
   pinMode(INCONTROL,INPUT);
   u8g2.begin();
   IrReceiver.begin(irReceiverPin , ENABLE_LED_FEEDBACK);  

   //Reterived stored values
   // preferences.begin("store", false);
   // trackJump = preferences.getUInt("trackJump",0);
   // if(trackJump == 0) trackJump = trackJumpBase;
   //stepsToZero = preferences.getUInt("stepsToZero",0);
   // if(stepsToZero == 0) stepsToZero = stepsToZeroBase;
   // preferences.end();
         Serial.println("Ready");
        
 

  //Reset beam to 0
  txtoled[0]='*';
  txtoled[1]=('S');
  txtoled[2]='*';
  midText(txtoled);
  // midText("*S*");
  
 
}

void loop() {
  int IRinput;
  processSerial();
  //getinSetting();
  if (ESTOP==true) EstopDisplay();
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
            // We have an unknown protocol here, print extended info
            //IrReceiver.printIRResultRawFormatted(&Serial, true);

            IrReceiver.resume(); // Do it here, to preserve raw data for printing with printIRResultRawFormatted()
        } else {
            IrReceiver.resume(); // Early enable receiving of the next IR frame
             IRinput = IrReceiver.decodedIRData.command;
            Serial.println(IRinput);
            processIR(IRinput);       
            //IrReceiver.printIRResultShort(&Serial);
            //IrReceiver.printIRSendUsage(&Serial);
        }
        Serial.println();     
       
       // Serial.println(IRinput);
        //processIR(IRinput);
       // IrReceiver.resume();
  }
}
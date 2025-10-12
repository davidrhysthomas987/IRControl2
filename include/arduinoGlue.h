#ifndef ARDUINOGLUE_H
#define ARDUINOGLUE_H


//============ Includes ====================
#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <Adafruit_NeoPixel.h>
#include <IRremote.hpp>
#include <Preferences.h>

//============ Defines & Macros====================
#define NEO_PIN 18 //
#define NUMPIXELS 14 
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels 

#define DEBUG   1 // set to 0 for no debug messages, 1 for messages to console
#define dirPin 17
#define stepPin 16
#define Spdmin 100
#define Spdmax 2000
#define slowSpd 3000
#define fastSpd 1200
#define slopeSpd 600   //number of steps from start to top speed

#define INP0  36
#define INP1  39
#define INP2  34
#define INP3  32
#define INCONTROL 19
#define OUTP0  12
#define OUTP1  13
#define OUTP2  27
#define OUTP3  14
#define irReceiverPin  4
#define mswitchA  26
#define mswitchB  33
#define ESTOPPin  25     // the number of the pushbutton pin plus

#define backlashRev 0  //allow for extra steps when changing direction
#define backlashFor 0

 //============ Extern Variables ============

 extern U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2;   // All Boards without Reset of th

   
                             		//-- from IRControl2
extern  bool   FORWARD;                           		//-- from IRControl2
extern  bool   REVERSE;                           		//-- from IRControl2
extern int          currentPos;                        		//-- from IRControl2
extern int          currentSpd;                        		//-- from IRControl2
extern int          lastDir;                           		//-- from IRControl2
extern int          maxPositions;                      		//-- from IRControl2

//extern Adafruit_NeoPixel pixels;                            		//-- from IRControl2
extern Preferences     preferences;                       		//-- from IRControl2
extern bool            runFlag;                           		//-- from IRControl2
extern int             stepsPerClick;                     		//-- from IRControl2
extern int             targetPos;                         		//-- from IRControl2
extern int             threshold;                         		//-- from IRControl2
extern bool            tpos;                              		//-- from IRControl2
extern int             turns;                             		//-- from IRControl2
//extern U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2;                              		//-- from IRControl2
extern unsigned int stepsToZeroBase;  //move from calibration point to centre
extern unsigned int trackJumpBase;   //move between tracks
extern unsigned int stepsToZero;  //move from calibration point to centre
extern unsigned int trackJump;   //move between tracks


extern boolean ESTOP;   //flag to record Emergency stop condition   

    //flag to say we are in run or calibrate
extern char txtoled[3];
//============ Function Prototypes =========
//-- from Display.ino -----------
void midText(char title[]);                                 
//-- from INOUTBits.ino -----------
void setout(int outvalue);                                  
void getinSetting();                                        
//-- from Inputs.ino -----------
void EstopTest();                                           
void EstopDisplay();                                        
//-- from IR.ino -----------
void processIR(int IRIN);                                   
//-- from IRControl2.ino -----------
void IRAM_ATTR EstopInt();                                  
//-- from Neo.ino -----------
void allRed();                                              
void allYellow();                                           
void posOK(int pos);                                        
void moveing(int st, int fin);                              
//-- from Serial.ino -----------
void processSerial();                                       
//-- from STEPS.ino -----------
void moveTable(int TurnNum,int TurnSpeed, boolean TurnDir); 
void moveTable2(int TurnNum,int TurnSpeed, boolean TurnDir);
void onestep(int speed);                                    
void onestepNoE(int speed);                                 
void calibrateTable();                                      
void movePos(int target);                                   

#endif // ARDUINOGLUE_H

/*
This script was created by Bob Clagett for I Like To Make Stuff
For more projects, check out iliketomakestuff.com

Parts of this sketch were taken from the keypad and servo sample sketches that comes with the keypad and servo libraries.
*/


#include <ctype.h>
#include <Servo.h>
#include <Keypad.h>

const byte servoCount = 6;
const int OPEN_ALL = 100;
const int CLOSE_ALL = 99;
const int openPos = 120;
const int closedPos = 50;

static Servo servoList[servoCount];

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
// Define the keymaps.  The blank spot (lower left) is the space character.
char numberKeys[ROWS][COLS] = {
  { '1','2','3','A'}
  ,
  { '4','5','6','B'}
  ,
  { '7','8','9','C'}
  ,
  { '*','0','#','D'}
};

byte rowPins[ROWS] = { 8,7,6,5 };
byte colPins[COLS] = { 12,11,10,9 }; 


// Create a new keypad
Keypad numpad( makeKeymap(numberKeys), rowPins, colPins, sizeof(rowPins), sizeof(colPins) );

const byte ledPin = 13;                            // Use the LED on pin 13.

void setup() {
  Serial.begin(9600);
  pinMode(5,INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  
  numpad.begin( makeKeymap(numberKeys) );
  numpad.addEventListener(keypadEvent_num);  // Add an event listener.
  numpad.setHoldTime(500);                   // Default is 1000mS
  
  servoList[0].attach(A0);
  servoList[1].attach(A1);
  servoList[2].attach(A2);
  servoList[3].attach(A3);
  servoList[4].attach(A4);
  servoList[5].attach(A5);
  
 setServoState(CLOSE_ALL); //reset all servos
}

char key;
static char virtKey = NO_KEY;      // Stores the last virtual key press. (Alpha keys only)
static char physKey = NO_KEY;      // Stores the last physical key press. (Alpha keys only)
static char buildStr[12];
static byte buildCount;
static byte pressCount;
static byte kpadState;

void loop() {
  key = numpad.getKey( );
}

// Take care of some special events.
void setServoState(char number) {
  int thisServ = 0;
  int val;
  boolean ignoreAll = false;
  switch (number){
  case '1':
    val = 0;
    break;
  case '2':
    val = 1;
    break;
  case '3':
    val = 2;
    break;
  case '4':
    val = 3;
    break;
  case '5':
    val = 4;
    break;
  case '6':
    val = 5;
    break;
  case '7':
  case '8':
  case '9':
    ignoreAll = true;
    break;
  default:
    val=number;
    break;
  }
  if(!ignoreAll){
    for(thisServ = 0; thisServ < servoCount; thisServ += 1){
      int newPos = 0;
      if(thisServ == val or val == OPEN_ALL){
        newPos = openPos;
      } 
      else {
        newPos = closedPos;
      }
      servoList[thisServ].write(newPos);
    }
  }
}

void keypadEvent_num( KeypadEvent key ) {
  // in here when using number keypad
  kpadState = numpad.getState();
  swOnState( key );

} // end numbers keypad events

void swOnState( char key ) {
  Serial.print("key = ");
  Serial.print(key);
  Serial.println();

  switch( kpadState ) {
  case PRESSED:

    if (isdigit(key) || key == ' ' || key == '.'){
      setServoState(key);
    }
    if (key == '#') {
      Serial.print("CLOSE ALL");
      Serial.println();
      setServoState(CLOSE_ALL);
    }
    if (key == '*') {
      Serial.print("OPEN ALL");
      Serial.println();
      setServoState(OPEN_ALL);
    }
    break;
 // case HOLD:
 //   if (key == '#')  {               // Toggle between keymaps.
 //   }
 //   else  {                          // Some key other than '#' was pressed.

 //   }
 //   break;

  case RELEASED:
    break;
  }  // end switch-case
}// end switch on state function




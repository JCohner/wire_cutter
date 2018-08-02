#include <PinChangeInt.h>
#include <Keypad.h>
#include <Wire.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {11, 10, 9, 8}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad myKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
  pinMode(7,INPUT);
  pinMode(6,INPUT);
  pinMode(5,INPUT);
  pinMode(4,INPUT);
  pinMode(11,INPUT);
  pinMode(10,INPUT);
  pinMode(9,INPUT);
  pinMode(8,INPUT);

  Wire.begin();
}

char stateKey;
char stateKey_prev;
char numKey; 
char state = '0'; 
void loop(){
  stateKey = myKeypad.getKey();
  switch (state){ 
    /*State chnage case*/
    case '0':
      if (stateKey){
        Serial.print("State: ");
        Serial.println(stateKey);
        stateKey_prev = stateKey;
        Wire.beginTransmission(8);
        Wire.write(stateKey);
        Wire.endTransmission(1);
      }
      break;
  }
}


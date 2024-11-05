#include "Keyboard.h" 
#include <Encoder.h>

int longPressDelay = 350;           //customizable keyboard values
int spamSpeed = 15;

byte inputs[] = {18,19,20,21};
#define inCount sizeof(inputs)/sizeof(inputs[0])
byte outputs[] = {10,16,14,15};
#define outCount sizeof(outputs)/sizeof(outputs[0])

char layout[outCount][inCount] = {               //layout grid for characters (adjust if your grid is not 4x4)
  {'/','*','+','-'},
  {'9','6','3',176}, //176 is for return or enter
  {'8','5','2','0'},
  {'7','4','1','.'},
};

int keyDown[outCount][inCount];
bool keyLong[outCount][inCount]; 

Encoder knobLeft(7, 8);
Encoder knobRight(1, 0);
long positionLeft  = -999;
long positionRight = -999;

void setup(){
  
  for(int i=0; i<outCount; i++){    //declaring all the outputs and setting them high
    pinMode(outputs[i],OUTPUT);
    digitalWrite(outputs[i],HIGH);
  }
  for(int i=0; i<inCount; i++){     //declaring all the inputs and activating the internal pullup resistor
    pinMode(inputs[i],INPUT_PULLUP);
  }
  
  Serial.begin(9600);               //establishing Serial link and initializing keyboard
  Serial.println("Connected");
  Keyboard.begin();
  
}

//Main loop going through all the keys, then waiting 0.5ms
void loop() {
  for (int i=0; i<outCount; i++)
  {    
    digitalWrite(outputs[i],LOW);   //setting one row low
    delayMicroseconds(5);           //giving electronics time to settle down
    
    for(int j=0; j<inCount; j++)
    {
      if(digitalRead(inputs[j]) == LOW)
      {
        keyPressed(i,j);            //calling keyPressed function if one of the inputs reads low
      }
      else if(keyDown[i][j] != 0)   //resetting the key if it is not pressed any more
      {  
        resetKey(i,j);
      }
    }
    
    digitalWrite(outputs[i],HIGH);
    delayMicroseconds(500);         //setting the row high and waiting 0.5ms until next cycle
  }
  long newLeft, newRight;
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  if (newLeft != positionLeft || newRight != positionRight) {
    Serial.print("Left = ");
    Serial.print(newLeft);
    Serial.print(", Right = ");
    Serial.print(newRight);
    Serial.println();
    positionLeft = newLeft;
    positionRight = newRight;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    knobLeft.write(0);
    knobRight.write(0);
  }
  
}

//if a key is pressed, this Funtion is called and outputs to serial the key location, it also sends the keystroke if not already done so
void keyPressed(int row, int col){
  Serial.print("Output: "); 
  Serial.print(row);
  Serial.print(" Input: ");
  Serial.print(col);
  Serial.print(" ");
  Serial.println(layout[row][col]);

  if(keyDown[row][col]==0){         //if the function is called for the first time for this key
    Keyboard.write(layout[row][col]);
  }
  else if(keyLong[row][col] && keyDown[row][col] > spamSpeed){ //if the key has been held long enough to warrant another keystroke set
    Keyboard.write(layout[row][col]);
    keyDown[row][col] = 1;
  }
  else if(keyDown[row][col] > longPressDelay){ //if the key has been held for longer that longPressDelay, it switches into spam mode
    keyLong[row][col] = true;
  }

  keyDown[row][col]++;
}

void resetKey(int row, int col){ //resetting the variables after key is released
  keyDown[row][col] = 0;
  keyLong[row][col] = false;
}

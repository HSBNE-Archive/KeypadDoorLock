//////////////////////////////////////////////////////////////////
// update by Wizard^^ for Telecom Public Phone Keypad
//©2011 bildr
//Released under the MIT License - Please reuse change and share
//Password for Arduino applications.
//Make sure you've installed the two libraries below (with link).
//Configured for the Sparkfun keypad (3x4)
//* is to validate password   
//# is to reset password attempt
//Credits to Alexander Brevig & Alexander Brevig
/////////////////////////////////////////////////////////////////

#include <Password.h> //http://www.arduino.cc/playground/uploads/Code/Password.zip
#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip

Password password = Password( "****" ); //no peeking

const byte ROWS = 4; // Four rows
const byte COLS = 3; //  columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

// Normal Keypad
// byte rowPins[ROWS] = { 5, 4, 3, 2 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
// byte colPins[COLS] = { 8, 7, 6 };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
// Telecom Public Phone Keypad
byte rowPins[ROWS] = { 5, 4, 2, 6, };
byte colPins[COLS] = { 7, 8, 3 };


// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){

  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}

void loop(){
  keypad.getKey();
}

//take care of some special events
void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
    case PRESSED:
    Serial.print("Pressed: ");
    Serial.println(eKey);
    switch (eKey){
      case '#': checkPassword(); break;
      case '*': password.reset(); break;
      default: password.append(eKey);
     }
  }
}

void checkPassword(){
  if (password.evaluate()){
    Serial.println("Success"); //Add code to run if it works
     digitalWrite(11, LOW);
     digitalWrite(10, HIGH);
  }else{
    Serial.println("Wrong"); //add code to run if it did not work
     digitalWrite(10, LOW);
     digitalWrite(11, HIGH);
  }
  delay(2000); // wait for a second
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  password.reset();
}

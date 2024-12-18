#include <Keypad.h>
#include <Servo.h>


      //***************Keypad**********************///

const byte ROWS = 4; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

// pins for the black keyboard
byte rowPins[ROWS] = {5, 6, 7, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2, 3, 4}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
 
      //***************Servo**********************///

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position


      //***************PASSWORD**********************///

const String password = "123"; // change your password here
String input_password;

void setup() {
  Serial.begin(9600);

  myservo.attach(9);


  input_password.reserve(32); // maximum input characters is 33, change if needed
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
    input_password += key; // append new character to input password string

   //  if (input_password.length() == password.length()) {
   //   if (password == input_password) {
     
     if(key == '*'){
        Serial.println("password is correct");
        // DO YOUR WORK HERE
       // unlockServo();
       myservo.write(180);
      
      } else if (key == '#'){
        Serial.println("password is incorrect, try again");
         myservo.write(0);
      }
      input_password = ""; // clear input password

    }
  
  delay(100);
}


void unlockServo(){
   for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
   // in steps of 1 degree
   myservo.write(pos);              // tell servo to go to position in variable 'pos'
   delay(15);                       // waits 15ms for the servo to reach the position
 }
}

void lockServo(){
 for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
   // in steps of 1 degree
   myservo.write(pos);              // tell servo to go to position in variable 'pos'
   delay(15);                       // waits 15ms for the servo to reach the position
 }
}
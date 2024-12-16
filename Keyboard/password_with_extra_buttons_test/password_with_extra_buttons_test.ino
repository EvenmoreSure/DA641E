#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

// pins for the BLACK keyboard
byte rowPins[ROWS] = {5, 6, 7, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2, 3, 4}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


const String password = "123"; // change your password here
String input_password;

void setup() {
  Serial.begin(9600);
  input_password.reserve(32); // maximum input characters is 33, change if needed

}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);

    if (key == '*') {
      input_password = ""; // clear input password
      Serial.println("password cleared");

    }else
      if (key == '#') {
        if (password == input_password) {
          Serial.println("password is correct");
          // DO YOUR WORK HERE

        } else {
                  Serial.println(input_password);

          Serial.println("password is incorrect, try again");

        }
        input_password = ""; // clear input password

      } else {
          input_password += key; // append new character to input password string
    }

  }
  delay(100);
}
#include <Keypad.h>
#include <Servo.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

//***************Keypad**********************///

const byte ROWS = 4;
const byte COLS = 3;

char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

// pins for the black keyboard
byte rowPins[ROWS] = { 5, 6, 7, 8 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 2, 3, 4 };     //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//***************Servo**********************///

Servo myservo;  // create servo object to control a servo

int pos = 0;  // variable to store the servo position

//***************DISPLAY**********************///
U8G2_SH1107_SEEED_128X128_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);


//***************PASSWORD**********************///

const String password = "123";  // change your password here
String input_password;

//************************STATE****************//
enum DOORSTATE { LOCKED,
                 UNLOCKED };
DOORSTATE currentDoorState;

long lastUpdate;

void setup() {
  Serial.begin(9600);

  myservo.attach(9);

  u8g2.begin();

  input_password.reserve(32);  // maximum input characters is 33, change if needed

  writeTextToDisplay("Write pincode");
  currentDoorState = LOCKED;
  lastUpdate = millis();
}

void loop() {
  //if (millis() - lastUpdate > 100) {
   // lastUpdate = millis();
    char key = keypad.getKey();

    if (key) {
      Serial.println(key);
      input_password += key;  // append new character to input password string

      // update screen with new length of pincode
      if (input_password.length() > 0) {
        writeTextToDisplay(passwordToStars(input_password));
      }
      if (input_password.length() == password.length()) {  // will automatically check password if the correct length
        if (password == input_password) {
          Serial.println("password is correct");
          writeTextToDisplay("Welcome");
          unlockServo();

        } else {
          delay(1500);
          Serial.println("password is incorrect, try again");
          input_password = "";  // clear input password
          writeTextToDisplay("Wrong pincode");
          delay(5000);
          writeTextToDisplay("Write pincode");
        }
      }
    }

    if (currentDoorState == UNLOCKED) {
      // add handle for WHEN we want to lock the door again
      // should it just be a delay and then lock?
      delay(15000);
      lockServo();
      input_password = "";
    }
 // }
   delay(100); // Necessary delay for keypad to work.
}


void unlockServo() {
  for (pos = 0; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees
                                         // in steps of 1 degree
    myservo.write(pos);                  // tell servo to go to position in variable 'pos'
    delay(15);                           // waits 15ms for the servo to reach the position
  }
  currentDoorState = UNLOCKED;
}

void lockServo() {
  for (pos = 180; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
    // in steps of 1 degree
    myservo.write(pos);  // tell servo to go to position in variable 'pos'
    delay(15);           // waits 15ms for the servo to reach the position
  }
  currentDoorState = LOCKED;
}

char* passwordToStars(String psw) {
  int len = psw.length();
  char* newPassword;
  if (len == 1) {
    newPassword = "x";
  } else if (len == 2) {
    newPassword = "xx";
  } else if (len == 3) {
    newPassword = "xxx";
  } else {
    newPassword = "Write pincode";
  }
  return newPassword;
}

void writeTextToDisplay(char* text) {
  u8g2.clearBuffer();                  // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB12_tr);  // choose a suitable font and size
  u8g2.drawStr(0, 14, text);           // write something to the internal memory
  u8g2.sendBuffer();                   // transfer internal memory to the display
}
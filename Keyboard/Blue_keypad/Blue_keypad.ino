#include <Keypad.h> // Include the Keypad library


const byte ROWS = 4; // Number of rows, connect to the number od the rows
const byte COLS = 3; // Number of columns, connect to the colunm pinouts of the the keypad


byte rows[ROWS] = {9, 8, 7, 6}; // Connect to the row pinouts of the keypad
byte cols[COLS] = {5, 4, 3}; // Connect to the column pinouts of the keypad


char keys[ROWS][COLS] = { // Create 2D array for keys
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};


Keypad mykeypad = Keypad(makeKeymap(keys), rows, cols, ROWS, COLS);


void setup() {
  Serial.begin(9600); // Enable serial monitor
}


void loop() {
  char myKey = mykeypad.getKey(); // Get key and put it into the variable
  if (myKey) { // Check if a key is pressed
    Serial.println(myKey); // Print the key  
  }
  delay(100);
}

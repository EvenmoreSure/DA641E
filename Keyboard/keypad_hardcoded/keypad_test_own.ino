// Pins
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#define PIN8 8




void setup() {
 Serial.begin(115200);


 // Rows
 pinMode(PIN5, INPUT);
 digitalWrite(PIN5, HIGH);  // set pull-up resistors for all inputs


 pinMode(PIN6, INPUT);
 digitalWrite(PIN6, HIGH);


 pinMode(PIN7, INPUT);
 digitalWrite(PIN7, HIGH);


 pinMode(PIN8, INPUT);
 digitalWrite(PIN8, HIGH);


 // Columns
 pinMode(PIN2, OUTPUT);
 digitalWrite(PIN2, HIGH);


 pinMode(PIN3, OUTPUT);
 digitalWrite(PIN3, HIGH);


 pinMode(PIN4, OUTPUT);
 digitalWrite(PIN4, HIGH);
}


void loop() {
 int key = scanKeypad();
 /*
 if (key != -1) {
   if (key == STAR) {
     Serial.println("*");
   } else {
     if (key == POUND) {
       Serial.println("#");
     } else {
         Serial.println(key);
     }
   }
 }
 */
 Serial.println(key);
 delay(1000);
}


int scanKeypad() {
 int key = -1;


 // Pull the first column low, then check each of the rows to see if a
 // button is pressed.
 digitalWrite(PIN2, LOW);
 if (digitalRead(PIN5) == LOW) {
   key = 1;
  // Serial.println("Knapp 1 fungerar");
 } if (digitalRead(PIN6) == LOW) {
   key = 4;
   //Serial.println("Knapp 4 fungerar");
 } if (digitalRead(PIN7) == LOW) {
   key = 7;
   //Serial.println("Knapp 7 fungerar");
 }
 digitalWrite(PIN2, HIGH);
 // Moving on to the second column....


 digitalWrite(PIN3, LOW);
 if (digitalRead(PIN5) == LOW) {
   key = 2;
  // Serial.println("Knapp 2 fungerar");
 } if (digitalRead(PIN6) == LOW) {
   key = 5;
   //Serial.println("Knapp 5 fungerar");
 } if (digitalRead(PIN7) == LOW) {
   key = 8;
  // Serial.println("Knapp 8 fungerar");
 } if (digitalRead(PIN8) == LOW) {
   key = 0;
  // Serial.println("Knapp 0 fungerar");
 }
 digitalWrite(PIN3, HIGH);


 // Third "column".  Note that the 0 key is wired to this column even though
 // the 0 is really in the second column.
 digitalWrite(PIN4, LOW);
 if (digitalRead(PIN5) == LOW) {
   key = 3;
   //Serial.println("Knapp 3 fungerar");
 } if (digitalRead(PIN6) == LOW) {
   key = 6;
  // Serial.println("Knapp 6 fungerar");
 } if (digitalRead(PIN7) == LOW) {
   key = 9;
  // Serial.println("Knapp 9 fungerar");
 }
 digitalWrite(PIN4, HIGH);


 /*
 // Last "column" is not really it's own column.  Only wired to * and #
 digitalWrite(RED, LOW);
 if (digitalRead(ORANGE) == LOW) {
   key = STAR;
 }
 if (digitalRead(BROWN) == LOW) {
   key = POUND;
 }
 digitalWrite(RED, HIGH);
 */


 return key;
}

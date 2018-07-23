//============================================================
//  mjakovlevs@gmail.com
//============================================================

#include <Debounce.h>

#define buttonPin 8 // Arduino digital pin 8
#define ledPin 13 // Arduino digital pin 13 (internal led)

Debounce button;

bool ledState;
int counter;

void setup() {
  Serial.begin(9600);
  
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  // initialising the debouncer with a constructor
  button = Debounce(25, 1000, HOLD_MODE_ONCE); // debounce time 25ms, hold time 1000ms, single-shot hold mode
  // try changing to HOLD_MODE_RETRIG for periodic triggering
  
  //========================================================================================================================
  //  you can also use button.setDebounceTime(), button.setHoldTime() and button.setHoldMode() to set these parameters individually.
  //========================================================================================================================
}

void loop() {
  // writing our button pin state to the debouncer, this triggers debouncing
  button.writeState(digitalRead(buttonPin));
  
  // testing features
  if (button.pressed()) {
    ledState = !ledState; // toggle led state
    Serial.println("pressed");
  }
  
  if (button.released()) Serial.println("released");
  
  if (button.held()) {
     ledState = !ledState; // toggle led state
    Serial.println("held");
  }
  
  // write led state to the appropriate digital pin
  digitalWrite(ledPin, ledState);
}

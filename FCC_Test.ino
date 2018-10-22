/*
  Test code for the controller bench test setup
  
  This simple code is only intended to test that the inputs
  and outputs of the controller are connected correctly.
  
  It does not verify the controller's finite state machine algorithm.
*/

// the digital pin for the system on pin, may be changed as needed.
#define SYS_ON_PIN 9

// the analog threshold to listen for. May be tuned as needed.
#define ANALOG_THRESHOLD 500

void setup() {
  // Setup all digital outputs and inputs
  initDPins();
  
  // turn em all on and off quickly
  onOff();
  
  // turn em all on and off slowly
  allOn();
  delay(1000);
  allOff();
  
  // do nothing until the system on pin is pressed
  do {
    delay(50);
  while (dread(SYS_ON_PIN) != 1);
}

void loop() {
  // check if Ain's read above the constant analog threshold.
  // turn on a corresponding LED if it is 
  // (A0 -> D8, A1 -> D10, A2 -> D11, A3 -> D12, A4 -> D13
  for (int i = 0; i < 5; i++) {
    if (readA(i) > ANALOG_THRESHOLD) {
      if (i == 0)
        don(8); // A0 -> D8
      else
        don(i + 9); // A1 -> D10, A2 -> D11, A3 -> D12, A4 -> D13
    }
  }
}

// HELPERS

// Read an analog pin, given by pin
int readA(int pin) {
  return analogRead(pin);
}

// Turn a digital pin HIGH (turn it on). Will not work for the system on pin
void don(int pin) {
  if (pin == SYS_ON_PIN)
    return;
    
  digitalWrite(pin, HIGH);
}

// Turn a digital pin LOW (turn it off). Will not work for the system on pin
void doff(int pin) {
  if (pin == SYS_ON_PIN)
    return;

  digitalWrite(pin, LOW);
}

// Read from a digital pin. Does not work if <pin> is not the system on pin
int dread(int pin) {
  if (pin != SYS_ON_PIN)
    return;
    
  return digitalRead(pin);
}

// initialize all digital pins to be digital outputs, but make the system 
// on pin a digital input
void initDPins() {
   for (int i = 2; i < 14; i++) {
      if (i == SYS_ON_PIN)
         continue;
       
      pinMode(i, OUTPUT);
   }
   
   pinMode(SYS_ON_PIN, INPUT);
}

// Turn each digital pins HIGH for half a second, and then turn them back 
// off one at a time
void onOff() {
  for (int i = 2; i < 14; i++) {
      if (i == 9)
         continue;
       
      don(i);
      delay(500);
      doff(i);
   }
}

// Turn all of the digital output pins high at the same time
void allOn() {
  for (int i = 2; i < 14; i++) {
      if (i == SYS_ON_PIN)
         continue;
       
      don(i);
   }
}

// Turn all of the digital output pins low at the same time
void allOff() {
   for (int i = 2; i < 14; i++) {
       if (i == SYS_ON_PIN)
         continue;
       
       doff(i);
   }
}

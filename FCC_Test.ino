/*
Test code for the controller bench test setup

This simple code is only intended to test that the inputs
and outputs of the controller are connected correctly.

It does not verify the controller process of the controller
*/

#define SYS_ON_PIN 9
#define ANALOG_THRESHOLD 500

void setup() {
  // Setup all digital outputs and inputs
  initDPins();
  
  // turn em all on and off slowly
  onOff();
  
  // turn em all on and off slowly
  allOn();
  delay(1000);
  allOff();
  
  do {
    delay(50);
  while (dread(SYS_ON_PIN) != 1);
}

void loop() {
  // check if Ain's read above the constant analog threshold.
  // turn on a corresponding LED if it is
  
  for (int i = 0; i < 5; i++) {
    if (readA(i) > ANALOG_THRESHOLD) {
      if (i == 0)
        don(8); // A0 -> D8
      else
        don(i + 9); // A1 -> D10, A2 -> D11, A3 -> D12, A4 -> D13
    }
  }
}

int readA(int pin) {
  return analogRead(pin);
}

void don(int pin) {
  if (pin == SYS_ON_PIN)
    return;
    
  digitalWrite(pin, HIGH);
}

void doff(int pin) {
  if (pin == SYS_ON_PIN)
    return;

  digitalWrite(pin, LOW);
}

int dread(int pin) {
  if (pin != SYS_ON_PIN)
    return;
    
  return digitalRead(pin);
}

void initDPins() {
   for (int i = 2; i < 14; i++) {
      if (i == SYS_ON_PIN)
         continue;
       
      pinMode(i, OUTPUT);
   }
   
   pinMode(SYS_ON_PIN, INPUT);
}

void onOff() {
  for (int i = 2; i < 14; i++) {
      if (i == 9)
         continue;
       
      don(i);
      delay(500);
      doff(i);
   }
}

void allOn() {
  for (int i = 2; i < 14; i++) {
      if (i == SYS_ON_PIN)
         continue;
       
      don(i);
   }
}

void allOff() {
   for (int i = 2; i < 14; i++) {
       if (i == SYS_ON_PIN)
         continue;
       
       doff(i);
   }
}

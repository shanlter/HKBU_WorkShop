#define LEDBUILTIN 13

// the setup function runs once when you press reset or power the board
void setup(){ 
  // initialize digital pin LEDBUILTIN as an output.
  pinMode(LEDBUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop(){ 
  digitalWrite(LEDBUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);                       // wait for a second
  
  
  digitalWrite(LEDBUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}


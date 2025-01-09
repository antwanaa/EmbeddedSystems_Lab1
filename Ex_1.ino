/*
  Blink

*/
#define LED_PIN 6 // Defining the pin for the LED

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_PIN as an output.
  pinMode(LED_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(300);                    // wait for 300ms
  digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
  delay(800);                    // wait for 800ms
}

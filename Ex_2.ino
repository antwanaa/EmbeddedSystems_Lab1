#define LED_PIN 6 // Defining the pin for the LED
#define BUTTON_PIN 4  // Defining the pin for the push button

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins LED_PIN as an output and BUTTON_PIN as an input.
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  if(digitalRead(BUTTON_PIN)){    // If the button is pressed, 
    digitalWrite(LED_PIN, HIGH);  // Turn on the LED
  }else{                          // Otherwise
    digitalWrite(LED_PIN, LOW);   // Blink the LED
    delay(500);
    digitalWrite(LED_PIN, HIGH);
    delay(200);
  }
}

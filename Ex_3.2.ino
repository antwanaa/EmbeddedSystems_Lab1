#define LED_PIN 6 // Defining the LED pin
#define POTM A0   // Defining the potentiometer pin
float m = -450.0/1023.0;  // Initializing the scope

void setup() {
  pinMode(LED_PIN, OUTPUT); // Defining the LED pin as an output
  Serial.begin(115200);       // Starting serial communication
}

void loop() {
  // put your main code here, to run repeatedly:
  float pot = analogRead(POTM);     // Reading the value from the analog pin
  Serial.println(pot);              // Printing the value 
  float x = m*pot + 500.0;          // Computing our delay value
  
  digitalWrite(LED_PIN, HIGH);      // Turning on the LED
  delay(x);                         // Waiting the computed amount
  digitalWrite(LED_PIN, LOW);       // Turning off the LED
  delay(x);                         // Waiting the computed amount
}

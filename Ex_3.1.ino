#define LED_PIN 6 // Defining the LED pin
#define POTM A0   // Defining the potentiometer pin
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT); // Defining the LED pin as an output
  Serial.begin(9600);       // Starting serial communication
}

void loop() {
  int pot = analogRead(POTM);     // Reading the value from the analog pin
  Serial.println(pot);            // Printing the value 
  if(pot>=600){                   // If the value is higher than the threshold (600)
    digitalWrite(LED_PIN, HIGH);  // Turn on the LED
  }else{
    digitalWrite(LED_PIN, LOW);   // Otherwise, turn off the LED
  }
  delay(100);
}

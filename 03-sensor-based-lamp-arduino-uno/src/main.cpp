#include <Arduino.h>

//Relay
int relay = 8;
volatile byte relayState = LOW;

//PIR Sensor
int PIRInterrupt = 2;

// Timer var
long lastDebounceTime = 0;
long debounceDelay = 10000;

void detectMotion(){

  Serial.println("Motion");
  if(relayState == LOW){
    digitalWrite(relay, LOW);
  }
  relayState = HIGH;
  Serial.println("ON");
  lastDebounceTime = millis();
}

void setup() {
  // Pin for relay set as output
  pinMode(relay, OUTPUT);

  // Pin for PIR sensor set as input
  pinMode(PIRInterrupt, INPUT);

  // Triggers detectMotion function on rising mode to turn the relay on, if the condition is met
  attachInterrupt(digitalPinToInterrupt(PIRInterrupt), detectMotion, RISING);

  Serial.begin(9600);

}

void loop() {
  // If ten seconds have passed, the relay is turned off
  if((millis() - lastDebounceTime) > debounceDelay && relayState == HIGH){
    digitalWrite(relay, HIGH);
    relayState = LOW;
    Serial.println("OFF");
  }
  delay(50);
}
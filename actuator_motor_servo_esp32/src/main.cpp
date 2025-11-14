#include <Arduino.h>
#include <ESP32Servo.h>

Servo myservo; //Membuat objek servo

int servoPin = 13; //Inisiasi pin data servo

int pos = 0; //Inisiasi posisi servo (derajat)

//Menghubungkan ke servo
void setup(){
  Serial.begin(115200);
  Serial.println("Menyambungkan ke Motor Servo!");
  myservo.attach(servoPin);
}

void loop(){
  //Gerakkan dari 0 ke 180 derajat
  for(pos = 0; pos <= 180; pos += 1){

    myservo.write(pos);
    delay(15);
  }

  //Gerakkan dari 180 ke o derajat
  for(pos = 180; pos >= 0; pos -= 1){

    myservo.write(pos);
    delay(15);
  }
}
#include <Servo.h>


int readSwitch = 7;
int greenLED = 3;


int redLED = 4;
int potiPIN = A1;

float servoWert;

Servo myservo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(greenLED, OUTPUT);

  myservo.attach(7);

  servoWert = 0;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int potiWert;

  potiWert = analogRead(potiPIN);

  servoWert = (180.0/1024.0)*potiWert;

  Serial.print("Poti: ");
  Serial.print(potiWert);
  Serial.print(" Servo: ");
  Serial.println(servoWert);
  
  myservo.write(servoWert);

  delay(100);
  

}

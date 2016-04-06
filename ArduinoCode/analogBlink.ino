#include <Servo.h>


int readSwitch = 7;
int greenLED = 3;


int redLED = 4;
int potiPIN = A1;

int servoWert;

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

  servoWert = (180/1024)*potiWert;

  Serial.print("Poti: " + potiWert);
  Serial.println("Servo: " + servoWert);
  
  //myservo.write(servoWert);

  delay(100);
  

}

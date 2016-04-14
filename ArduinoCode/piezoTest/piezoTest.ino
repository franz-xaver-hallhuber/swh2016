const int blauHam =A0;
//const int pinkHam = A2;
const int ledPin= 4;
const int threshold= 100;

void setup()
{
Serial.begin(9600);
  
pinMode(ledPin, OUTPUT);
}

void loop()
{
int valBlue = analogRead(blauHam);
//int valPink = analogRead(pinkHam);


if (valBlue <= threshold)
{
digitalWrite(ledPin, HIGH);
delay(1000);
Serial.print("Blue:");
Serial.println(valBlue);
digitalWrite(ledPin, LOW);
}

/*if (valPink>= threshold)
{
digitalWrite(ledPin, HIGH);
delay(1000);
Serial.print("Pink:");
Serial.println(valPink);
digitalWrite(ledPin, LOW);
}*/

else 
digitalWrite(ledPin, LOW);
} 

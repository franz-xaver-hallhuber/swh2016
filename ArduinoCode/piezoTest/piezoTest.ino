const int blauHam = A0;
const int pinkHam = A2;
const int ledPin= 4;
const int threshold= 50;

void setup()
{
Serial.begin(9600);
  
pinMode(ledPin, OUTPUT);
//analogWrite(blauHam, HIGH);
analogWrite(pinkHam, HIGH);
}

void loop()
{
int valBlue = analogRead(blauHam);
int valPink = analogRead(pinkHam);

 /*digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);  */      

Serial.print("Blue:");
Serial.println(valBlue);
Serial.print("Pink:");
Serial.println(valPink);
delay(50);
if (valBlue >= threshold)
{
//digitalWrite(ledPin, HIGH);
delay(1000);
Serial.print("Blue:");
Serial.println(valBlue);
//digitalWrite(ledPin, LOW);
}

if (valPink >= 5)
{
//digitalWrite(ledPin, HIGH);
delay(1000);
Serial.print("Pink:");
Serial.println(valPink);
//digitalWrite(ledPin, LOW);
}

//else 
//digitalWrite(ledPin, LOW);
} 

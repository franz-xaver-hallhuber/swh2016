int redLED = 3;
int piezoPin = A0;
int threshold = 1000;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(redLED, OUTPUT);

  
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(piezoPin);
  Serial.println(val);
  
  if(val>=threshold) {
    digitalWrite(redLED, HIGH);
     delay(5000);
  } else {
    digitalWrite(redLED, LOW);
  }

 
  

}

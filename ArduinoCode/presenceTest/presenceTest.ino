
int threshold = 290;
const int squareWidth = 6; 
const bool w = true;
const bool f = false;
int counter = 0;

int rowPins[squareWidth] = {2,3,4,5,6,7};
int colPins[squareWidth] = {22,24,26,28,30,32};
int ctrlPins[squareWidth] = {A4,A5,A6,A7,A8,A9};
bool colStatus[squareWidth] = {w,w,w,w,w,w};
int colValues[squareWidth] = {0,0,0,0,0,0};

bool onMatrix[squareWidth][squareWidth] = {
  {w, f, f, f, f, f},
  { f, f, f, f, f, f},
  { f, f, f, f, f, f},
  { f, f, f, f, f, f},
  { f, f, f, f, f, f},
  { f, f, f, f, f, f}
};

void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  for (int i = 0; i < squareWidth; i++) {
    pinMode(rowPins[i], OUTPUT);
    pinMode(colPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
    digitalWrite(colPins[i], LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(analogRead(A4));

  counter++;
  drawOn();

  if (counter > 10) {
    for (int i = 0; i < squareWidth; i++) {
      Serial.print("status");
      Serial.println(colStatus[i]);
    }
    for (int i = 0; i < squareWidth; i++) {
      Serial.print("values");
      Serial.println(colValues[i]);
    }
    //Serial.println("");
    counter = 0;
  }
  
  
}

void drawOn() {
   for (int i = 0; i < squareWidth; i++) {
    for (int j = 0; j < squareWidth; j++) {
      if (onMatrix[i][j]) {
        blinkOnce(i,j); 
      } 
    }
  }
}

void blinkOnce(int row, int col) {
  
    digitalWrite(rowPins[row],HIGH);
    digitalWrite(colPins[col],HIGH);
    delay(10);
    checkStatus();
    digitalWrite(rowPins[row],LOW);
    digitalWrite(colPins[col],LOW);
    
}

void checkStatus() {
    for (int i = 0; i < squareWidth; i++) {
      colValues[i] = analogRead(i);
      if(analogRead(i) > threshold) {
        colStatus[i] = w;
      } else {
        colStatus[i] = f;
    }
  }
}


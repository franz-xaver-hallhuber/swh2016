

const int squareWidth = 6; 
const bool w = true;
const bool f = false;

bool dangerMatrix[squareWidth][squareWidth] = {
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f}
};

bool offMatrix[squareWidth][squareWidth] = {
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f}
};

bool onMatrix[squareWidth][squareWidth] = {
  {w, w, w, w, w, w},
  {w, w, w, w, w, w},
  {w, w, w, w, w, w},
  {w, w, w, w, w, w},
  {w, w, w, w, w, w},
  {w, w, w, w, w, w}
};

bool sMatrix[squareWidth][squareWidth] = {
  {f,f,w,w,w,w},
  {f,w,f,f,f,f},
  {f,w,w,w,f,f},
  {f,f,w,w,w,f},
  {f,f,f,f,w,f},
  {w,w,w,w,f,f}
};

bool wMatrix[squareWidth][squareWidth] = {
  {w,f,f,f,f,w},
  {w,f,f,f,f,w},
  {w,f,f,f,f,w},
  {w,f,f,f,f,w},
  {w,f,w,w,f,w},
  {f,w,f,f,w,f}
};

bool hMatrix[squareWidth][squareWidth] = {
  {w,f,f,f,f,w},
  {w,f,f,f,f,w},
  {w,w,w,w,w,w},
  {w,w,w,w,w,w},
  {w,f,f,f,f,w},
  {w,f,f,f,f,w}
};

bool testMatrix[squareWidth][squareWidth] = {
  {w,f,f,f,f,f},
  {f,f,f,f,f,f},
  {f,f,f,f,f,f},
  {f,f,f,f,f,f},
  {f,f,f,f,f,f},
  {f,f,f,f,f,f}
};

//pin config
int rowPins[squareWidth] = {2,3,4,5,6,7};
int colPins[squareWidth] = {22,24,26,28,30,32};
int rgbPins[4] = {42,44,46,48};
int polly = 52;
//int hammerIn = 36;

int speaker = A1;
int blauHam =A0;
int pinkHam = A2;
const int thresholdBlue = 10;
const int thresholdPink = 80; 
long counter = 0;
long counterVal = 0;
const int dangerCount = 4;

//values for RGB LED
const int blau = 42;
const int gruen = 44;
const int rot = 46;
const int blauu = 48;

//status parameters
bool gameStarted = false;
bool demoMode = true; //demo mode at beginning
bool blueturn, pinkturn;

//game parameters
int hitsValBlue = 3;
int hitsValPink = 3;
int sameTimeTreshold = 40;


void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(A12));
  
  // put your setup code here, to run once:
  for (int i = 0; i < squareWidth; i++) {
    pinMode(rowPins[i], OUTPUT);
    pinMode(colPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
    digitalWrite(colPins[i], LOW);
  }


  for (int i = 0; i < 4; i++) {
    pinMode(rgbPins[i], OUTPUT);
    digitalWrite(rgbPins[i], LOW);
  }  

  //pinMode(hammerIn, INPUT);
  pinMode(polly, OUTPUT);
  digitalWrite(polly, LOW);

  //somebody said pullup!
  int valPink = analogRead(pinkHam);
  /*digitalWrite(polly, HIGH);
  delay(1000);
  digitalWrite(polly, LOW);*/
}


void loop() {
  // put your main code here, to run repeatedly:
  // Value for Hammer
  int valBlue = analogRead(blauHam);
  int valPink = analogRead(pinkHam);

  counter++;
  //Serial.println(counter);
 /*
  
  //Game will be started with hitting both hammers at the same time
  if (valPink >= threshold && valBlue >= threshold) {
    demoMode = false;
    gameStarted = true; 
    }*/
    
  //Gamestart - all LEDs on
  if(gameStarted && (counter <10)) {
      drawOn(10);    
  }

  if (gameStarted && counter == 10) {
    selectDangerZone();
    selectBeginner();
  }

  if (gameStarted && counter > 11 && counter < 550) {
    drawDangerMatrix();
  }

  if (gameStarted && counter >= 550) {
     drawOn(1);
     if (blueturn) {
      digitalWrite(blau, HIGH);
      delay(2);
      digitalWrite(blau, LOW);
      if (valBlue >= thresholdBlue) {
         hitsDecrB();
         Serial.println(hitsValBlue);
         Serial.println("Blue:");
         Serial.println(valBlue);
         delay(500); //used to control the the value per hits
      }
       } else {
        digitalWrite(rot, HIGH);
        digitalWrite(blauu, HIGH);
        delay(2);
        digitalWrite(blauu, LOW);
        digitalWrite(rot, LOW);
  
        if (valPink >= thresholdPink) {
        hitsDecrP();
        Serial.println(hitsValPink);
        Serial.println("Pink:");
        Serial.println(valPink);
        delay(500); //used to control the the value per hits
       }
    }
  }


if(demoMode) {
    for (int i = 0; i < 55; i++) {
      drawS();
    }
    if(!demoMode) return;
    for (int i = 0; i < 55; i++) {
      drawW();
    }
    if(!demoMode) return;
    for (int i = 0; i < 55; i++) {
      drawH();
    }
  }
}//end loop


void hitBlue(){
  
}

void drawOn(int dur) {
   for (int i = 0; i < squareWidth; i++) {
    for (int j = 0; j < squareWidth; j++) {
      if (onMatrix[i][j]) {
        blinkOnce(i,j,dur); 
      } 
    }
  }
}

void drawS() {  
  //loop over wMatrix
  for (int i = 0; i < squareWidth; i++) {
    for (int j = 0; j < squareWidth; j++) {
      if (sMatrix[i][j]) {
        blinkOnce(i,j,2); 
      } 
    }
  }
  if (sameTime() == 1) {
      demoMode = false;
      gameStarted = true;
      counter = 0;
    }
}

void drawW() {  
  //loop over wMatrix
  for (int i = 0; i < squareWidth; i++) {
    for (int j = 0; j < squareWidth; j++) {
      if (wMatrix[i][j]) {
        blinkOnce(i,j,2); 
      } 
    }
  }
  if (sameTime() == 1) {
      demoMode = false;
      gameStarted = true;
    }
}

void drawH() {  
  //loop over hMatrix
  for (int i = 0; i < squareWidth; i++) {
    for (int j = 0; j < squareWidth; j++) {
      if (hMatrix[i][j]) {
        blinkOnce(i,j,2); 
      } 
    }
  }
  if (sameTime() == 1) {
      demoMode = false;
      gameStarted = true;
    }
}

void drawTest() {
  //loop over testMatrix
  for (int i = 0; i < squareWidth; i++) {
    for (int j = 0; j < squareWidth; j++) {
      if (testMatrix[i][j]) {
        blinkOnce(i,j,2); 
      } 
    }
  }
}

void drawDangerMatrix() {
  for (int i = 0; i < squareWidth; i++) {
    for (int j = 0; j < squareWidth; j++) {
      if (dangerMatrix[i][j]) {
        blinkOnce(i,j,2); 
      } 
    }
  }
}

void blinkOnce(int row, int col, int del) {
  
  if ((row == 2 || row == 3) && (col == 2 || col == 3)) {
    if(demoMode) {
      digitalWrite(gruen, HIGH);
      //digitalWrite(blauu, HIGH);
      delay(del);
      digitalWrite(gruen, LOW);
      //digitalWrite(blauu, LOW);
    }
  } else {
    digitalWrite(rowPins[row],HIGH);
    digitalWrite(colPins[col],HIGH);
    delay(del);
    digitalWrite(rowPins[row],LOW);
    digitalWrite(colPins[col],LOW);
  }  
}

void hitsDecrB() {
   if(hitsValBlue > 1){
     hitsValBlue-- ;
    }
    else {
      digitalWrite(rot, HIGH);
      digitalWrite(polly, HIGH);
      delay(2000);
      digitalWrite(polly, LOW);
      digitalWrite(rot, LOW);
      pinkturn = true;
      blueturn = false;
      hitsValBlue = 3;
    }
}

void hitsDecrP() {
   if(hitsValPink > 1){
     hitsValPink-- ;
    }
    else {
      digitalWrite(rot, HIGH);
      digitalWrite(polly, HIGH);
      delay(2000);
      digitalWrite(polly, LOW);
      digitalWrite(rot, LOW);
      blueturn = true;
      pinkturn = false;
      hitsValPink = 3;
    }
}



int sameTime() {
  // Value for Hammer
  int valBlue = analogRead(blauHam);
  int valPink = analogRead(pinkHam);

 // Serial.print("blue");
  //Serial.println(valBlue);
  //Serial.print("pink:");
  //Serial.println(valPink);

  if (valPink >= thresholdPink) {
    for (int i = 0; i < sameTimeTreshold; i ++) {
      if (valBlue >= thresholdBlue) {
        Serial.println("Demo over");
        return 1;
      }
    }
  }
  if (valBlue >= thresholdBlue) {
    for (int i = 0; i < sameTimeTreshold; i ++) {
      if (valPink >= thresholdPink) {
        Serial.println("Demo over");
        return 1;
      }
    }
  }
  
  return 0;
}

void selectDangerZone() {
  for(int i=0; i<dangerCount; i++) {
    int rCol = random(0,5);
    int rRow = random(0,5);

    Serial.print("random");
    Serial.print(rCol);
    Serial.println(rRow);
    dangerMatrix[rCol][rRow] = w;
  }
  
  }

void selectBeginner() {
  int ran = random(7,9);
  Serial.println(ran);
  if(ran == 8) {
    blueturn = true;
  }
  else {
    pinkturn = true;
  }
}


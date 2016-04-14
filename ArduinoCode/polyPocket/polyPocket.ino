

const int squareWidth = 6; 
const bool w = true;
const bool f = false;

bool offMatrix[squareWidth][squareWidth] = {
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f}
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
int hammerIn = 36;

int speaker = A1;
int hammerOne = A2;
int hammerTwo = A3;

//values for RGB LED
const int blau = 42;
const int gruen = 44;
const int rot = 46;
const int blauu = 48;

//status parameters
bool gameStarted = false;
bool demoMode = true; //demo mode at beginning

//game parameters
const int startVal = 5;


void setup() {
  //Serial.begin(9600);
  
  // put your setup code here, to run once:
  for (int i = 0; i < squareWidth; i++) {
    pinMode(rowPins[i], OUTPUT);
    pinMode(colPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
    digitalWrite(colPins[i], LOW);
  }

  //Serial.println("test1");

  for (int i = 0; i < 4; i++) {
    pinMode(rgbPins[i], OUTPUT);
    digitalWrite(rgbPins[i], LOW);
  }  

  pinMode(hammerIn, INPUT);
  pinMode(polly, OUTPUT);

  //digitalWrite(polly, HIGH);
  //delay(1000);
  //digitalWrite(polly, LOW);

  //Serial.println("test2");

  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(demoMode) {
    for (int i = 0; i < 55; i++) {
      drawS();
    }
    for (int i = 0; i < 55; i++) {
      drawW();
    }
    for (int i = 0; i < 55; i++) {
      drawH();
    }
    //demoMode = false;
  }
}

void drawS() {  
  //loop over wMatrix
  for (int i = 0; i < squareWidth; i++) {
    for (int j = 0; j < squareWidth; j++) {
      if (sMatrix[i][j]) {
        blinkOnce(i,j); 
      } 
    }
  }
  if (readHammers() == 1) {
    demoMode = false;
  }
}

void drawW() {  
  //loop over wMatrix
  for (int i = 0; i < squareWidth; i++) {
    for (int j = 0; j < squareWidth; j++) {
      if (wMatrix[i][j]) {
        blinkOnce(i,j); 
      } 
    }
  }
  if (readHammers() == 1) {
    demoMode = false;
  }
}

void drawH() {  
  //loop over hMatrix
  for (int i = 0; i < squareWidth; i++) {
    for (int j = 0; j < squareWidth; j++) {
      if (hMatrix[i][j]) {
        blinkOnce(i,j); 
      } 
    }
  }
  if (readHammers() == 1) {
    demoMode = false;
  }
}

void drawTest() {
  //loop over testMatrix
  for (int i = 0; i < squareWidth; i++) {
    for (int j = 0; j < squareWidth; j++) {
      if (testMatrix[i][j]) {
        blinkOnce(i,j); 
      } 
    }
  }
}

void blinkOnce(int row, int col) {
  
  if ((row == 2 || row == 3) && (col == 2 || col == 3)) {
    if(demoMode) {
      digitalWrite(gruen, HIGH);
      //digitalWrite(blauu, HIGH);
      digitalWrite(gruen, LOW);
      //digitalWrite(blauu, LOW);
    }
  } else {
    digitalWrite(rowPins[row],HIGH);
    digitalWrite(colPins[col],HIGH);
    delay(1);
    digitalWrite(rowPins[row],LOW);
    digitalWrite(colPins[col],LOW);
  }  
}

int readHammers() {
  return 0;
}


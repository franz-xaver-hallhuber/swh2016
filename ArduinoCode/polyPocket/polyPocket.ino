// we have 6 cubes per row and column
const int squareWidth = 6; 

//just to write the matrices more easily
const bool w = true;
const bool f = false;

//different patterns to be displayed by the 2D LED Matrix
//matrix in which randomly four cells will be set as "danger cubes"
bool dangerMatrix[squareWidth][squareWidth] = {
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f}
};

//just to turn everything off
bool offMatrix[squareWidth][squareWidth] = {
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f},
  {f, f, f, f, f, f}
};

//and to turn everything on 
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

//displays a "W" on the matrix
bool wMatrix[squareWidth][squareWidth] = {
  {w,f,f,f,f,w},
  {w,f,f,f,f,w},
  {w,f,f,f,f,w},
  {w,f,f,f,f,w},
  {w,f,w,w,f,w},
  {f,w,f,f,w,f}
};

//displays a "H" on the matrix
bool hMatrix[squareWidth][squareWidth] = {
  {w,f,f,f,f,w},
  {w,f,f,f,f,w},
  {w,w,w,w,w,w},
  {w,w,w,w,w,w},
  {w,f,f,f,f,w},
  {w,f,f,f,f,w}
};

//for test purposes (where is the top?)
bool testMatrix[squareWidth][squareWidth] = {
  {w,f,f,f,f,f},
  {f,f,f,f,f,f},
  {f,f,f,f,f,f},
  {f,f,f,f,f,f},
  {f,f,f,f,f,f},
  {f,f,f,f,f,f}
};

//pin configurations
int rowPins[squareWidth] = {2,3,4,5,6,7};
int colPins[squareWidth] = {22,24,26,28,30,32};
int rgbPins[4] = {42,44,46,48};
int polly = 52;
int blauHam =A0;
int pinkHam = A2;

//thresholds found by try and error
const int thresholdBlue = 10;
const int thresholdPink = 80; 

//counter for implementing a rudimentary "timer"
long counter = 0;
long counterVal = 0;

//how many "danger cubes" should there be?
const int dangerCount = 4;

//values to address RGB LED by colour names
const int blau = 42;
const int gruen = 44;
const int rot = 46;
const int blauu = 48;

//status parameters
bool gameStarted = false; //starts when both hammers have been hit
bool demoMode = true; //demo mode at beginning
bool blueturn, pinkturn; //whose turn is it?

//game parameters
int hitsValBlue = 3; //maximum hits per round
int hitsValPink = 3;
int sameTimeTreshold = 40; //tolerance to count the two hammers as being hit "simuntaneously"


void setup() {
  Serial.begin(9600);

  //read a random value from an unused analogue pin to get random values
  randomSeed(analogRead(A12));

  //set up all pins as OUT- or INPUT
  //pins for addressing LEDs
  for (int i = 0; i < squareWidth; i++) {
    pinMode(rowPins[i], OUTPUT);
    pinMode(colPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
    digitalWrite(colPins[i], LOW);
  }

  //pins for addressing the RGBB-LED
  for (int i = 0; i < 4; i++) {
    pinMode(rgbPins[i], OUTPUT);
    digitalWrite(rgbPins[i], LOW);
  }  

  //and there's polly, turn it of at the start
  pinMode(polly, OUTPUT);
  digitalWrite(polly, LOW);
}


void loop() {
  // put your main code here, to run repeatedly:
  // read hammer values
  int valBlue = analogRead(blauHam);
  int valPink = analogRead(pinkHam);

  //increment the counter at each loop
  counter++;
  //Serial.println(counter);
    
  //Gamestart - all LEDs on
  if(gameStarted && (counter <10)) {
      drawOn(10);    
  }

  // calculate random values: danger cubes and beginner
  if (gameStarted && counter == 10) {
    selectDangerZone();
    selectBeginner();
  }

  //show danger cubes for a short period of time
  if (gameStarted && counter > 11 && counter < 550) {
    drawDangerMatrix();
  }

  //now you might start playing
  if (gameStarted && counter >= 550) {
    //light all LEDs
     drawOn(1);
     
     if (blueturn) {
      //indicate that it is blue's turn by a blue LED
      digitalWrite(blau, HIGH);
      delay(2);
      digitalWrite(blau, LOW);

      //decrement the number of remaining hits when a hit is detected
      if (valBlue >= thresholdBlue) {
         hitsDecrB();
         //Serial.println(hitsValBlue);
         //Serial.println("Blue:");
         //Serial.println(valBlue);
         delay(500); //used to control the the value per hits
      }
       } else {
        //indicate that it is blue's turn by a pink LED
        digitalWrite(rot, HIGH);
        digitalWrite(blauu, HIGH);
        delay(2);
        digitalWrite(blauu, LOW);
        digitalWrite(rot, LOW);

        //decrement the number of remaining hits when a hit is detected
        if (valPink >= thresholdPink) {
        hitsDecrP();
        //Serial.println(hitsValPink);
        //Serial.println("Pink:");
        //Serial.println(valPink);
        delay(500); //used to control the the value per hits
       }
    }
  }

// show "SWH" when the game is in idle mode
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
}


// function to light all LEDs
void drawOn(int dur) {
   for (int i = 0; i < squareWidth; i++) {
    for (int j = 0; j < squareWidth; j++) {
      if (onMatrix[i][j]) {
        blinkOnce(i,j,dur); 
      } 
    }
  }
}

//function to draw an "S"
void drawS() {  
  //loop over wMatrix
  for (int i = 0; i < squareWidth; i++) {
    for (int j = 0; j < squareWidth; j++) {
      if (sMatrix[i][j]) {
        blinkOnce(i,j,2); 
      } 
    }
  }
  //detect if somebody wants to start the game
  if (sameTime() == 1) {
      demoMode = false;
      gameStarted = true;
      counter = 0;
    }
}

//function to draw an "W"
void drawW() {  
  //loop over wMatrix
  for (int i = 0; i < squareWidth; i++) {
    for (int j = 0; j < squareWidth; j++) {
      if (wMatrix[i][j]) {
        blinkOnce(i,j,2); 
      } 
    }
  }
  //detect if somebody wants to start the game
  if (sameTime() == 1) {
      demoMode = false;
      gameStarted = true;
    }
}

//function to draw an "H"
void drawH() {  
  //loop over hMatrix
  for (int i = 0; i < squareWidth; i++) {
    for (int j = 0; j < squareWidth; j++) {
      if (hMatrix[i][j]) {
        blinkOnce(i,j,2); 
      } 
    }
  }
  //detect if somebody wants to start the game
  if (sameTime() == 1) {
      demoMode = false;
      gameStarted = true;
    }
}

//draw the test matrix
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

//show Polly's danger cubes
void drawDangerMatrix() {
  for (int i = 0; i < squareWidth; i++) {
    for (int j = 0; j < squareWidth; j++) {
      if (dangerMatrix[i][j]) {
        blinkOnce(i,j,2); 
      } 
    }
  }
}

// shortly light a certain LED
// row,col: LED position
// del: duration in ms
void blinkOnce(int row, int col, int del) {  
  // if a matrix addresses one of the four (non-existant) central blocks
  // light the RGB LED in green instead
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

// decrease the remaining hits for blue by one and light the LED red 
// if the numer hits zero to indicate that the round is over for now
void hitsDecrB() {
   if(hitsValBlue > 1){
     hitsValBlue-- ;
    }
    else {
      digitalWrite(rot, HIGH);
      //digitalWrite(polly, HIGH);
      delay(2000);
      digitalWrite(rot, LOW);
      //digitalWrite(polly, LOW);
      pinkturn = true;
      blueturn = false;
      hitsValBlue = 3;
    }
}

// decrease the remaining hits for pink by one and light the LED red 
// if the numer hits zero to indicate that the round is over for now
void hitsDecrP() {
   if(hitsValPink > 1){
     hitsValPink-- ;
    }
    else {
      digitalWrite(rot, HIGH);
      //digitalWrite(polly, HIGH);
      delay(2000);
      //digitalWrite(polly, LOW);
      digitalWrite(rot, LOW);
      blueturn = true;
      pinkturn = false;
      hitsValPink = 3;
    }
}

// find out if both hammers have been hit at the same time
// returns 1 if yes, 0 if no
int sameTime() {
  // Value for Hammer
  int valBlue = analogRead(blauHam);
  int valPink = analogRead(pinkHam);

  //Serial.print("blue");
  //Serial.println(valBlue);
  //Serial.print("pink:");
  //Serial.println(valPink);

  if (valPink >= thresholdPink) {
    // wait for a certain time for the other player
    for (int i = 0; i < sameTimeTreshold; i ++) {
      if (valBlue >= thresholdBlue) {
        Serial.println("Demo over");
        return 1;
      }
    }
  }
  if (valBlue >= thresholdBlue) {
    // wait for a certain time for the other player
    for (int i = 0; i < sameTimeTreshold; i ++) {
      if (valPink >= thresholdPink) {
        Serial.println("Demo over");
        return 1;
      }
    }
  }
 
  return 0;
}

// sets the "danger cubes" randomly
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

// selects randomly who starts the game
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


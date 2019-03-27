
#include <Stepper.h>

const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 8, 11, 12, 13);


// Constants:

const int S1 = 7;
const int S2 = 2;
const int S3 = 3;
const int Red = 4;
const int Green = 5;
const int Full = 6;
const int interval = 500;
const int debounceDelay = 10;
const int openSteps = 50;
const int closeSteps = -50;

// Variables;

int i = 0;
int redState = HIGH;
int greenState = LOW;
int fullState = LOW;
int lastFullState = LOW;
int carCount = 0;
int fullBlinkTriggered = false; // used to tell the loop to blink full sign for 5 seconds.
int fullStateCount = 0;         // used to count how many time the sign has blinked.
int readingS1 = LOW;
int readingS2 = LOW;
int readingS3 = LOW;
int previousS1 = LOW;
int previousS2 = LOW;
int previousS3 = LOW;
unsigned long previousMillis = 0;
unsigned long currentMillis = millis();


void setup() {
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(Green, OUTPUT);
  pinMode(Red, OUTPUT);
  pinMode(Full, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(Green, greenState);
  digitalWrite(Full, fullState);
  digitalWrite(Red, redState);
  myStepper.setSpeed(30);
  Serial.begin(9600);
  Serial.println("Setup Finished");
}

void loop() {
  
    // Debounce S1:

readingS1 = digitalRead(S1);
    if (readingS1 == HIGH && previousS1 == 0){
      newCar();
    };
    previousS1 = readingS1;

    // Debouse S2:

    readingS2 = digitalRead(S2);
    if (readingS2 == HIGH && previousS2 == 0){
      closeBarrier();
    };
    previousS2 = readingS2;

    // Debounce S3:


    readingS3 = digitalRead(S3);
    if (readingS3 == HIGH && previousS3 == 0){
      
      Serial.println("running carLeaving");
      carCount = carCount - 1;
      Serial.println(carCount);
      digitalWrite(Full, LOW);
      Serial.println("returning to loop");
      Serial.println("--------------");  
      
    };
    previousS3 = readingS3;




  // Blink the Car Park Full Sign:
  
  if ( fullBlinkTriggered == true ) {
    currentMillis = millis();
    if ( currentMillis - previousMillis >= interval && fullStateCount <= 10 ) {
      previousMillis = currentMillis;

      if (fullState == LOW) {
        fullState = HIGH;
        lastFullState = fullState;
      } else {
        fullState = LOW;
        lastFullState = fullState;
      }
      digitalWrite(Full, fullState);
      Serial.println("Blinking Full sign");
      if ( fullStateCount >= 11 ) {
        int fullStateCount = 0;
        fullBlinkTriggered = false;
      };
    };
  };

}

void newCar() {
  Serial.println("running new car");
  Serial.println("carCount at start:");
  Serial.println(carCount);
  if (carCount < 5) {
    Serial.println("about to run openBarrier");
    openBarrier();
  } else {
    Serial.println("fullBlinkTriggered = true");
    int fullBlinkTriggered = true;
  };
}


void openBarrier() {
  Serial.println("running openBarrier");
  myStepper.step(openSteps);
  digitalWrite(Red, LOW);
  digitalWrite(Green, HIGH);
  Serial.println("Returning to loop");
  Serial.println("--------------");
}

void closeBarrier() {
  Serial.println("running closeBarrier");
  Serial.println("current carCount:");
  Serial.println(carCount);

  carCount = carCount + 1;
  Serial.println("new carCount");
  Serial.println(carCount);
  if ( carCount >= 5 ) {
    Serial.println("Full sign to high");
    digitalWrite( Full, HIGH );
  };
  digitalWrite(Red, HIGH);
  digitalWrite(Green, LOW);
  myStepper.step(closeSteps);
  Serial.println("returning to loop");
  Serial.println("--------------");
}

void carLeaving() {
  Serial.println("running carLeaving");
  carCount = carCount - 1;
  Serial.println(carCount);
  digitalWrite(Full, LOW);
  Serial.println("returning to loop");
  Serial.println("--------------");
}


/*

*/

// Constants:

const int S1 = 1;
const int S2 = 2;
const int S3 = 3;
const int Red = 4;
const int Green = 5;
const int Full = 6;
const long interval = 500;

// Variables;

int i = 0;
int redState = HIGH;
int greenState = LOW;
int fullState = LOW;
int lastFullState = LOW;
int barrierState = LOW; // What state is down?
int carCount = 0;
int fullBlinkTriggered = false; // used to tell the loop to blink full sign for 5 seconds.
int fullStateCount = 0;  // used to count how many time the sign has blinked. 
unsigned long previousMillis = 0;
unsigned long currentMillis = millis();

void setup() {
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(Green, OUTPUT);
  pinMode(Red, OUTPUT);
  pinMode(Full, OUTPUT);
  digitalWrite(Green, greenState);
  digitalWrite(Full, fullState);
  digitalWrite(Red, redState);
}

void loop() {
  if (digitalRead(S1) == HIGH) newCar();      // need to debounce

  if (digitalRead(S3) == HIGH) carLeaving();  // need to debounce

  if ( fullBlinkTriggered == true ) {
    
    if (fullState != lastFullState) {
        int fullStateCount = fullStateCount + 1;
      };
      
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
      
      if ( fullStateCount >= 11 ){
        int fullStateCount = 0;
        fullBlinkTriggered = false;
      };
    };
  };
}  
  


void newCar() {
  if (carCount < 5) {
    openBarrier();
  } else {
    int fullBlinkTriggered = true;
  };

}

void openBarrier() {
  // open barrier
  digitalWrite(Red, LOW);
  digitalWrite(Green, HIGH);
  if (digitalRead(S1) == LOW) {
    if (digitalRead(S2) == HIGH) { //rework to look for a brief high.
      closeBarrier();
    };
  };
}

void closeBarrier() {
  carCount = carCount + 1;
  if ( carCount >= 5 ) {
    digitalWrite( Full, HIGH );
  };
  digitalWrite(Red, HIGH);
  digitalWrite(Green, LOW);
  // close barrier
}

void carLeaving() {
  carCount = carCount - 1;
  digitalWrite(Full, LOW);
}








/*
  Stepper Motor Control - one revolution

  This program drives a unipolar or bipolar stepper motor.
  The motor is attached to digital pins 8 - 11 of the Arduino.

  The motor should revolve one revolution in one direction, then
  one revolution in the other direction.


  Created 11 Mar. 2007
  Modified 30 Nov. 2009
  by Tom Igoe

  s1 on 1
  s2 on 2
  s3 on 3
  green on 5
  red on 4
  full on 6

*/
/*
  #include <Stepper.h>

  const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
  // for your motor

  // initialize the stepper library on pins 8 through 11:
  Stepper myStepper(stepsPerRevolution, 8, 11, 12, 13);

  void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  }

  void loop() {
  // step one revolution  in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500);
  }

*/

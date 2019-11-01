#include <Ultrasonic.h>

// Pinos Led
int pinRed = 9;
int pinGreen = 10;
int pinBlue = 11;

// Pinos Ultra
int trig = 6;
int echo = 5;

// Pinos LDR
int ldr = 4;

// Configuração
int distStep = 51 / 4;
int lumiStep = 1023 / 3;
String cmdLDR = "luz";
String cmdUltra = "ultra";

// Inicializações
Ultrasonic ultra(trig, echo);

// Estáticos
int dist;
int lumi;
String cmd;

void setup() {
  Serial.begin(9600);
  
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
}

void loop() {
  readInput();
  handleTask();
}

void readInput() {
  if (Serial.available()) {
    cmd = Serial.readString();
  }
}

void readLumi() {
  lumi = analogRead(ldr);
}

void readDist() {
  dist = ultra.Ranging(CM);
}

void handleTask() {
  if (cmd == cmdUltra) {
    Serial.println(dist);
    doUltra();
  } else if (cmd == cmdLDR) {
    Serial.println(lumi);
    doLDR();
  } else {
    cmd = "ultra";
  }
}

void doUltra() {
  readDist();

  if (dist <= distStep) {
    doRed();
  } else if (dist <= distStep * 2) {
    doGreen();
  } else if (dist <= distStep * 3) {
    doBlue();
  }
}

void doLDR() {
  readLumi();

  if (lumi <= lumiStep) {
    doPurple();
  } else if (lumi <= lumiStep * 2) {
    doYellow();
  } else if (lumi <= lumiStep * 3) {
    doWhite();
  }
}


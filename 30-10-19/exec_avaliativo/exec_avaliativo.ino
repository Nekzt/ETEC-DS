#include <LiquidCrystal.h>
#include <Ultrasonic.h>

int trig = 7;
int echo = 6;

int pinRed = 8;
int pinGreen = 9;
int pinBlue = 10;

int refreshRate = 300;
int maxDist = 51;
int distSteps = 4;
int distStep = maxDist / distSteps;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Ultrasonic ultra(trig, echo);

String curColor;
int dist;

void setup() {
  lcd.begin(16, 2);
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
  curColor = blue();
}

void loop() {
  getDist();
  setLight();
  
  showColorLCD();
  showDistLCD();
  
  delay(refreshRate);
  garbageCollect();
}

void garbageCollect() {
  lcd.clear();
}

void getDist() {
  dist = ultra.Ranging(CM);
}

void setLight() {
  if (dist <= distStep) {
    curColor = red();
  } else if (dist <= distStep * 2) {
    curColor = green();
  } else if (dist <= distStep * 3) {
    curColor = blue();
  }
}

void showColorLCD() {
  lcd.setCursor(0,0);
  lcd.print("Cor: ");
  lcd.print(curColor);
}

void showDistLCD() {
  lcd.setCursor(0,1);
  lcd.print("Distancia: ");
  lcd.print(dist);
  lcd.print(" cm");
}

String red() {
  digitalWrite(pinRed, 1);
  digitalWrite(pinGreen, 0);
  digitalWrite(pinBlue, 0);
  return "vermelho";
}

String green() {
  digitalWrite(pinRed, 0);
  digitalWrite(pinGreen, 1);
  digitalWrite(pinBlue, 0);
  return "verde";
}

String blue() {
  digitalWrite(pinRed, 0);
  digitalWrite(pinGreen, 0);
  digitalWrite(pinBlue, 1);
  return "azul";
}

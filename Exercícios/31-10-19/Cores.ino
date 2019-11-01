void light(int pin, int mode) {
  analogWrite(pin, mode);
}

void doRandomColor() {
  light(pinRed, random(0, 255));
  light(pinGreen, random(0, 255));
  light(pinBlue, random(0, 255));
}

void doRed() {
  light(pinRed, 255);
  light(pinGreen, 0);
  light(pinBlue, 0);
}

void doGreen() {
  light(pinRed, 0);
  light(pinGreen, 255);
  light(pinBlue, 0);
}

void doBlue() {
  light(pinRed, 0);
  light(pinGreen, 0);
  light(pinBlue, 255);
}

void doWhite() {
  light(pinRed, 255);
  light(pinGreen, 255);
  light(pinBlue, 255);
}

void doYellow() {
  light(pinRed, 255);
  light(pinGreen, 40);
  light(pinBlue, 0);
}

void doPurple() {
  light(pinRed, 127);
  light(pinGreen, 0);
  light(pinBlue, 255);
}

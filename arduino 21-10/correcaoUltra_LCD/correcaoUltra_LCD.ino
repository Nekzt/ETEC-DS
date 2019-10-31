#include <Ultrasonic.h>
#include <LiquidCrystal.h> //Carrega a biblioteca LiquidCrystal

int trig = 9;
int echo = 7;
int distancia;
int buzzer = 8;

//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //RS,E,D4,D5,D6,D7
Ultrasonic ultra(trig, echo);

void setup() {
  lcd.begin(16, 2);
  pinMode(buzzer, OUTPUT);
}

void loop() {

  lcd.setCursor(4, 0);
  lcd.print("Tecnico em");
  lcd.setCursor(6, 1);
  lcd.print("DS");
  delay(1000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Atividade");
  lcd.setCursor(0, 1);
  lcd.print("ULTRA - BUZZER");
  delay(1000);
  lcd.clear();

  distancia = ultra.Ranging(CM);

  lcd.setCursor(0, 0);
  lcd.print("Distancia");
  lcd.print(distancia);
  lcd.print("CM");

  if (distancia > 45) {
    lcd.setCursor(0, 1);
    lcd.print("Prosseguir");
    noTone(buzzer);
  }
  else if (distancia < 45 && distancia > 25) {
    lcd.setCursor(0, 1);
    lcd.print("Atencao");
    tone(buzzer,1500);
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print("Parar");
    tone(buzzer,2500);
  }

  delay(1000);
  lcd.clear();

}

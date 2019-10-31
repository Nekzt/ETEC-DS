#include <Ultrasonic.h>

// inicia a biblioteca do ultrasonic
Ultrasonic ultrasonic(9, 8);

// define o ldr, ultra e buzzer
int ldr = 4;
int ultra = 8;
int buzz = 3;

// define os pinos led
int lr = 11; // vermelho
int lg = 13; // verde
int ly = 12; // amarelo

// variaveis inteiras para a distancia e luz
int dist;
int luz;

// inicia os pinos e o ldr
void setup() {
  pinMode(lr, OUTPUT);
  pinMode(lg, OUTPUT);
  pinMode(ly, OUTPUT);
  pinMode(ldr, INPUT);

  Serial.begin(9600);
}

void loop() {
	// definição da luz e distancia
	dist = ultrasonic.Ranging(CM);
	luz = analogRead(ldr);
  
	// tone
	if (dist > 45) {
		noTone(buzz);
	else if (dist > 35) {
		tone(buzz, 500);
	else if (dist > 25) {
		tone(buzz, 300);
	else if (dist > 15) {
		tone(buzz, 100);
	else if (dist <= 15) {
		tone(buzz, 25);
	}
	
	// verifica luz ou distancia para acender os leds
	if (luz < 200 || dist < 50) {    
		digitalWrite(lr, 1);
		digitalWrite(lg, 1);
		digitalWrite(ly, 1);
	// caso não estiver aceso ou a distancia for grande, apaga os leds
	} else {  
		digitalWrite(lr, 0);
		digitalWrite(lg, 0);
		digitalWrite(ly, 0);
	}
}

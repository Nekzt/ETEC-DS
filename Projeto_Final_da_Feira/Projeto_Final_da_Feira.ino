#include <Servo.h> // Biblioteca do Servo Motor
#include <Ultrasonic.h> // Biblioteca do Ultrasonic

// Pinos
int pinoServ = A0; // Servo
int pinoTrig = A1; // Trigger do Ultrasonic
int pinoEcho = A2; // Echo do Ultrasonic

// Configuração
int ticksFechado = 100; // Tempo que o servo mantem a tampa fechada
int ticksAberto = 10; // Tempo que o servo mantem a tampa berta
int delayTick = 5; // Tempo entre a alteração de rotação do Servo
int distAgir = 20; // Distancia necessária (ou menor) para acionar o dispositivo
int grauFechado = 65; // Grau que define o modo fechado
int grauAberto = 40; // Grau que define o modo aberto

// Inicialização externa
Servo servo; // Cria um novo objeto Servo para ser utilizado
Ultrasonic ultrasonic(pinoTrig, pinoEcho); // Inicia o Ultrasonic no Trigger e no Echo

// Dinâmicas
bool aberto = false; // Inicializa o dispostivo em modo "fechado"
int dist; // Contador de distância do Ultrasonic
int ticks; // Contador de ticks (1 tick = 1 loop total)
int pos; // Variável para cuidar da posição durante a transição

void setup() {
  servo.attach(pinoServ); // Configura o pino para o servo
  servo.write(grauFechado); // Define a rotação do servo para o grau fechado
  Serial.begin(9600); // Inicializa o canal do console em 9600
}

void loop() {
  dist = ultrasonic.Ranging(CM); // Faz a leitura da distância do Ultrasonic

  if (aberto == true) { // Caso estiver aberto, mostra a leitura em modo aberto
    Serial.print(ticks);
    Serial.println("-ts aberto");
  } else {
    Serial.print(ticks); // Caso estiver fechado, mostra a leitura em modo fechado
    Serial.println("-ts fechado");
  }
  
  if (aberto == false && dist <= distAgir && ticks >= ticksFechado) { // Caso estiver fechado, dentro da distância, e os ticks mínimos necessários passarem, abre
    aberto = true; // Define o dispositivo para modo aberto
    ticks = 0; // Reseta os ticks para serem reciclados na próxima checagem

    //int pos; // Faz o loop de for para abrir o dispositivo
    for (pos = grauFechado; pos >= grauAberto; pos = pos - 1){
      servo.write(pos);
      delay(delayTick);
    }
  } else if (aberto == true && ticks >= ticksAberto) {
    aberto = false; // Define o dispositivo para modo aberto
    ticks = 0; // Reseta os ticks para serem reciclados na próxima checagem

    //int pos; // Faz o loop de for para fechar o dispositivo
    for (pos = grauAberto; pos <= grauFechado; pos = pos + 1){
      servo.write(pos);
      delay(delayTick);
    }
  }

  ticks = ticks + 1; // Atribui um tick (após um loop completo) á variável
}

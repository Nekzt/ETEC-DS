// Inclui as bibliotecas necessárias
#include <Keypad.h>
#include <Servo.h>

// Cria um objeto de referência ao servo
Servo servo;

// Variáveis estáticas
String senha = "456";
int abrir = 90;
int fechar = -90;
int passo = 5;

int somNumerico = 10000;
int durNumerico = 50;

int somFuncoes = 4050;
int durFuncoes = 100;

int somNotificar = 6000;
int durNotificar = 100;
int delayNotificar = 150;

// Referências aos pinos utilizados
int pinoVerd = 7;
int pinoVerm = 2;
int pinoServ = 12;
int pinoBuzz = 13;

// Cria uma matriz 4x4 para o teclado
const byte qtdLinhas = 4;
const byte qtdColunas = 4;

char matrizTeclas[qtdLinhas][qtdColunas] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinosLinhas[qtdLinhas] = {3, 4, 5, 6};
byte pinosColunas[qtdColunas] = {8, 9, 10, 11};

// Variáveis dinâmicas
String teclasUsadas = "";
bool aberto = false;
bool aceso = false;

// Cria um objeto de referência ao teclado numérico
Keypad teclado = Keypad(makeKeymap(matrizTeclas), pinosLinhas, pinosColunas, qtdLinhas, qtdColunas);

void setup(){
  // Inicializa o servo em modo fechado
  servo.write(fechar);
  servo.attach(pinoServ);

  // Inicializa os leds
  pinMode(pinoVerd, OUTPUT);
  pinMode(pinoVerm, OUTPUT);
  pinMode(pinoBuzz, OUTPUT);

  // Inicializa o canal 9600 e acende a luz vermelha e apaga a verde
  Serial.begin(9600);
  digitalWrite(pinoVerm, 1);
  digitalWrite(pinoVerd, 0);
  aceso = false;
}

void loop(){
  // Cria uma variável para quando uma tecla for iniciada
  char teclaUsada = teclado.getKey();

  // Caso a tecla "A" for apertada
  if (teclaUsada == 'A'){
    tone(pinoBuzz, somFuncoes, durFuncoes);

  // Caso a tecla "B" for apertada
  } else if (teclaUsada == 'B'){
    tone(pinoBuzz, somFuncoes, durFuncoes);
    
  // Caso a tecla "C" for apertada
  } else if (teclaUsada == 'C'){
    tone(pinoBuzz, somFuncoes, durFuncoes);
    
    teclasUsadas = "";
    digitalWrite(pinoVerm, 1);
    digitalWrite(pinoVerd, 0);
    aceso = false;
    Serial.println("Reset");

  // Caso a tecla "D" for apertada
  } else if (teclaUsada == 'D'){
    tone(pinoBuzz, somFuncoes, durFuncoes);
    
  // Caso qualquer outra tecla for apertada
  } else if (teclaUsada) {
    tone(pinoBuzz, somNumerico, durNumerico);
    
    teclasUsadas = teclasUsadas + teclaUsada;
    Serial.println(teclasUsadas);
  }

  // Caso estiver aberto ou puder abrir, indica com a luz verde
  if ((aberto == false && teclasUsadas == senha) || aberto == true) {
    if (aceso == false){
      aceso = true;

      tone(pinoBuzz, somNotificar, durNotificar);
      delay(delayNotificar);
      tone(pinoBuzz, somNotificar, durNotificar);
      delay(delayNotificar);
      tone(pinoBuzz, somNotificar, durNotificar);
      delay(delayNotificar);
    }
    
    digitalWrite(pinoVerm, 0);
    digitalWrite(pinoVerd, 1);
  }
  

  // Caso puder abrir, a senha estiver correta e a função "A" for apertada, abre
  if (teclasUsadas == senha && aberto == false && teclaUsada == 'A') {
    // Reseta as variáveis dinâmicas
    aberto = true;
    teclasUsadas = "";

    // Rotaciona o servo para abrir
    int pos;
    for (pos = fechar; pos <= abrir; pos += 1){
      servo.write(pos);
      delay(passo);
    }

    // Indica que o servo está aberto
    Serial.println("Aberto");
    
  // Caso estiver aberto e a tecla "B" for apertada, fecha
  } else if (aberto == true && teclaUsada == 'B') {
    // Reseta as variáveis dinâmicas
    aberto = false;
    teclasUsadas = "";

    // Acende a luz vermelha e apaga a verde
    digitalWrite(pinoVerm, 1);
    digitalWrite(pinoVerd, 0);
    aceso = false;

    // Rotaciona o servo para fechar
    int pos;
    for (pos = abrir; pos >= fechar; pos -= 1){
      servo.write(pos);
      delay(passo);
    }

    // Indica que o servo está fechado
    Serial.println("Fechado");
    
  }
}


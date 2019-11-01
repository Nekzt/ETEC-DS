// Bibliotecas utilizadas
#include <Servo.h> // Biblioteca Servo para movimentar o motor
#include <Ultrasonic.h> // Biblioteca Ultrasonic para medir a distância
#include <LiquidCrystal.h> // Biblioteca Liq. Crystal para o visor digital
#include <Keypad.h> // Biblioteca Keypad para o teclado númerico

// Pinos
int pinoServo = A0; // Pino do Servo
int pinoTrigger = A1; // Pino Trigger do Ultrasonic
int pinoEcho = A2; // Pino Echo do Ultrasonic
int pinoBuzzer = A3; // Pino Buzzer

// Configuração do Display
int lcdColunas = 16; // Número de colunas do Display
int lcdLinhas = 2; // Número de linhas do Display
int lcdLimparMonitor = 10; // Taxa de atualização para limpar o Display

// Configuração do Keypad
const byte keypadLinhas = 4; // Número de linhas do teclado
const byte keypadColunas = 4; // Número de colunas do teclado
byte keypadPinosLinhas[keypadLinhas] = {6, 7, 8, 9}; // Pinos referentes as linhas
byte keypadPinosColunas[keypadColunas] = {2, 3, 4, 5}; // Pinos referentes as colunas

// Configuração do Servo
int tsFechado = 300; // Tempo que o servo mantem a tampa fechada
int tsAberto = 10; // Tempo que o servo mantem a tampa berta
int msPorGrau = 10; // Tempo entre a alteração de rotação do Servo
int grausFechado = 70; // Grau que define o modo fechado
int grausAberto = 40; // Grau que define o modo saidaAberta

// Configuração do Ultrasonic
int distMinima = 25; // Distancia necessária (ou menor) para acionar o dispositivo

// Configuração do Buzzer
int keypadSomNumerico = 10000; // Som refente a tecla numérica
int keypadDurSomNumerico = 50; // Duração do som respectivo

int keypadSomFuncoes = 4050; // Som referente as letras do teclado
int keypadDurSomFuncoes = 100; // Duração do som respectivo 

// Inicialização externa
Servo servo; // Cria um novo objeto Servo para ser utilizado

// Inicia o Ultrasonic no Trigger e no Echo
Ultrasonic ultrasonic(pinoTrigger, pinoEcho); // Cria um novo objeto para o Ultrasonic

// Inicia o visor para o Display
LiquidCrystal lcd(10, 11, 12, 13, A5, A4); // Cria um novo objeto para o Display

// Matriz do teclado numérico
char keypadMatriz[keypadLinhas][keypadColunas] = { // Matriz do Teclado Numérico
  {'D','#','0','*'},
  {'C','9','8','7'},
  {'B','6','5','4'},
  {'A','3','2','1'}
};

// Cria um objeto de referência ao teclado numérico
Keypad teclado = Keypad(makeKeymap(keypadMatriz), keypadPinosLinhas, keypadPinosColunas, keypadLinhas, keypadColunas);

// Dinâmicas
String teclasUsadas; // Variável para guardar quais teclas foram apertadas até o momento
bool saidaAberta = false; // Inicializa o dispostivo em modo "fechado"
bool modoEdicao = false; // Define se está no modo de edição ou não
int distUltra; // Contador de distância do Ultrasonic
int tsAtual; // Contador de tsAtual (1 tick = 1 loop total)
int posAtual; // Variável para cuidar da posição durante a transição
int parteMenu = 1; // Define qual parte do menu estamos acessando
int modeloUsado = 1; // Define qual modelo está sendo utilizado
int lcdTs; // Contador para calcular o tempo de limpar o Display

void setup() {
  // Inicializa o Servo
  servo.attach(pinoServo); // Configura o pino para o servo
  servo.write(grausFechado); // Define a rotação do servo para o grau fechado

  // Inicializa o Display
  lcd.begin(lcdColunas, lcdLinhas); // Inicializa o Display com o número de colunas e linhas
  lcd.clear(); // Limpa a tela do Display
  
  // Inicializa o monitor de serial
  Serial.begin(9600); // Inicializa o canal do console em 9600
}

void loop() {
  // Partição do teclado numérico
  char teclaUsada = teclado.getKey(); // Faz a leitura da tecla atual sendo pressionada no teclado
  
  if (teclaUsada == 'A'){ // Caso a tecla "A" for apertada
    tone(pinoBuzzer, keypadSomFuncoes, keypadDurSomFuncoes);
    
    if (modeloUsado == 1) { // Cria a alternância para o modelo de grande e pequeno porte
      lcd.clear();
      modeloGrandePorte();
      modeloUsado = 2;
      lcd.print("Grande porte");
      delay(1500);
    } else if (modeloUsado == 2) {
      lcd.clear();
      modeloPequenoPorte();
      modeloUsado = 1;
      lcd.print("Pequeno porte");
      delay(1500);
    }
    
  } else if (teclaUsada == 'B'){ // Caso a tecla "B" for apertada
    tone(pinoBuzzer, keypadSomFuncoes, keypadDurSomFuncoes);

    // Faz a confirmação dos números digitados
    if (teclasUsadas == "") {
      lcd.clear();
      lcd.print("Digite um valor!");
      delay(2000);
      lcd.clear();
      
    } else {
      if (parteMenu == 1) {
        tsFechado = teclasUsadas.toInt();
      } else if (parteMenu == 2) {
        tsAberto = teclasUsadas.toInt();
      } else if (parteMenu == 3) {
        msPorGrau = teclasUsadas.toInt();
      } else if (parteMenu == 4) {
        distMinima = teclasUsadas.toInt();
      }
      teclasUsadas = ""; // Limpa as teclas usadas
    }
    
  } else if (teclaUsada == 'C'){ // Caso a tecla "C" for apertada
    tone(pinoBuzzer, keypadSomFuncoes, keypadDurSomFuncoes); // Emite um som de efeito para o Keypad
    teclasUsadas = ""; // Limpa as teclas usadas
    
  } else if (teclaUsada == 'D'){ // Caso a tecla "D" for apertada
    tone(pinoBuzzer, keypadSomFuncoes, keypadDurSomFuncoes); // Emite um som de efeito para o Keypad
    if (modoEdicao == true) {
      modoEdicao = false; // Sai do modo de edição
      lcd.noDisplay();
    } else if (modoEdicao == false) {
      modoEdicao = true; // Sai do modo de edição
      lcd.display();
    }
  } else if (teclaUsada == '*'){ // Caso a tecla "*" for apertada
    if (modoEdicao == true) {
      tone(pinoBuzzer, keypadSomFuncoes, keypadDurSomFuncoes); // Emite um som de efeito para o Keypad
      lcd.clear(); // Limpa o Display
      parteMenu += 1; // Passa para a próxima página do menu
      checarMenu(); // Verifica os limites do menu
      teclasUsadas = ""; // Limpa as teclas digitadas
    }
    
  } else if (teclaUsada == '#'){ // Caso a tecla "#" for apertada
    if (modoEdicao == true) {
      tone(pinoBuzzer, keypadSomFuncoes, keypadDurSomFuncoes); // Emite um som de efeito para o Keypad
      lcd.clear(); // Limpa o Display
      parteMenu -= 1; // Passa para a página anterior do menu
      checarMenu(); // Verifica os limites do menu
      teclasUsadas = ""; // Limpa as teclas digitadas
    }
    
  } else if (teclaUsada) { // Caso qualquer outra tecla for apertada
    tone(pinoBuzzer, keypadSomNumerico, keypadDurSomNumerico); // Emite um som de efeito para o Keypad
    teclasUsadas += teclaUsada;
  }

  // Partição do menu de exibição
  lcdTs += 1; // Adiciona uma unidade ao contador
  if (fmod(lcdTs, lcdLimparMonitor) == 0) { // Faz um calculo simples para definir uma "taxa" de atualização do Display
    lcd.clear(); // Limpa o monitor
  }

  // Exibição do menu
  if (modoEdicao == true) {
    if (parteMenu == 1) {
      lcd.setCursor(0, 0);
      lcd.print("Fechado (ts): ");
      lcd.setCursor(0, 1);
      lcd.print(tsFechado);
    } else if (parteMenu == 2) {
      lcd.setCursor(0, 0);
      lcd.print("Aberto (ts): ");
      lcd.setCursor(0, 1);
      lcd.print(tsAberto);
    } else if (parteMenu == 3) {
      lcd.setCursor(0, 0);
      lcd.print("Rotativo (ms): ");
      lcd.setCursor(0, 1);
      lcd.print(msPorGrau);
    } else if (parteMenu == 4) {
      lcd.setCursor(0, 0);
      lcd.print("Distancia (cm): ");
      lcd.setCursor(0, 1);
      lcd.print(distMinima);
    }
  }
  
  // Partição da medição de distância
  distUltra = ultrasonic.Ranging(CM); // Faz a leitura da distância do Ultrasonic
  
  // Inicio da lógica do Servo
  delay(2);
  
  if (saidaAberta == false && distUltra <= distMinima && tsAtual >= tsFechado) { // Caso estiver fechado, dentro da distância, e os tsAtual mínimos necessários passarem, abre
    saidaAberta = true; // Define o dispositivo para modo saidaAberta
    tsAtual = 0; // Reseta os tsAtual para serem reciclados na próxima checagem
    
    for (posAtual = grausFechado; posAtual >= grausAberto; posAtual = posAtual - 1){
      servo.write(posAtual);
      delay(msPorGrau);
    }
  } else if (saidaAberta == true && tsAtual >= tsAberto) {
    saidaAberta = false; // Define o dispositivo para modo saidaAberta
    tsAtual = 0; // Reseta os tsAtual para serem reciclados na próxima checagem
    
    for (posAtual = grausAberto; posAtual <= grausFechado; posAtual = posAtual + 1){
      servo.write(posAtual);
      delay(msPorGrau);
    }
  }

  tsAtual = tsAtual + 1; // Atribui um tick (após um loop completo) á variável
}

void checarMenu() {
  if (parteMenu > 4) {
    parteMenu = 1;
  } else if (parteMenu < 1) {
    parteMenu = 4;
  }
}

void modeloPequenoPorte() { // Cria o modelo padrão para o pequeno porte
  tsFechado = 300;
  tsAberto = 10;
  msPorGrau = 10;
  distMinima = 25;
}

void modeloGrandePorte() { // Cria o modelo padrão para o grande porte porte
  tsFechado = 300;
  tsAberto = 40;
  msPorGrau = 10;
  distMinima = 50;
}

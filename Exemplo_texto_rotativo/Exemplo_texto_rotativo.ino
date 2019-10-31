#include <LiquidCrystal.h>

LiquidCrystal lcd(1, 2, 8, 9, 10, 11); // Cria um novo objeto para o Display
int lcdColunas = 16; // Número de colunas do Display
int lcdLinhas = 2; // Número de linhas do Display
int lcdShift = 16; // Número de passos que o Display vai dar
int i = 0;

void setup() {
  // Inicializa o Display
  lcd.begin(lcdColunas, lcdLinhas); // Inicializa o Display com o número de colunas e linhas
  lcd.clear(); // Limpa a tela do Display
}

void loop() {
  i = 0;
  lcd.clear(); // Limpa o monitor
  lcd.setCursor(0, 0); // Move para a coluna 0, linha 0
  typeWrite("Ola amigos!");
  delay(1000); // Aguarda
  
  for (i = i; i < lcdShift; i++){
    lcd.scrollDisplayLeft();
    delay(100);
  }

  for (i = 16; i >= -16; i--){
    lcd.scrollDisplayRight();
  }

  for (i = -16; i <= 0; i++){
    lcd.scrollDisplayLeft();
    delay(100);
  }

  delay(1000);
  lcd.clear(); // Limpa o monitor
  delay(500);
}

void typeWrite(char* text)
{
  while(text[0]){
    lcd.print(text++[0]);
    delay(50);
  }
}

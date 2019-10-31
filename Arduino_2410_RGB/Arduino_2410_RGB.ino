int pinoVermelho = 11;
int pinoVerde = 9;
int pinoAzul = 10;

int tempo = 500;
String comando;
bool ativo = true;

void setup()
{
  Serial.begin(9600);
  pinMode(pinoVermelho, OUTPUT);
  pinMode(pinoVerde, OUTPUT);
  pinMode(pinoAzul, OUTPUT);
}

void loop()
{
  if (Serial.available()) {
    comando = Serial.readString();

    if (comando == "on") {
      ativo = true;
    } else if (comando == "off") {
      ativo = false;
    } else if (comando == "azul") {
      azul();
    } else if (comando == "vermelho") {
      vermelho();
    } else if (comando == "verde") {
      verde();
    } else if (comando == "roxo") {
      roxo();
    } else if (comando == "amarelo") {
      amarelo();
    }

    delay(1000);
  } else if (ativo == true) {
    aleatorio();
    delay(tempo);
  }
}


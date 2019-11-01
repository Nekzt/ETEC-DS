void luz(int pino, int modo) {
  analogWrite(pino, modo);
}

void vermelho() {
  luz(pinoVermelho, 255);
  luz(pinoVerde, 0);
  luz(pinoAzul, 0);
}

void verde() {
  luz(pinoVermelho, 0);
  luz(pinoVerde, 255);
  luz(pinoAzul, 0);
}

void azul() {
  luz(pinoVermelho, 0);
  luz(pinoVerde, 0);
  luz(pinoAzul, 255);
}

void amarelo() {
  luz(pinoVermelho, 255);
  luz(pinoVerde, 40);
  luz(pinoAzul, 0);
}

void roxo() {
  luz(pinoVermelho, 127);
  luz(pinoVerde, 0);
  luz(pinoAzul, 255);
}

void aleatorio() {
  luz(pinoVermelho, random(0, 255));
  luz(pinoVerde, random(0, 255));
  luz(pinoAzul, random(0, 255));
}


int r  = 11; // led azul
int g = 9; // led vermelha
int b = 10; // led verde

void setup() {
  pinMode(r, OUTPUT); 
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
}

void loop() {
  for (int rc = 0; rc <= 255; rc += 50){
    for (int gc = 0; gc <= 255; gc += 50) {
      for (int bc = 0; bc <= 255; bc += 50) {
        analogWrite(r, rc);
        analogWrite(g, gc);
        analogWrite(b, bc);
      }
    }
  }
}

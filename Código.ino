const int ledRojo = 13;        
const int pulsadorSumarDos = 3; 
const int pulsadorSumarUno = 2; 
const int pulsadorReiniciar = 1;  
const int pulsadorNegativo = 0; 
bool modoNegativo = false; 
int numero = 0; 

void setup() {
  pinMode(ledRojo, OUTPUT);
  pinMode(pulsadorSumarDos, INPUT_PULLUP);
  pinMode(pulsadorSumarUno, INPUT_PULLUP);
  pinMode(pulsadorReiniciar, INPUT_PULLUP);
  pinMode(pulsadorNegativo, INPUT_PULLUP); 

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  digitalWrite(ledRojo, LOW); 
}

void loop() {
  int estadoSumarDos = digitalRead(pulsadorSumarDos);
  int estadoSumarUno = digitalRead(pulsadorSumarUno);
  int estadoApagar = digitalRead(pulsadorReiniciar);
  int estadoNegativo = digitalRead(pulsadorNegativo);
  
  if (estadoNegativo == HIGH) {
    modoNegativo = true;  
    delay(200);  
  }
  
  if (estadoSumarDos == HIGH) {
    numero += 2;
    delay(200); 
  }
  
  if (estadoSumarUno == HIGH) {
    numero++;
    delay(200); 
  }
  
  if (estadoApagar == HIGH) {
    apagarLuces();
    delay(200); 
  }

  procesarNumero();  
}

void procesarNumero() {
  int numeroMostrar = numero;

  if (modoNegativo) {
    numeroMostrar = numeroMostrar & 0x0F;
    numeroMostrar = complementoADos(numeroMostrar); 
    if (numeroMostrar == 8 && digitalRead(ledRojo) == LOW && digitalRead(12) == HIGH){
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);
      digitalWrite(10, LOW);
      digitalWrite(9, LOW);
      digitalWrite(ledRojo, HIGH); 
      delay(1500);
      apagarLuces();
    }
  }

  actualizarLuces(numeroMostrar);
  verificarOverflow();
}

void actualizarLuces(int numeroMostrar) {
  for (int i = 0; i < 4; i++) {
    int bit = (numeroMostrar >> i) & 1; 
    digitalWrite(9 + i, bit == 1 ? HIGH : LOW);
  }
}

void apagarLuces() {
  for (int i = 9; i <= 12; i++) {
    digitalWrite(i, LOW);
  }
  
  digitalWrite(ledRojo, LOW);
  numero = 0;
  modoNegativo = false;  
}

void verificarOverflow() {
  if (numero > 15) {  
    digitalWrite(ledRojo, HIGH);
    delay(1500);
    apagarLuces();
  } else {
    digitalWrite(ledRojo, LOW);
  }
}

int complementoADos(int n) {
  return (~n + 1) & 0x0F;
}

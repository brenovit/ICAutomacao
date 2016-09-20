#include "header.h"

void ligarLampada(int pino){
  digitalWrite(pino, HIGH); 
}

void desligarLampada(int pino){
  digitalWrite(pino, LOW); 
}

int estaLigado(int pino){
  return digitalRead(pino);
}


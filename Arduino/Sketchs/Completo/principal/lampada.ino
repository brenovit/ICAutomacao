#include "header.h"

void ligarLampada(int pino){
  digitalWrite(pino, HIGH);
  //informar que a lampada pino, foi ligada
}

void desligarLampada(int pino){
  digitalWrite(pino, LOW); 
  //informar que a lampada pino, foi desligada
}

int estaLigado(int pino){
  return digitalRead(pino);
  //informar que a lampada pino está ligada
}


#include "header.h"

int mVperAmp = 185; 
int RawValue = 0;
int ACSoffset = 2500;
double Voltage = 0;
double Amps = 0;

void ligarLampada(int pino){
  digitalWrite(pino, HIGH);
  //informar que a lampada pino, foi ligada
}

void desligarLampada(int pino){
  digitalWrite(pino, LOW); 
  //informar que a lampada pino, foi desligada
}

int temPulso(int pino){
  return digitalRead(pino);
  //informar que a lampada pino está ligada
}

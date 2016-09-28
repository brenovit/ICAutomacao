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

int estaLigado(int pino){
  return digitalRead(pino);
  //informar que a lampada pino está ligada
}

void Calcula_corrente()
{
  RawValue = analogRead(sCorrente);
  Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
  Amps = ((Voltage - ACSoffset) / mVperAmp);
  delay(2000);
}

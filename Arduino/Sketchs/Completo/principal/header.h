#define lampada1 1
#define lampada2 2
#define lampada3 3
#define SPir 4
#define sCorrente 5

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>
//#include <IRremote.h>

//RF24 radio(7, 8);

void ligarLampada(int lampada);
void desligarLampada(int lampada);
int estaLigado(int lampada);

bool enviarMensagem(char message);
char receberMensagem();

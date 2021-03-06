#define lampada1 1
#define lampada2 2
#define lampada3 3
#define SPir1 4
#define SPir2 5
#define sCorrente1 A0
#define sCorrente2 A1
#define sCorrente3 A2

#include <SPI.h>
#include <RF24.h>
#include <printf.h>
#include <IRremote.h>
#include <nRF24L01.h>

void ligarLampada(int lampada);
void desligarLampada(int lampada);

int temPulso(int lampada);

bool temGente(int pir);

bool enviarMensagem(char message);
void receberMensagem();

void checarCodigo(char codigo);

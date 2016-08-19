#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#define buzzer 4

//Armazena os dados enviados
int dados[1];

//Inicializa a placa nos pinos 7 (CE) e 8 (CS) do Arduino
RF24 radio(7,8);

//Define o endereco para comunicacao entre os modulos
const uint64_t pipe = 0xE14BC8F482LL;

//Define os pinos dos botoes

void setup()
{
  //Inicializa a serial
  Serial.begin(57600);
  Serial.println("Pressione botao 1 ou 2 para iniciar a comunicacao...");
  
  //Inicializa a comunicacao
  radio.begin();
  //Entra em modo de transmissao
  radio.openWritingPipe(pipe);
}

void loop()
{  
  String texto = "";
  if(Serial.available()){
    texto = Serial.readString();
    Serial.println("Digitou:" + texto);    
  }
    
  //Envia o numero 1 caso o botao1 seja pressionado
  if (texto == "1")
  {
    Serial.println("Botao 1 pressionado !");
    dados[0] = 1;
    radio.write(dados, 1);
  }
  
  //Envia o numero 2 caso o botao2 seja pressionado
  if (texto == "2")
  {
    Serial.println("Botao 2 pressionado !");
    dados[0] = 2;
    radio.write(dados, 1);
  }
}

void tocar(int nota, int atraso) {
  tone(buzzer, nota);
  delay(atraso);
  //Desligando o buzzer.
  noTone(buzzer);
  delay(atraso);
}

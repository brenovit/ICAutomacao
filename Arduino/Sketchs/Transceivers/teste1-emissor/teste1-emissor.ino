//Programa : Teste NRF24L01 - Emissor - Botoes
//Autor : Adilson Thomsen

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//Armazena os dados enviados
int dados[1];

//Inicializa a placa nos pinos 9 (CE) e 10 (CS) do Arduino
RF24 radio(9,10);

//Define o endereco para comunicacao entre os modulos
const uint64_t pipe = 0xE14BC8F482LL;

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
  //Envia o numero 1 caso o botao1 seja pressionado
  if(Serial.available()){
    String letra = Serial.readString();
    Serial.println("Comando: "+letra);    
    if(letra == "1"){
      dados[0] = 1;
      radio.write(dados, 1);
    }
    if(letra == "2"){
      dados[0] = 2;
      radio.write(dados, 1);
    }
  }  
}

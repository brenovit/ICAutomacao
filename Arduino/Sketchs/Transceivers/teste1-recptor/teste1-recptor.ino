//Programa : Teste NRF24L01 - Receptor - Led
//Autor : Adilson Thomsen

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//Armazena os dados recebidos
int recebidos[1];

//Inicializa a placa nos pinos 9 (CE) e 10 (CS) do Arduino
RF24 radio(9,10);

//Define o endereco para comunicacao entre os modulos
const uint64_t pipe = 0xE14BC8F482LL;

void setup()
{
  //Inicializa a serial
  Serial.begin(57600);
  
  //Inicializa a comunicacao
  radio.begin();
  //Entra em modo de recepcao
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}

void loop()
{
  //Verifica se ha sinal de radio
  if (radio.available())
  {
    bool done = false;    
    while (!done)
    {
      done = radio.read(recebidos, 1);
      Serial.print("Dados recebidos : ");    
      Serial.println(recebidos[0]);
      
      //Se recebeu o numero 1, acende o LED1
      if (recebidos[0] == 1)
      {
        delay(10);
        Serial.print("Recebi ");
        Serial.println(recebidos[0]);
      }
      else 
      {
        Serial.print("Recebi ");
        Serial.println(recebidos[0]);
      }
      
      //Se recebeu o numero 2, acende o LED2
      if (recebidos[0] == 2)
      {
        delay(10);
        Serial.print("Recebi ");
        Serial.println(recebidos[0]);
      }
      else 
      {
        Serial.print("Recebi ");
        Serial.println(recebidos[0]);
      }
      delay(100);
    }
  }
  else
  {
  Serial.println("Aguardando dados...");
  }
}

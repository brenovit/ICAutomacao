#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 receiver(7,8);//CSN,CE
String message;
//------------------------
String mensagemReceptor;
int iteration=0;

void setup(){
  delay(150);
  Serial.begin(115200);
  SPI.begin();
  //SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.setBitOrder(MSBFIRST);
  receiver.channel(90);
  receiver.TXaddress("Prado");
  receiver.RXaddress("Artur");
  receiver.init();
  delay(3000);
  //Serial.println("I'm PRX as transceiver");
  Serial.println("Eu sou o PRX (Receptor) como transceiver");
  //receiver.txPL("Hi PTX. I'm ready.");
  receiver.txPL("Ola PTX. Eu estou preparado.");
  receiver.send(SLOW);
  //receiver.txPL("tell me the library's name");
  receiver.txPL("Diga me o nome da Biblioteca");
  receiver.send(SLOW);
}

void loop(){
  
  if(receiver.available()){
    message="";
    receiver.read();
    receiver.rxPL(message);
    //Serial.print("PTX says: \"");
    Serial.print("PTX Diz: \"");
    Serial.print(message);
    Serial.println("\"");
  }else{
    message="";
  }
  delay(20);
  if(message=="nRF24L01p"){
    //message="**You're right ";
    message="**Voce esta Correto ";
    message+=String(iteration);
    message+="**";
    receiver.txPL(message);
    receiver.send(SLOW);
    //Serial.println("***The nRF24L01p library***");
    Serial.println("***A Biblioteca e a nRF24L01p***");
    //Serial.println("It works");
    Serial.println("Isto Funciona!");
    Serial.println();
    iteration++;
  }else if(message.length()>0){
    //receiver.txPL("That's not the name");
    receiver.txPL("Este nao e o nome correto");
    receiver.send(SLOW);
    //Serial.println("PTX is wrong");
    Serial.println("PTX esta errado");
    Serial.println();
  }
  
  
  //parte onde o receptor envia os dados da Serial--------
  if(Serial.available()>0){

    char incomming=Serial.read();
    if(incomming=='\n'){
      receiver.txPL(mensagemReceptor);
      receiver.send(SLOW);
      mensagemReceptor="";
    }
    else{
      mensagemReceptor+=incomming;
    }
  }
  //parte onde o receptor envia os dados da Serial--------
  
  

}






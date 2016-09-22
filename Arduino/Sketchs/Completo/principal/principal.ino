#include "header.h"

RF24 radio(7, 8);
int arduino = 1;
byte endereco[][6] = {"Arduino1", "Arduino2"};

void setup() {
  Serial.begin(9600);
  
  pinMode(lampada1, OUTPUT);
  pinMode(lampada1, OUTPUT);
  pinMode(lampada1, OUTPUT);
  pinMode(SPir1, INPUT);
  pinMode(SPir2, INPUT);
  pinMode(sCorrente, INPUT);  

  printf_begin();
  radio.begin();  //inicia o radio
  radio.setPALevel(RF24_PA_LOW); //define a potencia (energia) do transceiver, por padrão é alto.

  // verifica qual arduino é este e define
  if (arduino == 1) {
    radio.openWritingPipe(endereco[1]);     //o end. de envio de um no -> Pt1
    radio.openReadingPipe(1, endereco[0]);  //e o end. de recebiemnto de um no -> Pt2
  } else {
    radio.openWritingPipe(endereco[0]);     //Pt2 -> end. de envio do outro
    radio.openReadingPipe(1, endereco[1]);  //Pt1 -> end. de recebimento do outro
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

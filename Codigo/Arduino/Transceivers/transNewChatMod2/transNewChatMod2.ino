#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

RF24 radio(7, 8);

int arduino = 0;
byte endereco[][6] = {"Arduino1", "Arduino2"};
const int dataToFinish = 2;

void setup() {
  Serial.begin(9600);

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

  radio.startListening(); //inicia a troca de dados
  //radio.printDetails(); //mostra os detalhes do equipamento.
  printf("Pronto...\n");
}

void loop() {
  if (Serial.available()) {         //verifica se o buffer do Serial esta disponivel
    while (Serial.available()) {    //enquanto o buffer do serial estiver diponivel
      /* a rotina vai executar a função de enviar dados pelo transceiver 'enviarMensagem(char dado)'
         a qual retorna 1 caso consiga enviar ou 0, caso não consiga
         caso aconteça algum erro, uma mensagem de erro é mostrada na tela
      */
      String theMessage = Serial.readString();
      if (!enviarDado(theMessage)) {
        printf("Falha ao enviar a mensagem!\n");
      }
      theMessage = "";
    }
  }
  /* a partir do momento que o transceiver não tiver mais dados para ler
     o arduino estará continuamente verificação se o outro arduino esta enviando algum dado
     por meio da função receberMensagem();
  */
  receberDado();
}
/*
   Função: Enviar string para outro transceiver
   Parametro: variavel do tipo String
   Retorno: booleano, true se conseguir enviar, false se der algum erro
*/
bool enviarDado(String theMessage) {
  radio.stopListening();

  int messageSize = theMessage.length();

  for (int i = 0; i < messageSize; i++) {
    int charToSend;
    charToSend = theMessage.charAt(i);
    if (!radio.write(&charToSend, sizeof(charToSend)))
      printf("Deu erro ao enviar [%s]!\n", charToSend);
  }

  printf("EU: ");
  Serial.println(theMessage);

  if (radio.write(&dataToFinish, sizeof(dataToFinish))) {
    radio.powerDown();
    delay(1000);
    radio.powerUp();
    radio.startListening();
    return true;
  }
  radio.powerDown();
  delay(1000);
  radio.powerUp();
  radio.startListening();
  return true;
}

void receberDado() {
  String theMessage = "";
  bool theEnd = false;
  int msg;
  while (!theEnd) {
    if (radio.available()) {
      while (radio.available()) {
        radio.read(&msg, sizeof(msg));
        char theChar = msg;
        if (msg != 2) {
          theMessage.concat(theChar);
        }
        else {
          printf("OUTRO: ");
          Serial.println(theMessage);
          theMessage = "";
          theEnd = true;
        }
      }
    } else {
      theEnd = true;
    }
  }
}


#include <SPI.h>
#include "nRF24L01.h"
#include <RF24.h>
#include "printf.h"

RF24 radio(7, 8);

const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

bool go_to_tx_mode = false;
char input[32] = "";

int arduino = 0;
byte endereco[][6] = {"COM4", "COM5"};
bool funcao = 0;

unsigned int dadoEnviado = 0;

void setup() {
  Serial.begin(115200);

  printf_begin();
  radio.begin();  //inicia o radio

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW); //define a potencia (energia) do transceiver, por padrão é alto.

  // abre um arduino escritor e um leitor, onde cada 1 tem seu endereço
  if (arduino == 1) {
    radio.openWritingPipe(endereco[1]);
    radio.openReadingPipe(1, endereco[0]);
  } else {
    radio.openWritingPipe(endereco[0]);
    radio.openReadingPipe(1, endereco[1]);
  }

  radio.startListening(); //inicia a troca de dados
  radio.printDetails(); //mostra os detalhes do equipamento.
}

void loop() {
  if (funcao == 1) {
    radio.stopListening();         // primeiro, para de ouvir para começar a falar
    dadoEnviado++;                 // incremento dado enviado

    if (!radio.write(&dadoEnviado, sizeof(unsigned int))) { // se não conseguir enviar o dado
      printf("Dado não foi enviado\n");
    }

    radio.startListening(); //agora ele ouve.

    unsigned long tempo_inicio = micros();             // cria uma variavel que vai receber o tempo que ele iniciou em microsegundos
    boolean tempoAcabou = false;                       // cria uma variavel que vai indicar se recebeu ou não resposta

    while (!radio.available()) {                       // Enquanto nada for recebido
      if (micros() - tempo_inicio > 200000) {            // e o tempo de espera ultrapassar 200ms
        tempoAcabou = true;                            // indica que o tempo experiou
        break;                                         // e sai do loop
      }
    }

    if (tempoAcabou) {
      printf("O tempo de resposta expirou\n");
    } else {
      unsigned int dadoRecebido;
      radio.read(&dadoRecebido, sizeof(unsigned int));
      printf("Enviei: %d e Recebi: %d\n", dadoEnviado, dadoRecebido);
    }
  }

  if (funcao == 0) {
    unsigned int dadoRecebido;
    if (radio.available()) {
      while (radio.available()) {
        radio.read(&dadoRecebido, sizeof(unsigned int));
      }

      radio.stopListening();
      radio.write(&dadoRecebido, sizeof(unsigned int));
      radio.startListening();
      printf("Resposta enviada: %d\n", dadoRecebido);
    }
  }

  lerSerial();
}

void lerSerial() {
  String texto = (Serial.readString());
  if ( texto == "t" && funcao == 0) {
    printf("===== Modo: Transmitindo -- Pressione 'R' para voltar =====\n");
    funcao = 1;
  } else if ( texto == "r" && funcao == 1) {
    printf("===== Modo: Recebendo -- Pressione 'T' para voltar =====\n");
    funcao = 0;
  }
}


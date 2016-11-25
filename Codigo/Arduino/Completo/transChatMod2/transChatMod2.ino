#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

int A = 4;
int B = 5;
int C = 6;

#define pir 3

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
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  printf("Pronto...\n");
}

void loop() {
  if (Serial.available()) {         //verifica se o buffer do Serial esta disponivel
    while (Serial.available()) {    //enquanto o buffer do serial estiver diponivel
      char texto = Serial.read();   //o primeiro 1 byte do serial é armazenado na variavel texto, do tipo char
      /* a rotina vai executar a função de enviar dados pelo transceiver 'enviarMensagem(char dado)'
         a qual retorna 1 caso consiga enviar ou 0, caso não consiga
         caso aconteça algum erro, uma mensagem de erro é mostrada na tela
      */      
        if (!enviarMensagem(texto)) {
          printf("\nFalha ao enviar a mensagem!");
        }
        texto = "";  
    }
  }
  /* a partir do momento que o transceiver não tiver mais dados para ler
     o arduino estará continuamente verificação se o outro arduino esta enviando algum dado
     por meio da função receberMensagem();
  */
  receberMensagem();
}

/*
   Função: Enviar dados para outro transceiver
   Parametro: variavel do tipo char
   Retorno: booleano, true se conseguir enviar, false se der algum erro
*/
bool enviarMensagem(char message) {
  /*
     Para enviar um dado, primeiro o transceiver tem de para de receber dados (parar de ouvir)
     em seguida, usa-se o metodo write para ler os dados enviados
     tendo como parametros a variavel contendo o dado, passando como referência e o tamanho dessa variavel
     retornando 1 para true e 0 para false,(conseguiu enviar e não conseguiu, respectivamente
  */
  radio.stopListening();
  if (radio.write(&message, sizeof(message))) {
    /*
       caso consiga enviar,
       mostra na tela a mensagem enviada
       aguarda 300 milisegundos
       volta a ouvir (receber dados) novamente
       por fim retorna true
    */
    printf("\nEU: %c", message);
    delay(300);
    radio.startListening();
    return true;
  }
  /*
     caso não consiga
     volta a ouvir
     retornando falso
  */
  radio.startListening();
  return false;
}

/*
   Função: Receber dados de outro transceiver
   Parametro: nenhum
   Retorno: nenhum
*/
void receberMensagem() {
  char dadoRecebido;        //variavel que irá armazenar o dado recebido
  if (radio.available()) {  //verifica se o transceiver esta disponivel
    while (radio.available()) {   //enquanto ele se manter neste estado
      /*
         o transceiver irá executar o metodo read
         tendo como parametro a variavel que vai armazenar o dado lido, como referência, e o tamanho desse dado
      */
      radio.read(&dadoRecebido, sizeof(dadoRecebido));      
      checarCodigo(dadoRecebido);
      printf("\nOUTRO: %c", dadoRecebido);      //mostra o dado lido na tela
    }
  }
}

void checarCodigo(char codigo){
    if(codigo == "a"){
      ligar(A);     
    }else if(codigo == "b"){
      ligar(B);     
    }else if(codigo == "c"){
      ligar(C);     
    }else if(codigo == "d"){
      desligar(A);     
    }else if(codigo == "e"){
      desligar(B);  
    }else if(codigo == "f"){
      desligar(C);
    }
    printf("COM4 recebeu: %c",codigo);
}

void ligar(int pino){
  digitalWrite(pino, HIGH); 
}

void desligar(int pino){
  digitalWrite(pino, LOW); 
}

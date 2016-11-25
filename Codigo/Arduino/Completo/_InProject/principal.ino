#include "header.h"

RF24 radio(7, 8);
int arduino = 2;
byte endereco[][6] = {"Arduino1", "Arduino2"};

int sCorrente1Var = 0;
int sCorrente2Var = 0;
int sCorrente3Var = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(lampada1, OUTPUT);
  pinMode(lampada2, OUTPUT);
  pinMode(lampada3, OUTPUT);
  pinMode(SPir1, INPUT);
  pinMode(SPir2, INPUT); 

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
  /*int val = estaLigado(sCorrente1);
  Serial.print("Ligado: ");
  Serial.println(val);
  delay(2000);
  int temGente = temGente(SPir1);
  Serial.print("Tem Gente: ");
  Serial.println(temGente);*/
  /*int var1 = temGente(SPir1);
  int var2 = estaLigado(sCorrente1);
  delay(2000);  
  if(var1){
    Serial.println("Tem Gente!");
    if(sCorrente1Var == 0 || var2 == 0){
      ligarLampada(lampada2);
      Serial.println("Ligado");
    }
    else{
      Serial.println("Apagado!");
    }    
    sCorrente1Var = 1;
  } else{
    Serial.println("Não tem Gente!");
    desligarLampada(lampada2);
  }*/
  if (Serial.available()) {         //verifica se o buffer do Serial esta disponivel
    while (Serial.available()) {    //enquanto o buffer do serial estiver diponivel
      /* a rotina vai executar a função de enviar dados pelo transceiver 'enviarMensagem(char dado)'
         a qual retorna 1 caso consiga enviar ou 0, caso não consiga
         caso aconteça algum erro, uma mensagem de erro é mostrada na tela
      */
      char theMessage = Serial.read();
      if (!enviarMensagem(theMessage)) {
        printf("Falha ao enviar a mensagem!\n");
      }
      theMessage = "";
    }
  }
  /* a partir do momento que o transceiver não tiver mais dados para ler
     o arduino estará continuamente verificação se o outro arduino esta enviando algum dado
     por meio da função receberMensagem();
  */
  receberMensagem();
}

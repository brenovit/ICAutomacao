#include "header.h"

RF24 radio(7, 8);
int arduino = 2;
byte endereco[][6] = {"Arduino1", "Arduino2"};

bool lamp1On = false;
bool lamp2On = false;
bool lamp3On = false;

bool pulso2 = false;
int gente1 = false;

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
//  int val = estaLigado(sCorrente1);
  //delay(2000);
  gente1 = temGente(SPir1);

  
  //cenario 1
  /* não tem ninguem na sala, o sensor percebe movimento
   * verifica se os equipamentos estão ligados
   * não estando: liga todos eles e altera o estado logicamente
   * se não tiver movimento: 
   */

  if(temPulso(sCorrente2)){
    pulso2 = true;
  }else{
    pulso2 = false;
  }  
  
  if(gente1){ //se tiver pessoa -. ligar a porra toda
    if(!lamp2On){ //SE A lampada tiver desligada
      ligarLampada(lampada2);
      lamp2On = true;
    }    
  }else{
    //tempo de contagem
    if(lamp2On){
      desligarLampada(lampada2);
      lamp2On = false;
    }   
  } 
  
  //delay(2000);  
  
  /*if(var1){
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

void checarCodigo(char codigo){  //manda ligar as lampadas
    if(codigo == 'a'){
      ligarLampada(lampada1);
    }else if(codigo == 'b'){
      if(!lamp2On){
        ligarLampada(lampada2);
        lamp2On = true;
      }  
    }else if(codigo == 'c'){
      ligarLampada(lampada3);
    }
    //manda desligar as lampadas
    else if(codigo == 'd'){
      desligarLampada(lampada1);
    }else if(codigo == 'e'){
      if(lamp2On){
        desligarLampada(lampada2);
        lamp2On = false;
      }
    }else if(codigo == 'f'){
      desligarLampada(lampada3);
    }
    printf("\nCOM3 recebeu: %c",codigo);
}

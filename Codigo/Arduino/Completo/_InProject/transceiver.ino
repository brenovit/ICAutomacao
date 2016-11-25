#include "header.h"

void checarCodigo(char codigo){  //manda ligar as lampadas
    if(codigo == "a"){
      ligarLampada(lampada1);     
    }else if(codigo == "b"){
      ligarLampada(lampada2);  
    }else if(codigo == "c"){
      ligarLampada(lampada3);
    }
    //manda desligar as lampadas
    else if(codigo == "d"){
      desligarLampada(lampada1);
    }else if(codigo == "e"){
      desligarLampada(lampada2);
    }else if(codigo == "f"){
      desligarLampada(lampada3);
    }
    printf("\nCOM3 recebeu: %c",codigo);
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
char receberMensagem() {
  char dadoRecebido;        //variavel que irá armazenar o dado recebido
  if (radio.available()) {  //verifica se o transceiver esta disponivel
    while (radio.available()) {   //enquanto ele se manter neste estado
      /*
         o transceiver irá executar o metodo read
         tendo como parametro a variavel que vai armazenar o dado lido, como referência, e o tamanho desse dado
      */
      radio.read(&dadoRecebido, sizeof(dadoRecebido));
      checarCodigo(dadoRecebido);
     // printf("\nOUTRO: %c", dadoRecebido);      //mostra o dado lido na tela
     return dadoRecebido;
    }
  }
}

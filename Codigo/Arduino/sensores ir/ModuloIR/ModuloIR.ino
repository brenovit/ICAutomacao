#include <IRremote.h>// incluindo a biblioteca do infravermelho
const int pinIR = 2; // pino 6 no arduino
const int pinLED = 5;

IRrecv modIR(pinIR); //declarando a variável do sensor
decode_results codigo; //resultado

void setup()
{    
  Serial.begin(9600); //mostra o resultado no computador
  modIR.enableIRIn(); // inicia a recepção
  pinMode(pinLED, OUTPUT);
}
void loop() {
  if (modIR.decode(&codigo)) {//verifica se um codigo foi recebido
    if (codigo.value != 0 ){
      Serial.println(codigo.value, HEX); //mostra no serial o resultado
  }
  //Obs.: Colocar o 0x antes do numero hexadecimal, pois só assim para poder comparar no if
  if ((codigo.value == 0x39C618E7) || (codigo.value == 0xFF30CF)){// verifica se foi pressionado o numero 1 dos controles
    digitalWrite(pinLED, HIGH);
    delay(500);
    digitalWrite(pinLED, LOW);
  }
  modIR.resume(); // recebe o próximo código
  delay(200);
  }
}

#include <printf.h>

bool foi = true;
String msg = "";

void setup() {
  Serial.begin(9600);
  Serial.println("Pronto");
}

void loop() {
  /*String texto1 = "Sou um texto";
  String texto2 = "Sou um texto e meu nome é Breno nunes arantes, estou até fazendo um chat";
  
  Serial.print("sizeof(int) - ");
  Serial.println(sizeof(int)); 

  Serial.print("sizeof(unsigned int) - ");
  Serial.println(sizeof(unsigned int)); 

  Serial.print("sizeof(char) - ");
  Serial.println(sizeof(char)); 
  
  Serial.print("sizeof(String) - ");
  Serial.println(sizeof(String));

  Serial.print("sizeof("+texto1+") - ");
  Serial.println(sizeof(texto1));

  Serial.print("sizeof("+texto2+") - ");
  Serial.println(sizeof(texto2));*/
  
  ler(&msg); 
  Serial.println("No loop: "+msg);
  
  delay(2000);
}

void ler(String *msg){
  if(Serial.available()){
    *msg = Serial.readString();
    
    Serial.println("No ler: "+*msg);
  }  
}


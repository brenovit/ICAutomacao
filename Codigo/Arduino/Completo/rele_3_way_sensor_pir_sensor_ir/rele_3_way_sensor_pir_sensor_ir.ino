#define A 4
#define B 5
#define C 6

#define pir 3

bool stateB = false, stateA = true;
int val;
int sec = 0;
int state = 0;

/*IRrecv irrec(rir);
IRsend irsend;
decode_results codigo;*/

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(pir, INPUT);
  
  //irrec.enableIRIn();    
  
  Serial.begin(9600);
  delay(2000);
  Serial.println("Pronto");
}

void loop() {
  //lerSerial();  
  //receptorIR(2);  //mode 2 just execute mode 1 receiver code
  //sensorPir();
  
  if(Serial.available()){
    String letra = Serial.readString();
    Serial.println("Comando: "+letra);    
    if(letra == "oa"){
      ligar(A);     
    }else if(letra == "ob"){
      ligar(B);     
    }else if(letra == "oc"){
      ligar(C);     
    }else if(letra == "ba"){
      desligar(A);     
    }else if(letra == "bb"){
      desligar(B);     
    }else if(letra == "bc"){
      desligar(C);     
    }    
  }
  /*if(sensorPir() == true){
    ativar(A);
    Serial.println("Tem gente");
    delay(3000);
  }else{
      desativar(A);
  }*/   
}

void ligar(int pino){
  digitalWrite(pino, HIGH); 
}

void desligar(int pino){
  digitalWrite(pino, LOW); 
}

/*void emissorIR(int codigo){
  if (Serial.read() != -1) {
    for (int i = 0; i < 3; i++) {
      irsend.sendPanasonic(0x4004, codigo); // Sony TV power code
      delay(40);
    }
  }
}

void receptorIR(int mode){  
  if(irrec.decode(&codigo)){
    if(mode == 1){
      if(codigo.value != 0){
        Serial.print("Codigo: ");
        Serial.println(codigo.value,HEX);
      }
    }else if(mode == 2){
        if(codigo.value == 0x1000405)     
          ativar(A);
        if(codigo.value == 0x1008485)      
          desativar(A);
    }   
  }
  irrec.resume();
  delay(1000);
}

void lerSerial(){
  if(Serial.available()){
    String letra = Serial.readString();
    Serial.println("Comando: "+letra);    
    if(letra == "on a"){     
        ativar(A);
    } else if (letra == "off a"){
        desativar(A);
    }    
    letra = "";
  }
}
/*void sensorPir(){
  val = digitalRead(pir);
  if(val == HIGH){
    irsend.sendPanasonic(0x4004, volu); // Sony TV power code
  }else{
    irsend.sendPanasonic(0x4004, vold); // Sony TV power code
  }
}*/

void ativar(int pino){  
  if(pino == B){      
        digitalWrite(B, HIGH);        
        Serial.println("Ativei B");
  } else if(pino == A){
        digitalWrite(A, HIGH);        
        Serial.println("Ativei A");
  }
}
void desativar(int pino){
  if(pino == B){
        digitalWrite(B, LOW);        
        Serial.println("Desativei B");
  }else if(pino == A){
        digitalWrite(A, LOW);
        Serial.println("Desativei A");
  }
}


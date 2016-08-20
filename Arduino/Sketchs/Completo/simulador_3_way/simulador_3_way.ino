int B = 9, A = 10;
bool b = true, a = true;

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    String letra = Serial.readString();
    Serial.println("Apertou: "+letra);
    
    if(letra == "a"){
      //acender(pinR1);
      if(a == true){
        digitalWrite(A, LOW);
        Serial.println("Desliguei A");
        a = false;
      }else{
        digitalWrite(A, HIGH);        
        Serial.println("Liguei A");
        a = true;
      }
    } 
    if(letra == "b"){
      //acender(pinR2);
      if(b == true){
        digitalWrite(B, LOW);        
        Serial.println("Desliguei B");
        b = false;
      }else{
        digitalWrite(B, HIGH);        
        Serial.println("Liguei B");
        b = true;
      }
    }
  }
}

/*void acender(int pino){  
  if(pino == pinR1){
    if(bR1 == true){
      digitalWrite(pino, LOW);
      bR1 = false;
    }else{
      digitalWrite(pino, HIGH);
      bR2 = true;
    }
  }else if(pino == pinR2){
    if(bR2 == true){
      digitalWrite(pino, LOW);
      bR2 = false;
    }else{
      digitalWrite(pino, HIGH);
      bR2 = true;
    }
  }
}*/


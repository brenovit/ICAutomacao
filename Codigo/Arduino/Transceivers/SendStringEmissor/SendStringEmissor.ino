#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

const int msg = 2;
RF24 radio(7, 8);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int num = 0;

void setup(void) {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop(void) {
  if (Serial.available()) {
    while (Serial.available()) {
      String theMessage = Serial.readString();
      enviar(theMessage);
    }
  }
}

void enviar(String theMessage) {
  
  int messageSize = theMessage.length();
  for (int i = 0; i < messageSize; i++) {
    int charToSend;
    charToSend = theMessage.charAt(i);
    radio.stopListening();
    radio.write(&charToSend, sizeof(charToSend));
  }
  Serial.println(theMessage);
  //send the 'terminate string' value...
  radio.write(&msg, sizeof(msg));
  radio.powerDown();
  delay(1000);
  radio.powerUp();
}


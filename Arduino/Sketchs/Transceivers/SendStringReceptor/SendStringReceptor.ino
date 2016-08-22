#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

int messageLength = 12;
int msg[1];
RF24 radio(7, 8);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int lastmsg = 1;
String theMessage = "";

void setup(void) {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}

void loop(void) {
  receber();
}

void receber() {
  int msg[1];
  int lastmsg = 1;
  String theMessage = "";
  bool theEnd = true;
  while (theEnd) {
    if (radio.available()) {
      radio.read(msg, sizeof(msg));
      char theChar = msg[0];
      if (msg[0] != 2) {
        theMessage.concat(theChar);
      }
      else {
        Serial.println(theMessage);
        theMessage = "";
        theEnd = false;
      }
    }
  }
}


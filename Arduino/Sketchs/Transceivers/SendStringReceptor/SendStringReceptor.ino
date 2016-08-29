#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

RF24 radio(7, 8);
const uint64_t pipe = 0xE8E8F0F0E1LL;

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
  int msg;
  String theMessage = "";
  bool theEnd = false;
  while (!theEnd) {
    if (radio.available()) {
      radio.read(&msg, sizeof(msg));
      char theChar = msg;
      if (msg != 2) {
        theMessage.concat(theChar);
      }
      else {
        Serial.println(theMessage);
        theMessage = "";
        theEnd = true;
      }
    }
  }

}

/*
void receber() {
  int msg;
  String theMessage = "";
  bool theEnd = false;

  while (!theEnd) {
    if (radio.available()) {
      radio.read(&msg, sizeof(msg));
      char theChar = msg;
      if (msg != 2) {
        theMessage.concat(theChar);
      }
      else {
        Serial.println(theMessage);
        theMessage = "";
        theEnd = true;
      }
    }
  }
}
*/


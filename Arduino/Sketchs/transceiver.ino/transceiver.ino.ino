#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8
RF24 radio(7, 8);

// Topology
const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };              // Endereços hexadecimais

// Role management: Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.

typedef enum { enviar = 1, receber } role_e;                 // as diferentes funções suportadas por esse sketch
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};  // The debug-friendly names of those roles
role_e funcao = enviar;                                              // The role of the current running sketch

// A single byte to keep track of the data being sent back and forth
byte counter = 1;

void setup() {

  Serial.begin(115200);
  printf_begin();
  Serial.print(F("\n\rRF24/examples/pingpair_ack/\n\rROLE: "));
  Serial.println(role_friendly_name[role]);
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  // Setup and configure rf radio

  radio.begin();
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.enableAckPayload();               // Allow optional ack payloads
  radio.setRetries(0, 15);                // Smallest time between retries, max no. of retries
  radio.setPayloadSize(1);                // Here we are sending 1-byte payloads to test the call-response speed
  
  radio.openWritingPipe(pipes[1]);        // Endereço 0x544d52687CLL <- escreve
  radio.openReadingPipe(1, pipes[0]);     // Endereço 0xABCDABCD71LL <- ler
  
  radio.startListening();                 // Inicia a troca de dados
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging
}

void loop(void) {

  if (role == role_ping_out) {

    radio.stopListening();                                  // First, stop listening so we can talk.

    printf("Now sending %d as payload. ", counter);
    byte gotByte;
    unsigned long time = micros();                          // Take the time, and send it.  This will block until complete
    //Called when STANDBY-I mode is engaged (User is finished sending)
    if (!radio.write( &counter, 1 )) {
      Serial.println(F("failed."));
    } else {
      if (!radio.available()) {
        Serial.println(F("Blank Payload Received."));
      } else {
        while (radio.available()) {
          unsigned long tim = micros();
          radio.read( &gotByte, 1 );
          printf("Got response %d, round-trip delay: %lu microseconds\n\r", gotByte, tim - time);
          counter++;
        }
      }
    }
    // Try again later
    delay(1000);
  }

  // Pong back role.  Receive each packet, dump it out, and send it back
  if ( role == role_pong_back ) {
    byte pipeNo;
    byte gotByte;                                       // Dump the payloads until we've gotten everything
    while ( radio.available(&pipeNo)) {
      radio.read( &gotByte, 1 );
      radio.writeAckPayload(pipeNo, &gotByte, 1 );
    }
  }

  // Change roles

  if ( Serial.available())
  {
    char c = toupper(Serial.read());
    if ( c == 'T' && role == receber) {
      Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));

      role = enviar;                  // Become the primary transmitter (ping out)
      radio.openWritingPipe(pipes[0]);
      radio.openReadingPipe(1, pipes[1]);
    } else if ( c == 'R' && role == enviar) {
      Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));

      role = receber;                // Become the primary receiver (pong back)
      radio.openWritingPipe(pipes[1]);
      radio.openReadingPipe(1, pipes[0]);
      radio.startListening();
    }
  }
}

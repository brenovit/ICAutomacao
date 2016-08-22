#include <SPI.h>
#include <RF24.h>

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 1;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7, 8);
/**********************************************************/

byte addresses[][6] = {"1Node", "2Node"};

// Used to control whether this node is sending or receiving
bool role = 0;

void setup() {
  Serial.begin(115200);
  Serial.println(F("RF24/examples/GettingStarted"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);

  // Open a writing and reading pipe on each radio, with opposite addresses
  if (radioNumber) {
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1, addresses[0]);
  } else {
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1, addresses[1]);
  }

  // Start the radio listening for data
  radio.startListening();
}

void loop() {
  /****************** Ping Out Role ***************************/
  if (role == 1)  {

    radio.stopListening();                                    // First, stop listening so we can talk.

    Serial.println(F("Enviando agora"));

    unsigned long start_time = micros();                             // Take the time, and send it.  This will block until complete
    unsigned int data_send = 12;
    //if (!radio.write( &start_time, sizeof(unsigned long) )){
    if (!radio.write( &data_send, sizeof(unsigned int ))) {
      Serial.println(F("Falhou!"));
    }

    radio.startListening();                                    // Now, continue listening

    unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
    boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not

    while (!radio.available()) {                            // While nothing is received
      if (micros() - started_waiting_at > 200000) {           // If waited longer than 200ms, indicate timeout and exit while loop
        timeout = true;
        break;
      }
    }

    if (timeout ) {                                            // Describe the results
      Serial.println(F("Falhou, tempo de respota expirou."));
    } else {
      unsigned long got_time;                                 // Grab the response, compare, and send to debugging spew
      unsigned int data_rec;
      radio.read( &data_rec, sizeof(unsigned int) );
      unsigned long end_time = micros();

      // Spew it
      Serial.print(F("Enviei "));
      Serial.print(data_send);
      Serial.print(F(", Obeteve resposta "));
      Serial.print(data_rec);
      Serial.print(F(", Atraso de ida e volta "));
      Serial.print(end_time - start_time);
      Serial.println(F(" microseconds"));
    }

    // Try again 1s later
    delay(1000);
  }



  /****************** Pong Back Role ***************************/

  if ( role == 0 )
  {
    unsigned long got_time;
    unsigned int data_rec;
    if ( radio.available()) {
      // Variable for the received timestamp
      while (radio.available()) {                                   // While there is data ready
        radio.read( &data_rec, sizeof(unsigned int) );             // Get the payload
      }

      radio.stopListening();                                        // First, stop listening so we can talk
      radio.write( &data_rec, sizeof(unsigned int) );              // Send the final one back.
      radio.startListening();                                       // Now, resume listening so we catch the next packets.
      Serial.print(F("Resposta Enviada "));
      Serial.println(data_rec);
    }
  }




  /****************** Change Roles via Serial Commands ***************************/

  if ( Serial.available() )
  {
    char c = toupper(Serial.read());
    if ( c == 'T' && role == 0 ) {
      Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      role = 1;                  // Become the primary transmitter (ping out)

    } else if ( c == 'R' && role == 1 ) {
      Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));
      role = 0;                // Become the primary receiver (pong back)
      radio.startListening();

    }
  }


} // Loop


#include "header.h"

bool temGente(int pir){
  int val = digitalRead(pir);
  if(val == HIGH){
    return true;
    //mandar mensagem que tem gente na sala
  }
  return false;
}

void sensorPir(){
  val = digitalRead(pir);
  if(val == HIGH){
    irsend.sendPanasonic(0x4004, volu); // Sony TV power code
  }else{
    irsend.sendPanasonic(0x4004, vold); // Sony TV power code
  }

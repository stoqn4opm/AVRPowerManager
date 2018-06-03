#include <AVRPowerManager.h>
#include "HEF4021BP.h"
#include "AVRSleep.hpp"

namespace {
HEF4021BP shiftRegister(3, 4, 5); // clock, latch, data
};

/*
 * This example show you how you can turn off the atmega328p with 8 bit shift register input.
 * for this demo, hook a NES controller on pins 3, 4, 5 and pass the input to the AVRPowerManger
 * Press simultaneously "start" and "select buttons for 2 seconds and after release the system will
 * enter shutdown sleep mode. There is also a 2 min autoshutdown in case of no buttons pressed.
 * 
 */

void setup() {
  // put your setup code here, to run once:
     Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  shiftRegister.update();
  int8_t buttonStates = shiftRegister.getButtonStates();
  AVRPowerManager::shared()->shutdownIfNeeded(buttonStates);
  Serial.println(buttonStates, BIN);
}

//
//  HEF4021BP.cpp
//  NESController
//
//  Created by Stoyan Stoyanov on 22.04.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#include "HEF4021BP.h"

#pragma mark - Constants

/*
Bit sequence:
A_BUTTON         = 0;
B_BUTTON         = 1;
SELECT_BUTTON    = 2;
START_BUTTON     = 3;
UP_BUTTON        = 4;
DOWN_BUTTON      = 5;
LEFT_BUTTON      = 6;
RIGHT_BUTTON     = 7;
*/

#pragma mark - Constructor

HEF4021BP::HEF4021BP(int8_t clock, int8_t latch, int8_t data) {
  clockPin = clock;
  latchPin = latch;
  dataPin = data;

  pinMode(dataPin, INPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  // Set initial states
  digitalWrite(clockPin, LOW);
  digitalWrite(latchPin, LOW);
}

#pragma mark - Actions

void HEF4021BP::update() {

  int8_t tempData = 0xFF;

  for (int8_t currentButton = 0; currentButton <= 7; currentButton++) {
    pulse(currentButton == 0 ? latchPin : clockPin);
    clearBitOfTempDataIfNeeded(tempData, currentButton);
  }
  
  buttonStates = ~tempData;
}

int8_t HEF4021BP::getButtonStates() {
  return buttonStates;
}

#pragma mark - Helpers

void HEF4021BP::pulse(int8_t pin) {
  digitalWrite(pin, HIGH);
  digitalWrite(pin, LOW);
}

void HEF4021BP::clearBitOfTempDataIfNeeded(int8_t &tempData, int8_t bitPosition) {
  if (digitalRead(dataPin) == LOW)
    bitClear(tempData, bitPosition);
}


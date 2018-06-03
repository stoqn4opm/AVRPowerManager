//
//  HEF4021BP.hpp
//  NESController
//
//  Created by Stoyan Stoyanov on 22.04.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#ifndef HEF4021BP_hpp
#define HEF4021BP_hpp

#include "Arduino.h"

class HEF4021BP {
  private:
    int8_t buttonStates = (int8_t)0xFF;
    int8_t clockPin;
    int8_t latchPin;
    int8_t dataPin;
    void pulse(int8_t pin);
    void clearBitOfTempDataIfNeeded(int8_t &tempData, int8_t bitPosition);
  public:
    HEF4021BP(int8_t clock, int8_t latch, int8_t data);
    void update();
    int8_t getButtonStates();
};

#endif /* HEF4021BP_hpp */

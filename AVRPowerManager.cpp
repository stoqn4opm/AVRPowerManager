//
//  AVRPowerManager.cpp
//  NESController
//
//  Created by Stoyan Stoyanov on 22.04.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#include "AVRPowerManager.h"
#include "AVRSleep.hpp"

#pragma mark - Singleton Reference

AVRPowerManager::AVRPowerManager() {
  AVRSleep::setup();

  isInMiddleOfPattern = false;
  isInMiddleOfAutoShutdown = false;
  isAboutToDie = false;
  initialStateEntered = false;
}

AVRPowerManager* AVRPowerManager::instance = 0;

AVRPowerManager* AVRPowerManager::shared() {
  if (instance == 0) {
    instance = new AVRPowerManager();
  }
  return instance;
}

#pragma mark - Shutdown Procedures

void AVRPowerManager::shutdownIfNeeded(int8_t input) {

  if (input == startState) {
    initialStateEntered = true;
  }
  if (!initialStateEntered) {
    return;
  }

  if (isAboutToDie == true) {
    waitForStartState(input);
    return;
  }

  autoShutdownIfNeeded(input);

  if (input == desiredState) {
    handleExpectedInput();
  } else {
    breakPattern();
  }
}

void AVRPowerManager::autoShutdownIfNeeded(int8_t input) {

  unsigned long currentTime = millis();
  if (isInMiddleOfAutoShutdown && autoShutdownStartTime < currentTime && currentTime - autoShutdownStartTime > (unsigned long)autoShutDownDelay * 1000) {
    isInMiddleOfAutoShutdown = false;
    shutdown();
    return;
  }

  if (input == startState) {
    if (!isInMiddleOfAutoShutdown) {
      autoShutdownStartTime = millis();
      isInMiddleOfAutoShutdown = true;
    }
  } else {
    isInMiddleOfAutoShutdown = false;
  }
}

void AVRPowerManager::handleExpectedInput() {

  if (isInMiddleOfPattern) {
    // check if variable overflow occured
    unsigned long currentTime = millis();
    if (currentTime < patternStartTime) {
      breakPattern();
      return;
    }

    // check if pattern is completely recognized
    if ((currentTime - patternStartTime) >= (delayBeforeExecutionInSecs * 1000)) {
      shutdown();
      breakPattern();
    }
  } else {
    // pattern recognition begins
    patternStartTime = millis();
    isInMiddleOfPattern = true;
  }
}

void AVRPowerManager::waitForStartState(int8_t input) {
  if (input == startState) {
    breakPattern();
    initialStateEntered = false;
    isAboutToDie = false;
    AVRSleep::shutdown();
  }
}

#pragma mark - Helper Methods

void AVRPowerManager::breakPattern() {
  isInMiddleOfPattern = false;
}

void AVRPowerManager::shutdown() {
  initialStateEntered = false;
  isAboutToDie = true;
}

#pragma mark - Computed Variables

bool AVRPowerManager::wantsShutdown() {
  return isAboutToDie;
}


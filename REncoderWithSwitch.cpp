#include <Arduino.h>
#include "REncoderWithSwitch.h"

REncoderWithSwitch::REncoderWithSwitch(int8_t clkPin, int8_t dtPin, int8_t swPin) 
  : REncoderWithoutSwitch::REncoderWithoutSwitch (clkPin, dtPin) {
  this->clkPin = clkPin >= 0 ? clkPin : -1;
  this->dtPin = dtPin >= 0 ? dtPin : -1;
  this->swPin = swPin >= 0 ? swPin : -1;
  this->init();
};

#if !defined(RENCODER_ENABLE_SWITCH_IRQ) && !defined(RENCODER_ENABLE_ENCODER_IRQ)
  void REncoderWithSwitch::enableContinuousSwitchDetection(bool enableState) {
    this->continousSwitchDetection = enableState;
  };

  void REncoderWithSwitch::enableEncoderWhenSwitchPushed(bool enableState) {
    this->enableRotationDetectionWhenSwitchActive = enableState;
  };
#endif

void REncoderWithSwitch::init() {
  REncoderWithoutSwitch::init();
  if (this->swPin >= 0) {
    pinMode(this->swPin, INPUT_PULLUP);
    this->lastSwState = digitalRead(this->swPin);
  }
};

#ifndef RENCODER_ENABLE_SWITCH_IRQ
  #ifdef RENCODER_ENABLE_SWITCH_SOFTWARE_DEBOUNCING
    REncoderWithSwitch::Event REncoderWithSwitch::reStateSwitch() {
      REncoderWithSwitch::Event switchEvent = REncoderWithSwitch::Event::REncoder_Event_None;
      if (this->swPin >= 0) {
        if ((millis() - this->lastSwitchDebounceTime) > this->debounceSwitchTolerance) {
          byte swState = digitalRead(this->swPin);
          if (swState == LOW) {
            if (this->continousSwitchDetection) {
              switchEvent = REncoderWithSwitch::Event::REncoder_Event_Switch_Pushed;
            }
            else if (this->lastSwState == HIGH) {
              switchEvent = REncoderWithSwitch::Event::REncoder_Event_Switch_Pushed;
              this->lastSwState = LOW;
            }
          } else {
            this->lastSwState = HIGH;
          }
          this->lastSwitchDebounceTime = millis();
        }
      }
      return switchEvent;
    };
  #else
    REncoderWithSwitch::Event REncoderWithSwitch::reStateSwitch() {
      REncoderWithSwitch::Event switchEvent = REncoderWithSwitch::Event::REncoder_Event_None;
      if (this->swPin >= 0) {
        byte swState = digitalRead(this->swPin);
        if (swState == LOW) {
          if (this->continousSwitchDetection) {
            switchEvent = REncoderWithSwitch::Event::REncoder_Event_Switch_Pushed;
          } else if (this->lastSwState == HIGH) {
            switchEvent = REncoderWithSwitch::Event::REncoder_Event_Switch_Pushed;
            this->lastSwState = LOW;
          }
        } else {
          this->lastSwState = HIGH;
        }
      }
      return switchEvent;
    };
  #endif
#endif

#ifndef RENCODER_ENABLE_ENCODER_IRQ
  REncoderWithSwitch::Event REncoderWithSwitch::reStateEncoder() {
    // make sure that PW pin is not LOW. When the PW pin is LOW, then the button
    // switch is pressed and during this time, the rotation of the encoder shall
    // have no effect.
    if (!this->enableRotationDetectionWhenSwitchActive && this->lastSwState == LOW) {
      #ifdef RENCODER_ENABLE_ENCODER_SOFTWARE_DEBOUNCING
        this->lastEncoderDebounceTime = millis();
      #endif
      return REncoderWithSwitch::Event::REncoder_Event_None;
    }

    // make sure that the CLK and DT pins are defined and check if the encoder changed state
    return REncoderWithoutSwitch::reState();
  };
#endif

#if !defined(RENCODER_ENABLE_SWITCH_IRQ) || !defined(RENCODER_ENABLE_ENCODER_IRQ)
  REncoderWithSwitch::Event REncoderWithSwitch::reState(void) {
    REncoderWithSwitch::Event event = REncoderWithSwitch::Event::REncoder_Event_None;

    #ifndef RENCODER_ENABLE_SWITCH_IRQ
      event = this->reStateSwitch();
      // 'SWITCH Activated' (i.e., button pushed) event has higher priority
      if (event != REncoderWithSwitch::Event::REncoder_Event_None) {
        return event;
      }
    #endif

    #ifndef RENCODER_ENABLE_ENCODER_IRQ
      event = this->reStateEncoder();
    #endif

    return event;
  }
#endif

#ifdef RENCODER_ENABLE_SWITCH_IRQ
  void REncoderWithSwitch::attachSwitchHandler(void (*switchHandler)(void)) {
    if (this->swPin >= 0 && switchHandler) {
      // remove any possibly already attached interrupt for the SWITCH pin
      detachInterrupt(digitalPinToInterrupt(this->swPin));
      
      // attache interrupt in FALLING pin mode (HIGH state changes to LOW state)
      attachInterrupt(digitalPinToInterrupt(this->swPin), switchHandler, FALLING);
    }
  };
#endif
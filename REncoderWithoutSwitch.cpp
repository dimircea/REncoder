#include <Arduino.h>
#include "REncoderWithoutSwitch.h"

REncoderWithoutSwitch::REncoderWithoutSwitch(int8_t clkPin, int8_t dtPin) {
  this->clkPin = clkPin >= 0 ? clkPin : -1;
  this->dtPin = dtPin >= 0 ? dtPin : -1;
  this->init();
};

#ifndef RENCODER_ENABLE_ENCODER_IRQ
  RENCODER_ROTATION_VALUE_TYPE REncoderWithoutSwitch::getPosition(void) {
    return this->encoderPosition;
  };

  void REncoderWithoutSwitch::setPosition(RENCODER_ROTATION_VALUE_TYPE encoderPosition) {
    if (encoderPosition > this->maxPosition) {
      this->encoderPosition = this->maxPosition;
    } else if (encoderPosition < this->minPosition) {
      this->encoderPosition = this->minPosition;
    } else {
      this->encoderPosition = encoderPosition;
    }
  };
#endif

void REncoderWithoutSwitch::setMinEncoderPosition(RENCODER_ROTATION_VALUE_TYPE minPosition) {
  this->minPosition = minPosition;
};

void REncoderWithoutSwitch::setMaxEncoderPosition(RENCODER_ROTATION_VALUE_TYPE maxPosition) {
  this->maxPosition = maxPosition;
};

void REncoderWithoutSwitch::init() {
  if (this->clkPin >= 0 && this->dtPin >= 0) {
    pinMode(this->clkPin, INPUT_PULLUP);
    #ifndef RENCODER_ENABLE_ENCODER_IRQ
      this->lastClkState = digitalRead(this->clkPin);
    #endif

    pinMode(this->dtPin, INPUT_PULLUP);
    #ifndef RENCODER_ENABLE_ENCODER_IRQ
      this->lastDtState = digitalRead(this->dtPin);
    #endif
  }
};

#ifdef RENCODER_ENABLE_ENCODER_IRQ
  void REncoderWithoutSwitch::attachEncoderHandler(void (*encoderHandler)(REncoderWithoutSwitch::Event, RENCODER_ROTATION_VALUE_TYPE)) {
    if (this->clkPin >= 0 && this->dtPin >= 0 && encoderHandler) {

      static void (*eventHandler)(REncoderWithoutSwitch::Event, RENCODER_ROTATION_VALUE_TYPE) = encoderHandler;
      static RENCODER_ROTATION_VALUE_TYPE encoderPosition = 0;
      static RENCODER_ROTATION_VALUE_TYPE minPosition = this->minPosition;
      static RENCODER_ROTATION_VALUE_TYPE maxPosition = this->maxPosition;

      static uint8_t clkPin = this->clkPin;
      static uint8_t dtPin = this->dtPin;
      static uint8_t lastClkState = digitalRead(this->clkPin);

      // remove any possibly already attached interrupt for CLOCK and DATA pins
      detachInterrupt(digitalPinToInterrupt(this->clkPin));
      detachInterrupt(digitalPinToInterrupt(this->dtPin));

      attachInterrupt(
        digitalPinToInterrupt(this->clkPin),
        []() -> void {
          uint8_t clkState = digitalRead(clkPin);
          REncoderWithoutSwitch::Event event;
          if (clkState ^ lastClkState) {
            if (digitalRead(dtPin) == lastClkState) {
              if (encoderPosition < maxPosition) {
                encoderPosition++;
              }
              event = REncoderWithoutSwitch::Event::REncoder_Event_Rotate_CW;
            } else {
              if (encoderPosition > minPosition) {
                encoderPosition--;
              }
              event = REncoderWithoutSwitch::Event::REncoder_Event_Rotate_CCW;
            }
            eventHandler(event, encoderPosition);
          }
          lastClkState = clkState;
        },
        CHANGE
      );
    }
  };
#else
  REncoderWithoutSwitch::Event REncoderWithoutSwitch::reState() {
    REncoderWithoutSwitch::Event encoderEvent = REncoderWithoutSwitch::Event::REncoder_Event_None;

    // make sure that the CLK and DT pins are defined and check if the encoder changed state
    if (this->clkPin >= 0 && this->dtPin >= 0) {
      #ifdef RENCODER_ENABLE_ENCODER_SOFTWARE_DEBOUNCING
      if ((millis() - this->lastEncoderDebounceTime) > this->debounceEncoderTolerance) {
      #endif
        byte clkState = digitalRead(this->clkPin);
        byte dtState = digitalRead(this->dtPin);

        // CLK has a different state as when checked last time...
        if (this->lastClkState ^ clkState) {
            if (dtState == this->lastClkState) {
              if (this->encoderPosition < this->maxPosition) {
                this->encoderPosition++;
              }
              encoderEvent = REncoderWithoutSwitch::Event::REncoder_Event_Rotate_CW;
            } else {
              if (this->encoderPosition > this->minPosition) {
                this->encoderPosition--;
              }
              encoderEvent = REncoderWithoutSwitch::Event::REncoder_Event_Rotate_CCW;
            }
        }

        this->lastClkState = clkState;
        this->lastDtState = dtState;
      #ifdef RENCODER_ENABLE_ENCODER_SOFTWARE_DEBOUNCING
        this->lastEncoderDebounceTime = millis();
      }
      #endif
    }
    return encoderEvent;
  };
#endif
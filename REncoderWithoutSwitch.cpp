#include <Arduino.h>
#include "REncoderWithoutSwitch.h"

REncoderWithoutSwitch::REncoderWithoutSwitch(int8_t clkPin, int8_t dtPin) {
  this->clkPin = clkPin >= 0 ? clkPin : -1;
  this->dtPin = dtPin >= 0 ? dtPin : -1;
  this->init();
};

#ifndef RENCODER_ENABLE_ENCODER_IRQ
  int16_t REncoderWithoutSwitch::getPosition(void) {
    return this->encoderPosition;
  };

  void REncoderWithoutSwitch::setPosition(int16_t encoderPosition) {
    if (encoderPosition > this->maxPosition) {
      this->encoderPosition = this->maxPosition;
    } else if (encoderPosition < this->minPosition) {
      this->encoderPosition = this->minPosition;
    } else {
      this->encoderPosition = encoderPosition;
    }
  };
#endif

void REncoderWithoutSwitch::setMinEncoderPosition(int16_t minPosition) {
  this->minPosition = minPosition;
};

void REncoderWithoutSwitch::setMaxEncoderPosition(int16_t maxPosition) {
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
  void REncoderWithoutSwitch::attachEncoderHandler(void (*encoderHandler)(REncoderWithoutSwitch::Event, int16_t)) {
    if (this->clkPin >= 0 && this->dtPin >= 0 && encoderHandler) {

      static void (*eventHandler)(REncoderWithoutSwitch::Event, int16_t) = encoderHandler;
      static int16_t encoderPosition = 0;
      static int16_t minPosition = this->minPosition;
      static int16_t maxPosition = this->maxPosition;

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
            if (digitalRead(dtPin) != clkState) {
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
            if (dtState != clkState) {
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
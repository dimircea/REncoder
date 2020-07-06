#ifndef __RENCODER_WITH_SWITCH_H
  #define __RENCODER_WITH_SWITCH_H

  #include <Arduino.h>
  #include "REncoderConfig.h"
  #include "REncoderWithoutSwitch.h"


  /**
   * @brief An implementation of a rotary encoder with a built-in switch button.
   *        The code allows to either make use of IRQs or to do the checks in a loop.
   * @note  Software debouncing is also supported, however, hardware debouncing is 
   *        strongly recommended. The simplest option for hardware debounncing is to 
   *        use 0.1uF / 100nF capacitors between the debouncing pin(s) and GND.
   *        It is also possible to use IRQ for SWITCH but not for the ENCODER rotation
   *        and the other way around. For more information about the possible configuration
   *        parameters, please read documentation inside REncoderConfig.h file.
   */

  class REncoderWithSwitch : public REncoderWithoutSwitch {
    public:
    
      REncoderWithSwitch(int8_t clkPin, int8_t dtPin, int8_t swPin = -1);

      #if !defined(RENCODER_ENABLE_SWITCH_IRQ) && !defined(RENCODER_ENABLE_ENCODER_IRQ)
        /**
         * @brief enable / disable the continuous detection of the SWITCH push. When enabled, the push 
         *        "SWITCH push" action is detected coninuously, without having to release the switch in
         *        between. The minimum time between the a two detections depends on the value of the 
         *        debounceSwitchTolerance class property, which represents the minimum time in milliseconds.
         * @note  When using IRQs for either the ENCODER, of the SWITCH, this feature is disabled and can't be enabled.
         *        Before calling this method, the status of this feature is: disabled (false).
         * @param enableState
         *        Specify the state of the continouous switch detection: enabled (true) or disabled (false).
         * @see debounceSwitchTolerance
         */ 
        void enableContinuousSwitchDetection(bool enableState);

        /**
         * @brief enable / disable the possibility to detect encoder rotation actions during the time of 
         *        having the SWITCH pushed. 
         * @note  When using IRQs for either the ENCODER, of the SWITCH, this feature is enabled and 
         *        it can't be disabled.
         *        Before calling this method, the status of this feature is: enabled (true).
         * @param enableState
         *        Specify the feature: enabled (true) or disabled (false).
         */ 
        void enableEncoderWhenSwitchPushed(bool enableState);
      #endif

      #if !defined(RENCODER_ENABLE_SWITCH_IRQ) || !defined(RENCODER_ENABLE_ENCODER_IRQ)
        #ifndef RENCODER_ENABLE_SWITCH_IRQ
          REncoderWithSwitch::Event reStateSwitch();
        #endif
        #ifndef RENCODER_ENABLE_ENCODER_IRQ
          REncoderWithSwitch::Event reStateEncoder();
        #endif
        /**
         * @brief re-evaluate the encoder state and calculate new encoder position (if changed).
         * @note: only available if both, RENCODER_ENABLE_SWITCH_IRQ and RENCODER_ENABLE_ENCODER_IRQ 
         *        are NOT defined by using the #define directive.
         * @return REncoderWithSwitch::Event element which defines possible changes in the state.
         */
        REncoderWithSwitch::Event reState(void);
      #endif

      #ifdef RENCODER_ENABLE_SWITCH_IRQ
        /**
         * @brief Define the action that is to be take when the rotary encoder push switch is activated.
         * @note: Only available if RENCODER_ENABLE_SWITCH_IRQ is defined by using the #define directive.
         *        It will actually represent the ISR for the interrupt.
         * @param switchPushedHandler - a function reference used as action for "SWITCH pushed" events.

        */
        void attachSwitchHandler(void (*switchHandler)(void));
      #endif

    protected:
      /**
       * @brief perform initialization: pin setup, initial data, etc.
       */
      void init();

      uint8_t lastSwState;
      #ifdef RENCODER_ENABLE_SWITCH_SOFTWARE_DEBOUNCING
        unsigned long lastSwitchDebounceTime = 0;
        uint8_t debounceSwitchTolerance = 5; // 5 miliseconds
      #endif

      // the GPIO pin used for the encoder SW (SWITCH) pin.
      int8_t swPin = -1;  // -1 => not defined      

      #ifndef RENCODER_ENABLE_SWITCH_IRQ
        /**
         * @brief a flag that enables (true) or disables (false) the continuous detection 
         *        of "SWITCH pushed" events. If disabled (false) then a new "SWITCH pushed" event
         *        is only detected after a release of the switch after each push action.
         */
        bool continousSwitchDetection = false;
      #endif

      #ifndef RENCODER_ENABLE_ENCODER_IRQ
        /**
         * @brief a flag that enables (true) or disables (false) the detection of encoder rotation
         *        during the time of having the switch pressed.
         */
        bool enableRotationDetectionWhenSwitchActive = true;
      #endif
  };

  #ifdef RENCODER_ENABLE_SWITCH
    #define REncoder REncoderWithSwitch
  #endif
#endif
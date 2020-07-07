#ifndef __RENCODER_WITHOUT_SWITCH_H
  #define __RENCODER_WITHOUT_SWITCH_H

  #include <Arduino.h>
  #include <limits.h>
  #include "REncoderConfig.h"

    
  #ifdef RENCODER_ENABLE_ENCODER_LONG_RANGE_ROTATION
    typedef long  RENCODER_ROTATION_VALUE_TYPE;
    #define RENCODER_ROTATION_MIN_VALUE LONG_MIN
    #define RENCODER_ROTATION_MAX_VALUE LONG_MAX
  #else
    typedef int RENCODER_ROTATION_VALUE_TYPE;
    #define RENCODER_ROTATION_MIN_VALUE INT_MIN  
    #define RENCODER_ROTATION_MAX_VALUE INT_MAX
  #endif


  /**
   * @brief An implementation of a rotary encoder without a built-in switch button.
   *        The code allows to either make use of IRQs or to do the checks in a loop.
   * @note  Software debouncing is also supported (only if IRQs are not used for the 
   *        encoder), however, hardware debouncing is strongly recommended. 
   *        The simplest option for hardware debounncing is to use 0.1uF / 100nF capacitors 
   *        between the debouncing pin(s) and GND.
   */

  class REncoderWithoutSwitch {
    public:
      
      enum Event {
        REncoder_Event_None,
        REncoder_Event_Rotate_CW,
        REncoder_Event_Rotate_CCW
        #ifndef RENCODER_ENABLE_SWITCH_IRQ
          , REncoder_Event_Switch_Pushed
        #endif
      };
      
      REncoderWithoutSwitch(int8_t clkPin, int8_t dtPin);

      #ifndef RENCODER_ENABLE_ENCODER_IRQ
        /**
         * @brief Get the encoder position. It can a positive or negative integer value.
         *        "Position" means the number of steps moved to the left (-1) / right (+1).
         * @return the encoder position value
         */
        RENCODER_ROTATION_VALUE_TYPE getPosition(void);

        /**
         * @brief Set the actual encoder position. It can a positive or negative integer value.
         *        "Position" means the number of steps moved to the left (-1) / right (+1).
         * @param encoderPosition
         *        the new encoder position value 
         */
        void setPosition(RENCODER_ROTATION_VALUE_TYPE encoderPosition);
      #endif

      /**
       * @brief set the minimum (CCW, Counter-Clock-Wise) "virtual" position.
       * @param minPosition 
       *        minimum virtual position value - counter clock wise 
       */
      void setMinEncoderPosition(RENCODER_ROTATION_VALUE_TYPE minPosition);

      /**
       * @brief set the maximum (CW, Clock-Wise) "virtual" position.
       * @param maxPosition 
       *        maximum virtual position value - counter clock wise 
       */
      void setMaxEncoderPosition(RENCODER_ROTATION_VALUE_TYPE maxPosition);

      #ifdef RENCODER_ENABLE_ENCODER_IRQ
        /**
         * @brief Define the action that is to be take when the rotary encoder is rotated CW or CCW.
         * @note: only available if the configuration parameter RENCODER_ENABLE_ENCODER_IRQ 
         *        is defined. 
         * @param encoderHandler - a function reference used as action for "ENCODER rotated" events.
         */
        void attachEncoderHandler(void (*encoderHandler)(REncoderWithoutSwitch::Event, RENCODER_ROTATION_VALUE_TYPE));
      
      #else
        /**
         * @brief re-evaluate the encoder state and calculate new encoder position (if changed).
         * @note: only available if the configuration parameter RENCODER_ENABLE_ENCODER_IRQ 
         *        is NOT defined.
         * @return REncoder::Event element which defines possible changes in the state.
         */
        REncoderWithoutSwitch::Event reState(void);
      #endif

    protected:
      /**
       * @brief perform initialization: pin setup, initial data, etc.
       */
      void init();

      #ifndef RENCODER_ENABLE_ENCODER_IRQ
        uint8_t lastClkState;
        uint8_t lastDtState;
        
        #ifdef RENCODER_ENABLE_ENCODER_SOFTWARE_DEBOUNCING
          unsigned long lastEncoderDebounceTime = 0;
          uint8_t debounceEncoderTolerance = 2; // 2 miliseconds
        #endif

        /**
         * @brief The actual "virtual" encoder position. 
         *        It increases (+1) for CW rotation and decreases (-1) for CCW rotations.
         *        Default: 0. The value must be in the range [−32768, +32767].
         *        Using setMinEncoderPosition(maxPos) and setMaxEncoderPosition(minPos) you can adjust the range, but 
         *        the values cannot go outside the interval [−32768, +32767] in any case.
         *  @see setMinEncoderPosition
         *  @see setMaxEncoderPosition
         */
        RENCODER_ROTATION_VALUE_TYPE encoderPosition = 0;
      #endif

      // the GPIO pin used for the encoder CLK (CLOCK) pin.
      int8_t clkPin = -1; // -1 => not defined
      // the GPIO pin used for the encoder DT (DATA) pin.
      int8_t dtPin = -1;  // -1 => not defined

      RENCODER_ROTATION_VALUE_TYPE maxPosition = RENCODER_ROTATION_MAX_VALUE;  // default: max positive range
      RENCODER_ROTATION_VALUE_TYPE minPosition = RENCODER_ROTATION_MIN_VALUE; // default: min negative range
  };

  #ifndef RENCODER_ENABLE_SWITCH
    #define REncoder REncoderWithoutSwitch
  #endif
#endif
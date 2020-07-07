#ifndef __RENCODER_H
  #define __RENCODER_H

  #include <Arduino.h>
  
  /**
   * Include the plugin configuration file.
   * For a full list of configuration parameters and their effect, 
   * please read the comments from the REncoderConfig.h file
   * @note the parameters can only be defined in the REncoderConfig.h file, 
   *       and they CAN'T simply just be defined/redefined on your own program 
   *       file(s) due to how the compiler works. 
   */
  #include "REncoderConfig.h"


  /**
   * Software debouncing for the SWITCH is only available 
   * if the switch does NOT use IRQ.
   * The primarily reason for this is to not overcharge the ISR 
   * with all kind of code which actually shall not be there.
   * Use a 0.1uF / 100nF capacitor between the PW and GND pins 
   * instead to have simple harware deboucing. 
   */ 
  #ifdef RENCODER_ENABLE_SWITCH_IRQ
    #undef RENCODER_ENABLE_SWITCH_SOFTWARE_DEBOUNCING
  #endif

  /**
   * Software debouncing for the ENCODER is only available 
   * if the encoder does NOT use IRQs.
   * The primarily reason for this is to not overcharge the ISR 
   * with all kind of code which actually shall not be there.
   * Use a 0.1uF / 100nF capacitor between the CLK and GND pins 
   * as well as between the DT and GND pins instead to have simple 
   * harware deboucing. 
   */ 
  #ifdef RENCODER_ENABLE_ENCODER_IRQ
    #undef RENCODER_ENABLE_ENCODER_SOFTWARE_DEBOUNCING
  #endif

  #ifdef RENCODER_ENABLE_SWITCH
    #include "REncoderWithSwitch.h"
  #else
    #include "REncoderWithoutSwitch.h"
  #endif
#endif
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
   * if the switch uses an IRQ.
   * The primarily reason for this is to not overcharge the ISR 
   * with all kind of code which actually shall not be there.
   * Use an 0.1uF capacitor between the PW and GND pins instead 
   * to get a simple harware deboucing. 
   */ 
  #ifdef RENCODER_ENABLE_SWITCH_IRQ
    #undef RENCODER_ENABLE_SWITCH_SOFTWARE_DEBOUNCING
  #endif

  /**
   * Software debouncing for the ENCODER is only available 
   * if the encoder uses IRQs.
   * The primarily reason for this is to not overcharge the ISR 
   * with all kind of code which actually shall not be there.
   * Use an 0.1uF capacitor between the CLK and GND pins as well 
   * as between the DT and GND pins instead to get a simple 
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
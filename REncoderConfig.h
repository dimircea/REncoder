/**
 * Define various configuration parameters for the library.
 * These parameters are used mostly at the compilation time, 
 * so the compiled code is kept as minimal as possible and 
 * therefore the usage of the precious RAM/FLASH resources of 
 * the small Arduino or similar boards are not used if this is 
 * not really needed.
 * IMPORTANT: due to how the compiler works, you can't simply
 *            just define these parameters in your own code 
 *            such as the Arduino sketch. Instead, you are 
 *            stuck with doing that in this configuration file.
 */


/***************************************
 ** --- SWITCH RELATED PARAMETERS --- **
 ***************************************/

/**
 * If the encoder includes also a SWITCH (usually they do so) then
 * defining the RENCODER_ENABLE_SWITCH allows to activate the SWITCH.
 * If RENCODER_ENABLE_SWITCH is not defined (so the definition 
 * of the following parameter is commented out) then the SWITCH 
 * will not be used by this library.
 */ 
#define RENCODER_ENABLE_SWITCH

/**
 *  ENABLE (uncomment the definition of RENCODER_ENABLE_SWITCH_IRQ) 
 *  or DISABLE (comment out the definition of RENCODER_ENABLE_SWITCH_IRQ) 
 *  the IRQ usage for the switch, if a switch IS available for the rotary encoder.
 *  IMPORTANT: Only used if the parameter RENCODER_ENABLE_SWITCH is enabled/defined.
 */ 
//#define RENCODER_ENABLE_SWITCH_IRQ

/** 
 * ENABLE (uncomment next line) / DISABLE (comment out next line) software dobouncing 
 * for the switch, if a switch IS available on the rotary encoder.
 * IMPORTANT: This parameter is used only if the parameter RENCODER_ENABLE_SWITCH is defined
 *            and the parameter RENCODER_ENABLE_SWITCH_IRQ is NOT defined.
 * NOTE: a better approach will be to debounce by using an 0.1uF capacitor between the SW pin 
 *       and the GND pin, then comment out the next code line (the definition of 
 *       RENCODER_ENABLE_SWITCH_SOFTWARE_DEBOUNCING). By doing so, a small amount of 
 *       resources (RAM/FLASH) are freed up and the overall usability also improves.
 *       
 */ 
#define RENCODER_ENABLE_SWITCH_SOFTWARE_DEBOUNCING

/****************************************
 ** --- ENCODER RELATED PARAMETERS --- **
 ****************************************/

/**
 *  ENABLE (uncomment the definition of RENCODER_ENABLE_ENCODER_IRQ) 
 *  or DISABLE (comment out the definition of RENCODER_ENABLE_ENCODER_IRQ) 
 *  the IRQ usage for the rotary encoder.
 */ 
//#define RENCODER_ENABLE_ENCODER_IRQ 

/** 
 * ENABLE (uncomment the definition of RENCODER_ENABLE_ENCODER_SOFTWARE_DEBOUNCING) 
 * or DISABLE (comment out the definition of RENCODER_ENABLE_ENCODER_SOFTWARE_DEBOUNCING) 
 * software dobouncing for the rotary encoder.
 * IMPORTANT: This parameter is used only if the parameter RENCODER_ENABLE_ENCODER_IRQ is NOT defined.
 * NOTE: a better approach will be to debounce by using 01.uF/ 100nF capacitors between the CLK pin
 *       and the GND pin, as well as between DT pin and the GND pin, then comment out 
 *       the next code line (the definition of RENCODER_ENABLE_ENCODER_SOFTWARE_DEBOUNCING). 
 *       By doing so, a small amount of resources (RAM/FLASH) are freed up and the overall 
 *       usability / feeling may also improve.
 */ 
#define RENCODER_ENABLE_ENCODER_SOFTWARE_DEBOUNCING

/** 
 * ENABLE (uncomment the definition of RENCODER_ENABLE_ENCODER_LONG_RANGE_ROTATION) 
 * or DISABLE (comment out the definition of RENCODER_ENABLE_ENCODER_LONG_RANGE_ROTATION) 
 * the use of the "long" as type for the rotary encoder current rotation value.
 * If this parameter is NOT enabled, the accepted values for the current encoder position 
 * are in the range [-32768, 32767], while if enable, the the values can be in 
 * the range [-2147483648, 214748364].
 */ 
//#define RENCODER_ENABLE_ENCODER_LONG_RANGE_ROTATION

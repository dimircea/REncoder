/*******************************
 ** SWITCH RELATED PARAMETERS **
 *******************************/

/**
 * If the encoder has also a SWITCH (usually they have one) then
 * defining the RENCODER_ENABLE_SWITCH allows to use the SWITCH.
 * If RENCODER_ENABLE_SWITCH is not defined (so the definition 
 * is commented out) then the SWITCH can't be used!
 */ 
#define RENCODER_ENABLE_SWITCH

/**
 *  ENABLE (uncomment the definition of RENCODER_ENABLE_SWITCH_IRQ) 
 *  or DISABLE (comment out the definition of RENCODER_ENABLE_SWITCH_IRQ) 
 *  the IRQ usage for the switch, if one is available for the rotary encoder.
 */ 
#define RENCODER_ENABLE_SWITCH_IRQ

/** 
 * ENABLE (uncomment next line) / DISABLE (comment out next line) software dobouncing 
 * for the switch, if one is available on the rotary encoder.
 * NOTE: a better approach is to debounce by using 01.uF capacitors between the SW pin 
 *       and the GND pin, then comment out the next code line (the definition of 
 *       RENCODER_ENABLE_SWITCH_SOFTWARE_DEBOUNCING). By doing so, a small amount of 
 *       resources (RAM/FLASH) are freed up and the overall usage "feeling" may improve.
 *       THIS ONLY MAKES SENSE IF AND ONLY IF RENCODER_ENABLE_SWITCH IS DEFINED !!!
 */ 
#define RENCODER_ENABLE_SWITCH_SOFTWARE_DEBOUNCING

/********************************
 ** ENCODER RELATED PARAMETERS **
 ********************************/

/**
 *  ENABLE (uncomment the definition of RENCODER_ENABLE_ENCODER_IRQ) 
 *  or DISABLE (comment out the definition of RENCODER_ENABLE_ENCODER_IRQ) 
 *  the IRQ usage for the rotary encoder.
 */ 
//#define RENCODER_ENABLE_ENCODER_IRQ 

/** 
 * ENABLE (uncomment next line) / DISABLE (comment out next line) software dobouncing 
 * for the rotary encoder.
 * NOTE: a better approach is to debounce by using 01.uF capacitors between the CLK pin 
 *       and the GND pin, as well as between DT pin and the GND pin, then comment out 
 *       the next code line (the definition of RENCODER_ENABLE_ENCODER_SOFTWARE_DEBOUNCING). 
 *       By doing so, a small amount of resources (RAM/FLASH) are freed up and the overall 
 *       usage "feeling" may improve.
 */ 
//#define RENCODER_ENABLE_ENCODER_SOFTWARE_DEBOUNCING

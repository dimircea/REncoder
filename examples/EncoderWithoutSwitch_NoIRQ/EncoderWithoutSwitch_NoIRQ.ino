#include <REncoder.h>

/** 
 * The REncoderConfig.h file contains the configuration parameters.
 * For this example, all the SWITCH related parameters are switched off.
 *
 * This example does not use IRQs. The reState method is called in 'loop'.
 *
 * To enable software debouncing, please enable the parameters
 * RENCODER_ENABLE_ENCODER_SOFTWARE_DEBOUNCING in the REncoderConfig.h file.
 *
 * However, if possible, please use 0.1uF/100nF capacitors between 
 * the CLK pin and the GND pin, as well as between the DT and the GND pins 
 * for debouncing instead of using software debouncing. This will improve 
 * the overall usability of the rotary encoder and will also free up some 
 * amount of precious RAM/FLASH resources.
 */
REncoder rEncoder(3 /* CLK Pin*/, 4 /* DT Pin */);

void setup() {
  Serial.begin(115200);

  rEncoder.setMinEncoderPosition(-2);
  rEncoder.setMaxEncoderPosition(3);
}

void loop() {
  REncoder::Event encoderEvent = rEncoder.reState();

  switch (encoderEvent) {
    case REncoder::Event::REncoder_Event_Rotate_CW: 
      Serial.println("Rotation CW to: " 
        + String(rEncoder.getPosition()));
    break;

    case REncoder::Event::REncoder_Event_Rotate_CCW: 
      Serial.println("Rotation CCW to: " 
        + String(rEncoder.getPosition()));
    break;
  }
}
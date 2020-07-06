#include <REncoder.h>

/** 
 * The REncoderConfig.h file contains the configuration parameters.
 * For this example, the RENCODER_ENABLE_SWITCH parameter must be 
 * enabled, otherwise the switch will not work.
 *
 * This example does not use IRQs. The reState method is called in 'loop'.
 *
 * To enable software debouncing, please enable the parameters
 * RENCODER_ENABLE_ENCODER_SOFTWARE_DEBOUNCING for the encoder 
 * and the parameter RENCODER_ENABLE_SWITCH_SOFTWARE_DEBOUNCING 
 * for the switch in the REncoderConfig.h file.
 *
 * However, if possible, please use 0.1uF/100nF capacitors between 
 * the CLK pin and the GND pin, between the the DT and the GND pins,
 * as well as between the SW and GND pins for debouncing instead of 
 * using software debouncing. This will improve the overall usability 
 * of the rotary encoder and will also free up some amount of 
 * precious RAM/FLASH resources.
 */
REncoder rEncoder(3 /* CLK Pin*/, 4 /* DT Pin */, 2 /* SW Pin */);

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
    
    case REncoder::Event::REncoder_Event_Switch_Pushed: 
      Serial.println("Switch pushed.");
    break;
  }
}
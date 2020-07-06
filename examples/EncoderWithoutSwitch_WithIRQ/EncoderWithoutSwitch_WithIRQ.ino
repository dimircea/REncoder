#include <REncoder.h>

/** 
 * The REncoderConfig.h file contains the configuration parameters.
 * For this example, all the SWITCH related parameters are switched off.
 *
 * This example uses IRQ to detect rotary encoder events.
 * IMPORTANT: in the REncoderConfig.h configuration file, the parameter 
 *            RENCODER_ENABLE_ENCODER_IRQ must be enabled / defined.
 *
 * When using IRQ, software debouncing is not available. This means that
 * the RENCODER_ENABLE_ENCODER_SOFTWARE_DEBOUNCING will just be ignored.
 * Please use 0.1uF/100nF capacitors between the CLK pin and the GND pin, 
 * as well as between the DT and the GND pins for debouncing reasons.
 */
REncoder rEncoder(3 /* CLK Pin*/, 4 /* DT Pin */);

void setup() {
  Serial.begin(115200);

  rEncoder.setMinEncoderPosition(-2);
  rEncoder.setMaxEncoderPosition(3);
  
  rEncoder.attachEncoderHandler([](REncoderWithoutSwitch::Event encoderEvent, int16_t encPos) {
    switch (encoderEvent) {
      case REncoder::Event::REncoder_Event_Rotate_CW: 
        Serial.println("IRQ -> Rotation CW to: " + String(encPos));
      break;

      case REncoder::Event::REncoder_Event_Rotate_CCW: 
        Serial.println("IRQ -> Rotation CCW to: " + String(encPos));
      break;
    }
  });
}

void loop() {}
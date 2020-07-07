# What is REncoder ?

REncoder is a simple Rotary Encoder and Switch Button implementation for Adruino and compatible boards.
While working on a Home Automation project, I got in the need of using an **Rotary Encoder** with a builtin **Switch**, to be more specific, the Keyes KY-040 one. 

At first, I was thinking: *of course there are tons of such libraries !*, so i've done my homework and do some search. Soon (well, after a few hours...) I just realized that while there are some libraries here and there that practically are doing that in one way or the other, none of them really worked good (if at all!) on all the boards I needed them to work: the [Arduino UNO](https://store.arduino.cc/arduino-uno-rev3), [Arduino MEGA](https://store.arduino.cc/arduino-mega-2560-rev3) and the [Seeeduino XIAO](https://www.seeedstudio.com/Seeeduino-XIAO-Arduino-Microcontroller-SAMD21-Cortex-M0+-p-4426.html). 

In addition, I wanted to be able to control some things, like if IRQs must be used or not, if the push of the switch is detected continuously or requires a release before the next push, to set limits on the maximum and minimum value of the encoder rotation, to be able to use more than one encoder at once, and so on.
While some of these features were (partially) available in some other libraries, I wasn't satisfied with the results, so it was the time to get to work and write some C/C++ code. A couple of hours and two medium cups of caffe later, I come up with the *REncoder* library. 

Some basic tests shown that the library itself, with just one instance, had a footprint of about 30 Bytes RAM and 1200 Bytes FLASH when no IRQ and no Switch was used. This depends on the board (the above are for on an Arduino UNO) and used compiler, and your own code will of course add up on top of that. 

# How to install REncoder

Rencoder is basicaly just another Arduino library. To use it, you have a multitude of choices, such as:
- download it as zip and install it on your Arduino IDE by using the *"Sketch > Include Library > Add .ZIP Library"* menu;
- download the souce code from here and then copy / paste the header ```(.h)``` and implementation files ```(.cpp)``` files somewhere on your project folder then use ```#include "path-to-library-folder"``` to load them on your sketch;
- use [PlatformIO IDE](https://platformio.org/platformio-ide) and refer the library on your project. I do strongly recommend PlatformIO over Arduino IDE - it is a free plugin for VCode, is is free to use and it is a few light years in front of the Arduino IDE from multiple points of view.
- ... or imagine something by yourself and do it so ...

# Configure the library

This library is configurable. The configuration parameters are available in the ```REncoderConfig.h``` file.
Due to the way on how the compilation works, you can't simply just define these parameters as part of your own code, i.e., inside your own sketch file. The parameters affects the compilation - multiple parts of the code are compiled differently on some of these parameters. The main reason for this, was to keep the usage of the RAM / FLASH resources as low as possible...these are anyway very limited in some boards.

The following parameters / flags are available:

- ```RENCODER_ENABLE_SWITCH```: enable or disable the switch on the rotary encoder. This only works of course if and only if a switch is builtin the rotary encoder. Alternatively, you can use a button in combination with a simple rotary encoder.  <br/>**Default value: enabled, so the switch/button can be used.**
- ```RENCODER_ENABLE_SWITCH_IRQ```: enable or disable the usage of an interrupt (IRQ) for the switch. When using this, make sure that the GPIO connected to the switch / button pin is one that supports interrupts (IRQ), and an interrupt is available for use. Otherwise, the switch / button will either not work at all, or  worst, it may make your program to act strange ... unpredictible. For Arduino boards, check this [Arduino Interrupts page](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/). The Seeeduino XIAO boards allows interrupts on all the pins, but the pins 5 (A5) and 7 (A7) can't use interrupts at the same time. <br/>**Default value: disabled, so no IRQ / interrupts are used for the switch.**
- ```RENCODER_ENABLE_SWITCH_SOFTWARE_DEBOUNCING```: enable or disable the software debouncing for the switch. While this may be an alternative to real debouncing, it also uses additional resources and it is not optimal when the switch ages. Alternatively, use a 01.uF / 100nF capacitor between the SW (or the button) pin and the GND.  <br/>**Default value: enabled, so the software debouncing is active.**
- ```RENCODER_ENABLE_ENCODER_IRQ```: enable or disable the usage of an interrupt (IRQ) for the encoder. When using this, make sure that the CLOCK pin (aka the CLK pin) is connected to a GPIO that supports interrupts, and an interrupt is available for use. For Arduino boards, check this [Arduino Interrupts page](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/). The Seeeduino XIAO boards allows interrupts on all the pins, but the pins 5 (A5) and 7 (A7) can't use interrupts at the same time. <br/>**Default value: disabled, so no IRQ / interrupt is used for the encoder.**
- ```RENCODER_ENABLE_ENCODER_SOFTWARE_DEBOUNCING```: enable or disable the software debouncing for the encoder. While this may be an alternative to real debouncing, it also uses additional resources and it is not very optimal when the encoder ages. Alternatively, use 01.uF / 100nF capacitors between the CLK pin and the GND as well as between the DT pin and GND.  <br/>**Default value: enabled, so the software debouncing is active.**
- ```RENCODER_ENABLE_ENCODER_LONG_RANGE_ROTATION```: enable or disable the long range values for the encoder position. If enabled, the values are in the range `[-2147483648, 2147483647]`, while if disabled, the values are in the range `[-32768, 32767]`. This allows to reduce the RAM usage when you need to use the encoder for human interraction and can be extended when you want to use it for example to count rotations of motors, or track movements when needed.  <br/>**Default value: disabled, so the the value of the encoder position can be in the range `[-32768, 32767]`.**

# Usage examples

In the ```examples``` folder you'll find a set of basic examples. The code comments (in particular, check the header files) may also help in special cases. 

In addition, here are some relevant use cases that shall give you the feeling on how you can use the library and what it can do.

## Example 1 - Simple Encoder: no IRQ and no Switch

For this examples, **all** the library parameters, available in the ```REncoderConfig.h``` configuration file are switched off. 

```
    #include "REncoder.h"
    
    REncoder rEncoder(
        3, // the CLK Pin 
        4  // the DT 
    );

    void setup() {
      rEncoder.setMinEncoderPosition(-2);
      rEncoder.setMaxEncoderPosition(3);
    }
    
    void loop() {
        
      REncoder::Event encoderEvent = rEncoder.reState();
      
      switch (encoderEvent) {
        case REncoder::Event::REncoder_Event_Rotate_CW: 
          // use rEncoder.getPosition() to get the current position
          // This is the case when the encoder is rotated Clock Wise
          // Here add code for what you'll like to happen in this case...
        break;

        case REncoder::Event::REncoder_Event_Rotate_CCW: 
          // use rEncoder.getPosition() to get the current position
          // This is the case when the encoder is rotated Counter Clock Wise
          // Here add code for what you'll like to happen in this case...
        break;
      }
    }
```

## Example 2 - Enabling the Switch

For this example, only the ```RENCODER_ENABLE_SWITCH``` parameter, available in the ```REncoderConfig.h``` configuration file is switched on. The extra code, by comparison with ```Example 1``` is marked as bold.

<pre><code>
    #include "REncoder.h"
    
    REncoder rEncoder(
        3, // the CLK Pin 
        4, // the DT Pin 
        <b>2 // the SW Pin</b> 
    );

    void setup() {
      rEncoder.setMinEncoderPosition(-2);
      rEncoder.setMaxEncoderPosition(3);
    }
    
    void loop() {
        
      REncoder::Event encoderEvent = rEncoder.reState();
      
      switch (encoderEvent) {
        case REncoder::Event::REncoder_Event_Rotate_CW: 
          // This is the case when the encoder is rotated Clock Wise
          // Here add code for what you'll like to happen in this case...
          // NOTE: you can use rEncoder.getPosition() to get the current encoder position
        break;

        case REncoder::Event::REncoder_Event_Rotate_CCW:  
          // This is the case when the encoder is rotated Counter Clock Wise
          // Here add code for what you'll like to happen in this case...
          // NOTE: you can use rEncoder.getPosition() to get the current encoder position
        break;
        
        <b style="color: blue">case REncoder::Event::REncoder_Event_Switch_Pushed: 
          // The switch was activated / the button was pressed
          // // Here add code for what you'll like to happen in this case...
        break;</b>
      }
    }
</code></pre>

## Example 3 - Use IRQ(s)
For this example the following parameters were enabled: ```RENCODER_ENABLE_SWITCH```, ```RENCODER_ENABLE_SWITCH_IRQ``` and ```RENCODER_ENABLE_ENCODER_IRQ```. All these parameters are available in the ```REncoderConfig.h``` configuration file. Notice how the call to ```rEncoder.reState()``` is now missing. It is also important to notice that one can still use IRQ for the switch but not for the encoder, and the other way around. All this is possible by enabling and/or disabling the following two parameters: ```RENCODER_ENABLE_SWITCH_IRQ``` and ```RENCODER_ENABLE_ENCODER_IRQ```.

<pre><code>
    #include "REncoder.h"
    
    REncoder rEncoder(
        3, // the CLK Pin 
        4, // the DT Pin 
        2 // the SW Pin 
    );
    
    void setup() {
      rEncoder.attachSwitchHandler([]() {
        // here add your code to be executed when the switch is pressed
      });

      rEncoder.attachEncoderHandler(
        [](REncoderWithoutSwitch::Event encoderEvent, int16_t encPos) {
        
        switch (encoderEvent) {
          case REncoder::Event::REncoder_Event_Rotate_CW: 
            // here add your code to be executed when the encoder is rotated Clock Wise
            // The current value of the rotation is provided by the <b>encPos</b> parameter
          break;

          case REncoder::Event::REncoder_Event_Rotate_CCW: 
            // here add your code to be executed when the encoder is rotated Counter Clock Wise
            // The current value of the rotation is provided by the <b>encPos</b> parameter
          break;
        }
      });
    }
    
    void loop() {}
</code></pre>

## Some Special features

One of the features that I wanted to have and no other library provided it, was to allow to rotate the encoder when the switch was pushed. This feature only works when the button does not use an IRQ and it is **enabled by default**. It can be controlled by calling the method ```enableEncoderWhenSwitchPushed``` with ```true``` to enable it and ```false``` to disable it.

<pre><code>
    #include "REncoder.h"
    
    REncoder rEncoder(
        3, // the CLK Pin 
        4, // the DT Pin 
        2 // the SW Pin 
    );
    
    void setup() {
      // ... some code ...
      
      <b>// disable the encoder when the switch is kept pressed
      rEncoder.enableEncoderWhenSwitchPushed(false) </b>
      
      // ... some code ...
    }
    
    void loop () {...}
</code></pre>

Another feature that I wanted to have, was to be able to keep the button pressed and to get the event continuously. This was needed to be able to use the encoder with a user interface. This feature only works when the button does not use an IRQ and it is **disabled by default**. It can be controlled by calling the method ```enableContinuousSwitchDetection``` with ```true``` to enable it and ```false``` to disable it.

<pre><code>
    #include "REncoder.h"
    
    REncoder rEncoder(
        3, // the CLK Pin 
        4, // the DT Pin 
        2 // the SW Pin 
    );
    
    void setup() {
      // ... some code ...
      
      <b>// enable the continuous detection of the switch pressed event
      rEncoder.enableContinuousSwitchDetection(true)</b> 
      
      // ... some code ...
    }
    
    void loop () {...}
</code></pre>

## MIT License - free to use at your own risk


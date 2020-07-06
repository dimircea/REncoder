# What is REncoder ?

REncoder is a simple Rotary Encoder and Switch Button implementation for Adruino and compatible boards.
While working on a Home Automation project, I got in the need of using an Rotary Encoder with a builtin Switch. 
First, I was thinking that ofcourse there are tons of such libraries, and start searchin. Soon I realized that while there are some libraries helping with that, none of them really worked good on the three boards I needed them to work: the Arduino UNO, Arduino MEGA and the Seeeduino XIAO. Moreover, I wanted to be able to control some behaviour, such as if IRQs must be used or not, if the push of the switch is detected conitinously or not and also to set limits on the max/min value of the encoder rotation. 
So, a few hours later, I come up with this library, which satisfied my needs.

# How to use REncoder

Rencoder is basicaly just another Arduino library. Therefore you can download it as zip and install it on the Arduino IDE by using the *"Sketch > Include Library > Add .ZIP Library"* menu.
You can also just copy / paste the header (.h) and implementation files (.cpp) files somewhere on your project folder then use ```#include "path-to-library-folder"``` to load them on your sketch. 

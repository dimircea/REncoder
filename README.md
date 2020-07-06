# What is REncoder ?

REncoder is a simple Rotary Encoder and Switch Button implementation for Adruino and compatible boards.
While working on a Home Automation project, I got in the need of using an Rotary Encoder with a builtin Switch. 

At first, I was thinking: *of course there are tons of such libraries !*, so i've start searching. Soon I just realized that while there are some libraries here and there that practically are doing that in one way or the other, none of them really worked good (if at all!) on the boards I needed them to work: the Arduino UNO, Arduino MEGA and the Seeeduino XIAO. 

In addition, I wanted to be able to control some things, like if IRQs must be used or not, if the push of the switch is detected continuously, to set limits on the maximum and minimum value of the encoder rotation, and so on. While some of these features were (partially) available in some other libraries, I wasn't satisfied with the results, so it was the time to get to work and create a such library. A few hours and two cups of caffe later, I come up with this library. Feel free to use it if you need it.

# How to use REncoder

Rencoder is basicaly just another Arduino library. To use it, you have multiple choices, such as:
- download it as zip and install it on your Arduino IDE by using the *"Sketch > Include Library > Add .ZIP Library"* menu;
- download the souce code from here and then copy / paste the header (.h) and implementation files (.cpp) files somewhere on your project folder then use ```#include "path-to-library-folder"``` to load them on your sketch;
- use PlatformIO IDE and refer the library on your project.
- ... or imagine something by yourself and do it so ...

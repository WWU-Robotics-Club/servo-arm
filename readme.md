Servo robot arm inspired by [Pinaut's project](https://www.youtube.com/watch?v=bLnAJ-mSElE)

pot_control controls the arm via a second arm with potentiometers to measure position like in Pinaut's video.

For assembly instructions see the readme under [instructions](instructions/readme.md).

blueberry_servo_arm is made to work with "keyframes" function of [this fork](https://github.com/CalebJ2/Android-Bluetooth-Remote-Control) of the blueberry remote control app. With the app, keyframe animations can be saved on the phone and played back on the arm.

## Parts list

* Set of laser cut parts made out of 1/8 inch plywood. If that isn't an option they could be cut out of cardboard or foamboard. There are .dwg to .pdf converters that could be used to print plans if autocad isn't available.
* 1x Arduino Uno & USB cable
* 1x V5.0 Sensor Shield (or similar)
* 5x 9g servos (I used 1 SG90 and 4 MG90S servos)
* 5x WH148 Rotary Potentiometers 10K Ohm 15mm shaft
* Misc. 20mm and 10mm jumper wires to extend servo wires and connect potentiometers
* (maybe) 1x USB battery bank to power it. The servos can draw more power than some computer USB ports can supply.

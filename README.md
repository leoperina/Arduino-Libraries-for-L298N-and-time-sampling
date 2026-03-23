# READ ME
this repository exists to collect some libraries I've been working on for some time.
Some are more advanced than others, but I put them together because they can work well together.

## introduction
The libraries which are available are:
- accelerometer.h
- controller.h
- encoder.h
- motordriver.h
- timemanager.h

## accelerometer.h
This library is the least sophisticated, it's literally just a function.
Honestly it's here only because I wanted to keep the main code tidy.
It requires MPU6050_tockn.h to work.

## controller.h
The sense of this library is to have a clean way to integrate a PID controller in a code.
As of today it does not have any autocalibration mode.

## encoder.h
This library is done specifically for an incremental encoder I had.
I have tested this function profundly and it seems to work without problems, if used right.

## motordriver.h
Same philosophy as the controller.h library, but for a motor driven by a L298N board or similar.
The idea is to just take the part of the code which is managed by the board and wrap it into a library.

## timemanager.h
This library allows a board to work in a sampled time without interrupting the process. 
It gets less precise as the sample time goes higher, but it is still pretty accurate if the work load is not excessive.

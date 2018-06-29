# ME 433: shaan savarirayan

### general

repo for ME 433 Advanced Mechatronics assignments and projects

*instructor*: Prof. Nick Marchuk

*institution*: Northwestern University, Evanston, IL, USA

*course source*: https://github.com/ndm736/ME433_2018/wiki

### equipment

PIC32MX250F128B microcontroller

## HW1

HW1 assignment description [here](https://github.com/ndm736/ME433_2018/wiki/HW1). my assignment folder [here](https://github.com/shanexavier313/shaansavarirayan_ME433/tree/master/HW1)

build PIC32 breadboard circuit and test demo of blinking LED light (1kHz) and stops blinking in reponse to button push

breadboard circuit:

<a href="url"><img src="https://github.com/shanexavier313/shaansavarirayan_ME433/blob/master/HW1/pic32%20circuit.jpg" height = "50%" width = "50%"></a>

## HW2 & HW3 - PCB CAD

HW2 assignment description [here](https://github.com/ndm736/ME433_2018/wiki/HW2). HW3 assignment description [here](https://github.com/ndm736/ME433_2018/wiki/HW3). my assignment folders [here](https://github.com/shanexavier313/shaansavarirayan_ME433/tree/master/HW2) and [here](https://github.com/shanexavier313/shaansavarirayan_ME433/tree/master/HW3)

create custom PCB of PIC32 circuit using SparkFun Eagle GitHub libraries

5cm x 5cm

checked for errors and Gerber files generated

*schematic*:

<a href="url"><img src="https://github.com/shanexavier313/shaansavarirayan_ME433/blob/master/HW3/pic32%20schematic.png" height = "50%" width = "50%"></a>
  
*board*:

<a href="url"><img src="https://github.com/shanexavier313/shaansavarirayan_ME433/blob/master/HW3/pic32%20board.png"></a>

## HW4 - SPI DAC

HW4 assignment description [here](https://github.com/ndm736/ME433_2018/wiki/HW4). my assignment folder [here](https://github.com/shanexavier313/shaansavarirayan_ME433/tree/master/HW4)

connect PIC32 to DAC (the [MCP4902](http://ww1.microchip.com/downloads/en/DeviceDoc/22250A.pdf)) and run a test demo

<a href="url"><img src="https://github.com/shanexavier313/shaansavarirayan_ME433/blob/master/HW4/SPI%20schematic.png" height = "70%" width = "70%"></a>

## HW5 - I2C pin expander

HW5 assignment description [here](https://github.com/ndm736/ME433_2018/wiki/HW5). my assignment folder [here](https://github.com/shanexavier313/shaansavarirayan_ME433/tree/master/HW5)

connect PIC32 to [MCP23008 I/O expander](http://ww1.microchip.com/downloads/en/DeviceDoc/21919e.pdf) and run a test demo

<a href="url"><img src="https://github.com/shanexavier313/shaansavarirayan_ME433/blob/master/HW5/I2C%20schematic.png" height = "70%" width = "70%"></a>

## HW6 - LCD printing

HW6 assignment description [here](https://github.com/ndm736/ME433_2018/wiki/HW6). my assignment folder [here](https://github.com/shanexavier313/shaansavarirayan_ME433/tree/master/HW6)

use SPI to communicate with this [128 x 160 pixel TFT LCD](https://www.aliexpress.com/item/Free-Shipping-1-8-inch-TFT-touch-LCD-Module-LCD-Screen-Module-SPI-serial-51-drivers/32263827143.html)

video demo [here](https://github.com/shanexavier313/shaansavarirayan_ME433/blob/master/HW6/LCD_Hello%20World!.mp4) (mp4 download required)

## HW7 - LCD control with IMU

HW7 assignment description [here](https://github.com/ndm736/ME433_2018/wiki/HW7). my assignment folder [here](https://github.com/shanexavier313/shaansavarirayan_ME433/tree/master/HW7)

control a flowing bars in x and y directions on LCD screen by rotating [LSM6DS33 Polulu breakout board](https://www.pololu.com/product/2736), with I2C connection

video demo [here](https://github.com/shanexavier313/shaansavarirayan_ME433/blob/master/HW7/IMU_accelerometer.mp4) (mp4 download required)

## HW8 - MPLABX Harmony 

HW8 assignment description [here](https://github.com/ndm736/ME433_2018/wiki/HW8). my assignment folder [here](https://github.com/shanexavier313/shaansavarirayan_ME433/tree/master/HW8)

Implement HW7 using Harmony in MPLABX

## HW9 - USB communication between PIC & PC

HW9 assignment description [here](https://github.com/ndm736/ME433_2018/wiki/HW8). my assignment folder [here](https://github.com/shanexavier313/shaansavarirayan_ME433/tree/master/HW9)

## HW10 - MAF, IIR, FIR low pass filtering

HW10 assignment description [here](https://github.com/ndm736/ME433_2018/wiki/HW10). my assignment folder [here](https://github.com/shanexavier313/shaansavarirayan_ME433/tree/master/HW10)

implement three different low pass filters on the data outputted by the IMU (see HW7 section for datasheet)

<a href="url"><img src="https://github.com/shanexavier313/shaansavarirayan_ME433/blob/master/HW10/filters%20graph.jpg" height="50%" width = "50%"></a>

## HW11 - HID USB Mouse

HW11 assignment description [here](https://github.com/ndm736/ME433_2018/wiki/HW11). my assignment folder [here](https://github.com/shanexavier313/shaansavarirayan_ME433/tree/master/HW11)

## HW12 - "Hello World!" Android App

HW12 assignment description [here](https://github.com/ndm736/ME433_2018/wiki/HW12). my assignment folder [here](https://github.com/shanexavier313/shaansavarirayan_ME433/tree/master/HW12)

Write a "Hello World!" Android app that also returns a slider value

video demo [here](https://github.com/shanexavier313/shaansavarirayan_ME433/blob/master/HW12/Android%20HelloWorld.mp4) (mp4 download required)

## HW13 - Color Recognition Android App

HW13 assignment description [here](https://github.com/ndm736/ME433_2018/wiki/HW13). my assignment folder [here](https://github.com/shanexavier313/shaansavarirayan_ME433/tree/master/HW13)

Write an Android app that recognizes green objects via camera and then highlights them in bright green

video demo [here](https://github.com/shanexavier313/shaansavarirayan_ME433/blob/master/HW13/ColorCamera%20-%20Green.mp4) (mp4 download required)

## HW14 - USB communication between Android and PIC

HW14 assignment description [here](https://github.com/ndm736/ME433_2018/wiki/HW13). my assignment folder [here](https://github.com/shanexavier313/shaansavarirayan_ME433/tree/master/HW14)

video demo [here](https://github.com/shanexavier313/shaansavarirayan_ME433/blob/master/HW14/Android%20CDC.mp4) (mp4 download required)

## Final Project

### description

design and build a laser cut/3d printed robot car that can follow rainbow road on the map below using a PIC32 for motor control and an Android phone camera for image processing

Android code [here](https://github.com/shanexavier313/shaansavarirayan_ME433/tree/master/HW18/android)

PIC code [here](https://github.com/shanexavier313/shaansavarirayan_ME433/tree/master/HW18/firmware)

### map:

<a href="url"><img src="https://github.com/shanexavier313/shaansavarirayan_ME433/blob/master/HW18/techCup2018.png" height = "50%" width = "50%"></a>

### car body (SolidWorks)

base + sides:

<a href="url"><img src="https://github.com/shanexavier313/shaansavarirayan_ME433/blob/master/HW15/car%20base.jpg" height = "50%" width = "50%"><a href="url"><img src="https://github.com/shanexavier313/shaansavarirayan_ME433/blob/master/HW15/car%20side.jpg" height = "50%" width = "50%"></a>

### wheels (OnShape)

<a href="url"><img src="https://github.com/shanexavier313/shaansavarirayan_ME433/blob/master/HW15/wheel.JPG" height = "50%" width = "50%"></a>

### final car

<a href="url"><img src="https://github.com/shanexavier313/shaansavarirayan_ME433/blob/master/HW18/final%20car.jpg" height = "75%" width = "75%"></a>









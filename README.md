# candleBot
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)

This repository holds the software and firmware for a small palm-sized robot that was designed and fabricated in 4 weeks for the University of St. Thomas' microcontroller course. The goal of the robot was that it would autonomously search a maze for a candle and extinguish the candle. The robot's solution for putting out the candle is to actually 'call the fire department' which was either [Tyler Holmes](https://github.com/TDHolmes) or myself.

It is believed that the hardware files for this robot were lost however work is being done to completely redesign the robot from the ground up over here: [PiBot](https://github.com/TDHolmes/PiBot)

This robot was designed around:
* PIC18F97J94 (Main processor, design requirement)
* [PIXY Cam](http://charmedlabs.com/default/pixy-cmucam5/) (Used to perform rudamentary SLAM)
* [FONA](https://www.adafruit.com/product/1946) (Used to 'call the fire department')
* MC33926PNB (Motor controllers)
* Nintendo Wii IR Cameras (2x, stereo vision used for camera 3D localization)

This repo is dormant and there are no future plans to put more work into this project. This project now resides as the first microcontroller project taken on by [Tyler Holmes](https://github.com/TDHolmes) and myself.

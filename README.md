# mbed-os-nfc04a1 
mbed-os-nfc04a1 is the application for the STMicroelectronics X-NUCLEO-NFC04A1 expansion board.
# Overview
This repository include some files and libraries useful to communicate with the X-NUCLEO-NFC04A1.
The following libraries have been used:

- BSP
- libNDEF
- ST25DV
  
# Tested Platforms
This firmware has been tested on STM32 NUCLEO-F401RE
# Example Application
mbed-os-nfc04a1 program gives the User the possibility to read or write the tag of the X-NUCLEO-NFC04A1. The user needs an NFC enabled device as a 
smartphone that has to be at least 10 cm close to the antenna of the X-NUCLEO-NFC04A1. The LEDs indicate the operational mode:

- LED1 is on, by reading the tag the User obtains the parameters of the WiFi access points.
- LED2 is on, by reading the tag the User is redirected to a website through the custom browser of the smartphone.
- LED3 is on, the User can overwrite the value of the tag through the use of any NFC application.
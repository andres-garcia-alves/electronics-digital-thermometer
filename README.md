# Digital Thermometer

Arduino code for a digital thermometer (temperature, humidity and heat index) with auto-OFF functionality.

&nbsp;

This project use the following electronic components:
- 1 x Arduino UNO / Nano v3
- 1 x DHT11 temperature/humidity sensor
- 1 x 3461BS-1 display (4 digit, 7 segment multiplexed display)
- 8 x 1k5 ohm resistors
- 1 x Transistor BC547 NPN
- 1 x Electrolitic capacitor 470uF 10v
- 1 x Push-button
- 1 x Batery 9v


The circuit:
- Pressing the push-button charges the capacitor and puts the transistor in conducting state.
- After the button is released, the capacitor continues to power the base of the transistor for around 20 seconds.
- The current through the transistor powers the Arduino (and rest of the thermometer).
- Arduino constrols the temperature+humidity measurement and the multiplexing process for the 4 digit display.

Notes:
- This thermometer automatically turns off approximately 20 seconds after activation.
- To increase this time, change the capacitor to one of higher capacitance.

&nbsp;

### Screenshots

| Diagram - Schematics 01                           | Diagram - Schematics 02                           |
|---------------------------------------------------|---------------------------------------------------|
| ![](Resources/01 - Diagram Squematic 01.jpg)      | ![](Resources/02 - Diagram Squematic 02.jpg)      |

| Diagram - Physical Layout                         |  Prototype - Main Block                           |
|---------------------------------------------------|---------------------------------------------------|
| ![](Resources/03 - Diagram Physical Layout.jpg)   | ![](Resources/04 - Prototype - Main Block 01.jpg) |

| Prototype - Auto OFF                              |  Prototype - Full                                 |
|---------------------------------------------------|---------------------------------------------------|
| ![](Resources/06 - Prototype - Auto OFF.jpg)      | ![](Resources/07 - Prototype - Full.jpg)          |

| Building 01                                       |  Building 02                                      |
|---------------------------------------------------|---------------------------------------------------|
| ![](Resources/08 - Building 01.jpg)               | ![](Resources/09 - Building 02.jpg)               |

| Project Final                                     | Project Final (YouTube video)                     |
|---------------------------------------------------|---------------------------------------------------|
| ![](Resources/11 - Building 04.jpg)               | [![](Resources/Proyect-Final.jpg)](https://youtu.be/) |

See 'Rescources' sub-folder for more pictures of the proyect.

&nbsp;

### Version History

v1.0 (2022.12.08) - Initial release.  
v1.1 (2022.12.10) - Re-arrange LEDs pin-out to simplefy PCB.  
v1.2 (2022.12.11) - Using masked bits to improve character display.  

&nbsp;

This source code is licensed under GPL v3.0  
Please send me your feedback about this app: andres.garcia.alves@gmail.com

# OpenGBW

This Project extends and adapts the original by Guillaume Besson

More info: https://besson.co/projects/coffee-grinder-smart-scale

as well as the openGBW adaptation by jb-xyz

More info: https://github.com/jb-xyz/openGBW


This mod will add GBW functionality and profiles to basically any coffe grinder that can be started and stopped manually.

The included 3D Models are adapted to the Eureka Mignon XL, but the electronics can be used for any Scale.

-----------

### Differences to jb-xyz's openGBW:

- Enabled rotary encoder to wake the scale from sleep

-----------

### Getting started

1) 3D print the included models or design your own
2) flash the firmware onto an ESP32
3) connect the display, relay, load cell and rotary encoder to the ESP32 according to the wiring instructions
4) go into the menu by pressing the button of the rotary encoder and set your initial offset. -2g is a good enough starting value for a Mignon XL
5) if you're using the grinder's push button to activate the grinder set grinding mode to impulse. If you're connected directly to the motor relay use continuous.
6) if you only want to use the scale to check your weight when single dosing, set scale mode to scale only. This will not trigger any relay switching and start a timer when the weight begins to increase. If you'd like to build your own brew scale with timer, this is also the mode to use.
7) calibrate your load cell by placing a 100g weight on it and following the instructions in the menu
8) set your dosing cup weight
5) exit the menu, set your desired weight and place your empty dosing cup on the scale. The first grind might be off by a bit - the accuracy will increase with each grind as the scale auto adjusts the grinding offset

-----------

### Wiring

#### Load Cell

| Load Cell  | HX711 | ESP32  |
|---|---|---|
| black  | E-  | |
| red  | E+  | |
| green  | A+  | |
| white  | A-  | |
|   | VCC  | VCC/3.3 |
|   | GND  | GND |
|   | SCK  | GPIO 18 |
|   | DT  | GPIO 19|

#### Display

| Display | ESP32 |
|---|---|
| VCC | VCC/3.3 |
| GND | GND |
| SCL | GPIO 22 |
| SDA | GPIO 21 |

#### Relay

| Relay | ESP32 | Grinder |
|---|---|---|
| + | VCC/3.3 | |
| - | GND | |
| S | GPIO 33 | |
| Middle Screw Terminal | | push button |
| NO Screw Terminal | | push button |

#### Rotary Encoder

| Encoder | ESP32 |
|---|---|
| VCC/+ | VCC/3.3 |
| GND | GND |
| SW | GPIO 34 |
| DT | GPIO 23 |
| CLK | GPIO 32 |

-----------

### BOM

- 1x ESP32
    - https://www.amazon.com/ESP-WROOM-32-Development-Microcontroller-Integrated-Compatible/dp/B08D5ZD528?th=1
- 1x HX711 load cell amplifier
    - https://www.amazon.com/dp/B0BLND4VF6?psc=1&ref=ppx_yo2ov_dt_b_product_details
- 1x 0.96" 128x64 OLED I2C Display
    - https://www.amazon.com/dp/B09T6SJBV5?ref=ppx_yo2ov_dt_b_product_details&th=
- 1x KY-040 rotary encoder
    - https://www.amazon.com/WayinTop-Degree-Encoder-Development-Arduino/dp/B07T3672VK/ref=sr_1_1
    - ensure you get rotary encoders with all of their pull-up resistors, otherwise functionality like clicking the knob may be broken
- 1x 500g load cell, dimensions 47 x 12 x 6mm (L*W*T)
    - https://www.amazon.com/uxcell-Weighing-Electronic-Balance-Sensor/dp/B07NRTJCFD/ref=sr_1_1 
    - note that the load cell is harder to find than other components on Amazon and sizes can vary.
- various jumper cables  
- a few WAGO or similar connectors

-----------

### 3D Files

You can find the 3D STL models on thangs.com

Eureka XL: https://thangs.com/designer/jbear-xyz/3d-model/Eureka%20Mignon%20XL%20OpenGBW%20scale%20addon-834667?manualModelView=true

These _should_ fit any grinder in the Mignon line up as far as I can tell.

**Baratza Sette models coming soon!**

There's also STLs for a universal scale in the repo, though it is mostly meant as a starting off point to create your own. You can use the provided files, but you'll need to print an external enclosure for the ESP32, relay and any other components your setup might need.

### Todo:
- menu refactor with additional settings
- grind profiles V1 with weight adjustments
- more detailed instructions (with pictures!)
- 3D Models for Baratza Sette 30, 270, and 270 wi
- upgraded screen and improved UI
- add stepper motor control for grind size adjustment
- add distribution mechanism and control
- Grind profiles V2 for one touch grind size and weight adjustment
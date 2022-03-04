<!-- For new line: \ -->
<!-- Picture: <img src="Photos/" width="300"/>  -->

# About project DRM Watch v2
<p align="center"><img src="Photos/header.png" width="600"/></p>

Arduino-based watch with Nokia 1280 LCD. \
Main challenge of this project is packing as much
as possible stuff inside Arduino Nano with its 32KB of memory and 2KB RAM.\
Programming contributions made by <b>Dr. Failov</b>.\
Hardware design is made by <b>MeltemiOS</b>.


## About project > Features
- Low power consumption, while screen is always showing time;
- Charging over USB, battery status indication;
- Easy to get components needed to assemble;
- For now firmware is stable enough to use device daily;
- Case fits to default 20mm watch bands;
- No need to disassemble device for firmwate update;
- Device easily can be used as arduino playground: battery powered, equipped with 2 buttons, display, buzzer;
- Multiple Watchfaces, can be changed from menu;
- 2-button controlled graphic menu allow access to all functions;
- Alarm, can be set from menu;
- Monophonic melodies, can be used as alarm or played from menu;
- Stopwatch, can be accessed from menu;
- Time can be set from menu;
- Silent mode can be set from menu. Disable all sounds except alarm;
- Sound of pressing buttons can be set from menu;
- If needed, you can reboot watch by long-pressing "Up" button on watchface;
- Flip screen allows you to choose between left-hand and right-hand buttons position;
- Random decision helper: Zrada-Peremoga;
- Screen "About" shows credits and firmware version. Long-press will show you some debug information.


## About project > Photos of device
I have assembled few watches and using it as my everyday watch. Here`s some photos: 
<p align="center">
<img src="Photos/photo_2022-02-18_12-43-26 (2).jpg" width="150"/> <img src="Photos/photo_2022-02-18_12-43-26.jpg" width="150"/>     <img src="Photos/photo_2022-02-18_12-43-26 (4).jpg" width="150"/>
<img src="Photos/photo_2022-02-18_12-43-26 (5).jpg" width="150"/> <img src="Photos/photo_2022-02-18_12-43-26 (3).jpg" width="150"/> <img src="Photos/photo_2022-02-18_00-19-38.jpg" width="150"/>
</p>

## About project > Video overview
YouTube video with device overview: 

[<p align="center"><img alt="DRM Watch v2 Overview" width="300px" src="Photos/youtube-overview.jpg" /> </p>](https://youtu.be/VYrUO039QUw) 
<p align="center">https://youtu.be/VYrUO039QUw </p>



## About project > Overview of Watchfaces
You can change set of watchfaces in firmware. More info about it in "Software" block.

### Watchface "DRM Watch"
The first watchface in project, back from 2016. Inspired by iPod nano. \
Designed by <b>MeltemiOS</b>.
Updates once in second. Not very power-efficient. 
Takes about <b>486 bytes</b> of FLASH memory. 
<p align="center"><img src="Photos/20220228_161025.jpg" width="250"/>
<img src="Photos/photo_2022-01-16_13-16-34.jpg" width="100"/></p>

### Watchface "DRM Lite"
"DRM Watch" without seconds. \
Designed by <b>Dr. Failov</b>.
Updates once in 8 seconds. Power-efficient. 
Takes about <b>430 bytes</b> of FLASH memory. 
<p align="center"><img src="Photos/20220228_160327.jpg" width="250"/></p>

### Watchface "Nomens"
Inspired by Siemens screensaver and Nokia home screen.\
Designed by <b>MeltemiOS</b>.
Updates once in 8 seconds. Power-efficient. 
Takes about <b>666 bytes</b> of FLASH memory. 
<p align="center"><img src="Photos/20220228_161238.jpg" width="250"/>
<img src="Photos/photo_2021-12-17_08-58-21.jpg" width="100"/>
<img src="Photos/photo_2022-01-05_09-30-16.jpg" width="100"/></p>

### Watchface "Zubat"
Project logo on watchface.\
Designed by <b>Dr. Failov</b>.
Updates once in 8 seconds. Power-efficient. 
Takes about <b>336 bytes</b> of FLASH memory. 
<p align="center"><img src="Photos/20220228_161255.jpg" width="250"/></p>

### Watchface "Xelibri"
Inspired by Siemens Xelibri product line. Very memory-hungry watchface.\
Designed by <b>MeltemiOS</b>.
Updates once in 8 seconds. Power-efficient. 
Takes about <b>1528 bytes</b> of FLASH memory. 
<p align="center"><img src="Photos/20220228_162136.jpg" width="250"/>
<img src="Photos/photo_2022-01-01_05-27-44.jpg" width="100"/></p>

### Watchface "Matrix"
Inspired by Matrix film, like font on secret documents.\
Designed by <b>MeltemiOS</b>.
Updates once in 8 seconds. Power-efficient. 
Takes about <b>886 bytes</b> of FLASH memory. 
<p align="center"><img src="Photos/20220228_162259.jpg" width="250"/>
<img src="Photos/photo_2022-03-01_17-50-55.jpg" width="100"/></p>

### Watchface "Life"
Conway's Game of Life as background.\
Designed by <b>Dr. Failov</b>.
Draws 10 frames every 8 seconds. Not Power-efficient, because of animation. 
Takes about <b>684 bytes</b> of FLASH memory. 
<p align="center"><img src="Photos/20220228_160803.jpg" width="250"/>
<img src="Photos/game of life.jpg" width="100"/></p>


## About project > Overview of screens
Here's detailed overview of every screen and mode with recomendations how to use it.
You also can add your own screens, more info about it in "Software" block.

### Init screen
Initial mode. Its goal to init Serial, init display, init RTC, show startup animation, and go to watchface.
Current firmware version is shown on this screen.
If RTC can not be initialized, watchface will not open.
No user input on this screen.
<p align="center"><img src="Photos/20220228_160743.jpg" width="250"/>
<img src="Photos/rtc_err.jpg" width="150"/></p>

### Watchface screen
Screen with watchface. 
Watchfaces is only screen with deep sleep, so device can run for a long time if in watchface mode.
Sleep depends on watchface sleep mode.
Most watcfaces draws 1 frame and sleeps 8 seconds. 
- To enter main menu, press <b>up</b> button once. 
- To force reboot watch, hold <b>up</b> button for 3 seconds. 
- To enable backlight for 7 seconds, press <b>down</b> button once. 
- To keep backlight on and continue animation (if any), hold <b>down</b> button. 
<p align="center"><img src="Photos/20220228_160327.jpg" width="250"/></p>

### Main menu screen
Main menu to access all the features. 
Upper bar contains current temperature (read from RTC), battery status and icons.
Bottom bar contains description of selected item. 
Text available in russian and english. See "Software" block for more.
If inactive for 120 sec, will automatically go to watchface. 
Buttons are indicated on the side of the screen.
- Press <b>up</b> button to confirm selected item.
- Press <b>down</b> button to move cursor down.
<p align="center"><img src="Photos/20220228_160333.jpg" width="250"/></p>

### Application list screen
List of useful applications.
Text available in russian and english. See "Software" block for more.
If inactive for 120 sec, will automatically go to watchface. 
Buttons are indicated on the side of the screen.
- Press <b>up</b> button to confirm selected item.
- Press <b>down</b> button to move cursor down.
<p align="center"><img src="Photos/20220228_160342.jpg" width="250"/></p>

### Stopwatch application
Stopwatch designed to measure the amount of time that elapses between its activation and deactivation.
Stopwatch count time only while application is opened due to power consumption reasons.
There is no auto-exit from this menu, so if you leave watch untouched in this mode, it will discharge and power off. 

Menu items is:
- Back to watchface. Stopwatch will reset.
- Start/Pause stopwatch.
- Reset stopwatch to zero value.

Buttons are indicated on the side of the screen.
- Press <b>up</b> button to confirm selected item.
- Press <b>down</b> button to move cursor down.
<p align="center"><img src="Photos/20220228_160438.jpg" width="250"/></p>

### Alarm
You can select time and melody and alarm will play at that time. Alarm will start only if watchface is opened.
There is no auto-exit from this menu, so if you leave watch untouched in this mode, it will discharge and power off. 

Menu items is:
- Back to apps list.
- Enable/Disable alarm.
- Alarm hour.
- Alarm Minute.
- Alarm Melody.

Buttons are indicated on the side of the screen.
- Press <b>up</b> button to confirm selected item or increment item.
- Press <b>down</b> button to move cursor down.
<p align="center"><img src="Photos/20220228_160517.jpg" width="250"/></p>

# Hardware
<p align="center"><img src="Photos/2022-03-02 Hardware-and-case.jpg" width="400"/></p>
If you want to assemble your own DRM Watch, this block is for you:)
To assemble watch, you will need: <b>circuit board, parts or modules to desolder, case</b>. 
Also, some instruments, much time and some experience.

## Hardware > Used parts
- Arduino Nano (MEGA328P chip)
- Nokia 1280 LCD (PCF8814 chip)
- RTC module (DS3231M chip)
- Li-Po charger module (TC4056A chip)

To get components I've desoldered modules. 
<p align="center">
<img src="Photos/photo_2022-01-11_15-28-52.jpg" width="350"/>
</p>

### Arduino Nano, CH340C and MEGA328P
MEGA328P used as main controller.\
CH340C Is needed to allow programming with USB port.\
Link: https://aliexpress.ru/item/4000903444456.html  
<p align="center">
<img src="Photos/photo_2021-11-05_13-17-31.jpg" height="150"/>
<img src="Photos/Atmega328P-AU.thumb.png.db7299316d0d61c1b34ebc4f1f3128a0.png" height="150"/>
</p>

### Nokia 1280, PCF8814 LCD
Also, this display is used in: Nokia 1202, Nokia 1280, Nokia 1203.
And also compatible with Nokia 1100 LCD, Nokia 1101 LCD, Nokia 1110 LCD, but it will not fit with board.
Display is main output device. \
Link: https://aliexpress.ru/item/32864378445.html  
<p align="center">
<img src="Photos/photo_2021-10-24_09-22-21.jpg" height="150"/>
<img src="Photos/photo_2021-10-16_11-31-45.jpg" height="150"/>
</p>

### RTC module, DS3231M chip
DS3231M is needed to precisely calculate time. \
Link: https://aliexpress.ru/item/4000004876793.html  
<p align="center">
<img src="Photos/1PCS-DS3231-AT24C32-IIC-Precision-RTC-Real-Time-Clock-Memory-Module-For-Arduino-new-original.jpg_220x220xzq55.jpg" width="150"/>
<img src="Photos/photo_2021-12-08_22-56-06.jpg" height="150"/>
<img src="Photos/Screenshot 2021-12-09 004224.png" height="150"/>
</p>

### Passive buzzer, 5.2mm x 5.2mm 
Buzzer allows to play sound signals and melodies. \
Link: https://aliexpress.ru/item/1005003227004618.html  
<p align="center">
<img src="Photos/buzzer.jpg" height="150"/>
<img src="Photos/photo_2021-12-03_20-30-06.jpg" height="150"/>
<img src="Photos/photo_2021-12-03_20-30-32.jpg" height="150"/>
</p>

### Board
I've ordered boards on JLC PCB. Actual version of gerber files to make your order see at `Circuit Board` folder. \
Here's what I got: 
<p align="center">
<img src="Photos/photo_2021-11-30_08-55-54.jpg" height="150"/> 
<img src="Photos/photo_2021-11-30_16-37-08.jpg" height="150"/> 
<img src="Photos/photo_2021-11-30_08-59-16.jpg" height="150"/> 
</p>
<p align="center">(It's older revision on photo) </p>


## Hardware > Schematics
### Board gerber files
You can fing GERBER files for DRM Watch board in `Circuit Board` folder.
<p align="center">
<img src="Photos\v4 20mm.JPG" width="300"/>
</p>

### Board soldering plan, elements list and LCD pinout
Description of elements on board:
<p align="center">
<img src="Photos\2022-01-16 DRMW2_DOC.png" width="300"/>
</p>

### Atmel 328P chip pinout
You can use this schematic as reference. 
<p align="center">
<img src="Photos/Atmega328P-AU.thumb.png.db7299316d0d61c1b34ebc4f1f3128a0.png" width="300"/>
</p>

Used pins:
- D0 - UART RX
- D1 - UART TX
- D2 - Button DOWN (Active HIGH)
- D3 - Button UP (Active HIGH)
- D5 - LCD RST
- D6 - LCD CS
- D7 - LCD MOSI
- D8 - LCD SCK
- D9 - not used
- D10 - LCD Power
- D11 - USB Voltage    
- D12 - Buzzer (Passive)
- D13 - Debug LED
- A1(D15) - LCD Backlight (Active HIGH)
- A4 - RTC SDA
- A5 - RTC SCL

## Hardware > Case 3D Model
You can fing STL files for DRM Watch case in `Case` folder. 
<p align="center">
<img src="Photos/Screenshot 2022-03-01 224852.jpg" width="230"/>
<img src="Photos/Screenshot 2022-03-01 224938.jpg" width="200"/>
</p>

## Hardware > Assembly instruction
### General way to assemble watch:
- Order PCB using `gerber` files, Get all [parts you needed](Photos/photo_2022-01-11_15-28-52.jpg), desolder modules;
- At first, solder parts from Arduino and Lipo charger modules, Double-check all the connections, especially for shorts between chip pins, Let board cool down before testing;
- Connect battery and check if no fire or heat from PCB, Connect charger and check current. Normal value is about 200mA (or about 1A if you did not replacd 1.2K resistance), Don't connect USB without battery - board will not work this way.
- Connect board to USB. If modules works properly, PC will recognize CH340G as connected device;
- If needed, install driver for CH340G: https://drive.google.com/file/d/1BqUo6f5WEd1vqdxt1UWzDh4OgjdQ7Mx1/view ;
- If needed, install Arduino IDE: https://www.arduino.cc/en/software ;
- Copy libraries to your Arduino IDE libraries folder;
- Build project and try to flash firmware. If [flashing successful](Photos/photo_2022-02-17_21-01-05.jpg), you can continue. [Normal log for this state](Photos/photo_2022-02-17_21-01-24.jpg) ;
- Now you can solder RTC, buttons, buzzer, LCD. [Photo](Photos/photo_2022-02-17_22-31-56.jpg) ;
- If successful, watch will turn on, play sound and [show time](Photos/photo_2022-02-17_22-41-40.jpg);
- If any of functions is not working, always keep in mind that any module can be defective out of the box, so you need to have spare ones to replace;
- If all works, carefully wash flux all over the board.
- Now you can assemble device to case and start using it :)

### Here's some photos of assembly process:
<p align="center">
<img src="Photos/photo_2022-02-18_11-24-21.jpg" height="190"/> 
<img src="Photos/photo_2022-02-17_21-01-05.jpg" height="190"/> 
<img src="Photos/photo_2022-02-17_21-01-24.jpg" height="190"/>
<img src="Photos/photo_2022-02-17_22-31-56.jpg" height="190"/> 
<img src="Photos/photo_2022-02-17_22-41-40.jpg" height="190"/> 
<img src="Photos/photo_2022-02-18_00-19-38.jpg" height="190"/>
<img src="Photos/photo_2022-02-19_00-35-44.jpg" height="190"/> 
<img src="Photos/photo_2022-02-19_13-24-18.jpg" height="190"/> 
<img src="Photos/photo_2022-02-19_13-35-22.jpg" height="190"/>
<img src="Photos/photo_2022-02-20_20-00-38.jpg" height="190"/>
</p>

### Assembly video on YouTube:
[<p align="center"><img alt="DRM Watch v2 Assembly" width="300px" src="Photos/youtube-assembly.jpg" /> </p>](https://youtu.be/IrAri0zF-KY)
<p align="center">https://youtu.be/IrAri0zF-KY </p>

## Hardware > Troubleshooting

### Select WTF After flash firmware
<img src="Photos/" width="300"/>
To fix it, go to settings and select watchface from list.

### No device connected or Unrecognized device when connected
<img src="Photos/" width="300"/>
TODO

### No response from board when trying to flash firmware.
<img src="Photos/" width="300"/>
Check your Arduino. (if pin13 LED is blinking when power on, arduino is alive)
TODO

### RTC FAIL on startup
<img src="Photos/" width="300"/>
TODO




# Software
Description of software components and how to build.

## Software > Used libraries
### LCD1202
Used to run nokia display. Also may be compatible with this LCD controllers: `pcf8814`, `ste2007`, `ST7565`, `HX1230`.
Library included in this repo. Just copy it to your libraries folder (`C:\Users\USER\Documents\Arduino\libraries`). \
This library is modified, to allow display flip options and direct access to buffer. So use version of library that included in this repository.
Source: http://arduino.ru/forum/proekty/khronograf-izmeritel-skorosti-puli-ot-prostogo-k-slozhnomu?page=5#comment-136147
### Low-Power-master
Used to allow deep sleep between screen refreshing. 
Library included in this repo. Just copy it to your libraries folder (`C:\Users\USER\Documents\Arduino\libraries`). \
Source: https://github.com/rocketscream/Low-Power
### DS3231M-1.0.6
Used to communicate with RTC module.
Library included in this repo. Just copy it to your libraries folder (`C:\Users\USER\Documents\Arduino\libraries`). \
Source: https://www.arduino.cc/reference/en/libraries/ds3231m/


## Software > How to set language
There is 2 options to select language: `Russian` and `English`.\
If you want use `Russian` language, uncomment `#define LANG_RU` string in `Generic.cpp` file.\
If you want use `English` language, uncomment `#define LANG_EN` string in `Generic.cpp` file.\
Only one string can be active at the time. If you select any language, you have to comment other one.


## Software > How to set watchfaces list
You can include multiple watcfaces in firmware. As much as enough FLASH memory.\
You can configure included wathfaces in file `_DRMWatch2.ino`.\
Update number of included watchfaces, comment or uncomment needed watchfaces, check memory usage.\
Example:
<p align="center"><img src="Photos/config_watchfaces.jpg" width="300"/></p>


## Software > How to add your own watchface
Project has several watchfaces included, but you always can create your own watchface and use it.
Here's instruction how to do it:
- Create file like `WatchFaceMy.cpp` and inherit class `GenericWatchface`. Use other watchfaces as reference.
- Implement virtual methods of `GenericWatchface`. Detailed description of each method you can find in `GenericWatchface.cpp`. Use other watchfaces as reference.
- Function `drawWatchface` draws watchface. You can draw everything you want calling functions from `Display.cpp`.
`drawWatchface` have to be a non-blocking function, othervise watch will not work properly.
Use other watchfaces as reference.
- In file `_DRMWatch2.ino` include your `WatchFaceMy.cpp`. Use other watchfaces as reference.
- In file `_DRMWatch2.ino` in `setup()` function add your watchface to array. Use other watchfaces as reference.
- Update `watchfacesCount` if needed.
- Now update your watch firmware and you can select your new watchface and use it!



## Software > How to add your own melodies
Because of Arduino have <b>VERY</b> limited space, but I want to store long melodies, I made algorythm to 
compress music as much as possible.\
As source I using Nokia-style composer music, named `RTTTL`.\
I made software to convert `RTTTL` to binary codes, which can be played by synthesizer of 
DRM Watch firmware.\
Melodies stored in form of one byte-one note. Array is contains tempo and notes.\
First 2 bits of note is representing note duration (values 4, 8, 16, 32).\
Last 6 bits represents note number counted from low note of first octave.\
Software can be found in `Windows RTTTL to binary converter\RTTTL Converter\bin\Release\net5.0-windows` folder.
<p align="center"><img src="Photos/photo_2021-12-16_22-37-15.jpg" width="400"/></p>

To add your melody to melody list:
- Convert your RTTTL melody to binary array;
- In file `MelodyPlayer.ino` add array and `get...()` function with your melody;
- In file `ModeMenuMelodies.ino` in function `getMelodyByIndex()` add index for your melody;
- In file `ModeMenuMelodies.ino` in array `modeMenuMelodiesItems` add name of your melody;
- In file `myEEPROM.cpp` in constant `#define eepromMelodyCount` update melody count;
- Update firmware on your watch;
- Now your melody will appear in list and can be set as alarm.


# Project history
A long time ago...
## Project history > 2016, First steps
Back in 2016 me and my friend <b>MeltemiOS</b> was playing with arduino and Nokia 5110 LCD.
Then idea of DRM Watch was born. We've assembled one DIY working prototype and stopped development. \
Here's some prorotype photos of these days: 
<p align="center">
<img src="Photos/xwYFapverSc.jpg" width="200"/> <img src="Photos/Kcf5E-HmfqE.jpg" width="200"/> <img src="Photos/RHoSkpuC5Ek.jpg" width="200"/>
<img src="Photos/z0RViSCt2jg.jpg" width="200"/> <img src="Photos/ApKsKMTuODI.jpg" width="200"/> <img src="Photos/n7C6VvySHto.jpg" width="200"/> 
</p>

## Project history > 2021, Development continued
Later, in 2021 for some reason project continued. 
LCD was changed to Nokia 1280 LCD, because it is easier to get and has more reliable connection. 
Here's some prototypes:
<p align="center">
<img src="Photos/photo_2021-12-19_16-08-34.jpg" height="200"/> <img src="Photos/photo_2021-12-05_17-01-19.jpg" height="200"/> <img src="Photos/photo_2021-12-04_13-20-55.jpg" height="200"/>
<img src="Photos/photo_2021-12-08_22-34-49.jpg" height="200"/> <img src="Photos/photo_2021-12-19_19-43-52 (2).jpg" height="200"/> 
</p>




















--------------------------------------------------------------------------------------------
Next part of this page is not structured
--------------------------------------------------------------------------------------------
# Under development
--------------------------------------------------------------------------------------------

### How to add my own screen?
Program contains several screens (menus, watchfaces...).
Every screen is a separate mode. Every mode contains of: modeSetup(), modeLoop(), modeFinish().
Modes can work independently. Modes divided into different files to ease.
Function of main program `loop()` is routing `modeLoop()` to correct mode according to `_mode` value.
Also `setMode()` function is triggering `modeSetup()` and `modeFinish()` for every mode.
To change mode call: `setMode(MODE_INIT);`.
When adding new mode: 
- Create new file with `modeLoop()`, `modeSetup()`, and `modeFinish()` for your mode.
- Define constant for it in main file, like `#define MODE_MENU_SET_BEEP_SOUND (byte)9`.
- Add to main `loop()` call for your `modeLoop()`.
- Call your `modeSetup()` from `setMode()` when entering your mode.
- Call your `modeFinish()` from `setMode()` when leaving your mode.
- Call `setMode(YOUR_MODE);` when you want to enter your new screen.
- Don't forget to call `goToWatchface()` or `setMode()` to exit your mode if needed.


### ModeMenuMelodies
Menu with list of melodies, which can be played. If inactive for 120 sec, will automatically go to watchface.
Press button Up to select. Press button Down to move cursor down.\
<img src="Photos/photo_2021-12-19_19-43-52 (4).jpg" width="300"/>

### ModeMenuSetTime
Menu to set correct time manually. There is no auto-exit from this menu, 
so if you leave watch untouched in this mode, it will discharge and power off.
Button down is moving field selection, button up is incrementing value.\
<img src="Photos/photo_2021-12-19_19-43-52 (5).jpg" width="300"/>

### ModeAbout
Information about developers and version.\
<img src="Photos/photo_2021-12-19_19-43-52 (8).jpg" width="300"/>

### modeZrada
Genegates random conscusion: "Peremoga" or "Zrada". This is local Ukrainian meme.
"Peremoga" is "win", "Zrada" is "treason".
Mechanics the same as heads and tails.\
<img src="Photos/" width="300"/>

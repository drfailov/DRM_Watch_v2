<!-- For new line: \ -->
<!-- Picture: <img src="Photos/" width="300"/>  -->

# About project DRM Watch v2
<p align="center"><img src="Photos/header.png" width="600"/></p>

Arduino-based watch with Nokia 1280 LCD. \
Main challenge of this project is packing as much
as possible stuff inside Arduino Nano with its 32KB of memory and 2KB RAM.\
Programming contributions made by <b>Dr. Failov</b>.
<!--Hardware design is made by <b>MeltemiOS</b>. -->


## About project > Features
- Low power consumption, while screen is always showing time;
- Charging over USB, battery status indication;
- Easy to get components needed to assemble;
- For now firmware is stable enough to use device daily;
- Case fits to default 20mm watch bands;
- No need to disassemble device for firmwate update;
- Device easily can be used as arduino playground: battery powered, equipped with 2 buttons, display, buzzer;
- Water-resistance up to 0 meters :)
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
I have assembled few watches and using it as my everyday watch for over a year. 
My device has battery about 80mAh capacity and works about 5 days for one charge.
Other device with 250mAh battery lasts about 2 weeks for one charge.
According to my tests, time error can't be noticed in 1 mounth perspective: RTC is very precise.

Here's some photos of watches with SLS case: 
<p align="center">
<img src="Photos/photo_2023-04-19_13-19-54.jpg" height="160"/> 
<img src="Photos/photo_2023-04-19_13-19-54 (2).jpg" height="160"/> 
<img src="Photos/photo_2023-04-19_13-19-54 (3).jpg" height="160"/> 
<img src="Photos/photo_2023-04-19_13-19-54 (4).jpg" height="160"/> 
<img src="Photos/photo_2023-04-19_13-19-54 (5).jpg" height="160"/> 
<img src="Photos/photo_2023-04-19_13-19-54 (6).jpg" height="160"/> 
</p>

And some photos of watches with FDM case:
<p align="center">
<img src="Photos/photo_2023-04-19_00-23-33 (4).jpg" height="200"/>
<img src="Photos/photo_2023-04-19_00-23-33 (3).jpg" height="200"/> 
</p>




## About project > Video overview
YouTube video with device overview: 

[<p align="center"><img alt="DRM Watch v2 Overview" width="300px" src="Photos/youtube-overview.jpg" /> </p>](https://youtu.be/VYrUO039QUw) 
<p align="center">https://youtu.be/VYrUO039QUw </p>


## About project > Typical problems
Regarding watches: they have two typical problems.
1) Water. There is essentially no protection against water, so you need to avoid getting water on them, and especially inside.
2) Statics. Static can occur when plugged into a charger, or when putting on/taking off a sweater or other synthetic clothing.
Therefore, the watch must either be removed for a while, or move slowly so that static in large quantities does not have time to form.


If static has already affected the clock, then:
- usually the display suffers first, there are artifacts. For six months, I had this happen 5 times. 
In this case, the watch can be reset (hold down the top button until you see the loading animation).
- A complete freeze of the controller may occur up to the impossibility of rebooting. 
Then you need to disassemble the watch and reconnect the battery, or wait for the battery to be FULLY discharged and then charge the fully discharged watch.
In the meantime, time will slip. (In my six months of use, this was 1 time).
- The controller may also be affected. (in theory, in practice I haven’t had this for half a year of use)
In this case, it needs to be replaced with a new one (solder the microcircuit)


## About project > Overview of Watchfaces
You can change set of watchfaces in firmware. More info about it in "Software" block.

### Watchface "DRM Watch"
The first watchface in project, back from 2016. Inspired by iPod nano. 
Takes about <b>486 bytes</b> of FLASH memory. 
<p align="center"><img src="Photos/20220228_161025.jpg" width="250"/>
<img src="Photos/photo_2022-01-16_13-16-34.jpg" width="100"/></p>

### Watchface "DRM Lite"
"DRM Watch" without seconds. \
Designed by <b>Dr. Failov</b>.
Takes about <b>430 bytes</b> of FLASH memory. 
<p align="center"><img src="Photos/20220228_160327.jpg" width="250"/></p>

### Watchface "Nomens"
Inspired by Siemens screensaver and Nokia home screen.
Takes about <b>666 bytes</b> of FLASH memory. 
<p align="center"><img src="Photos/20220228_161238.jpg" width="250"/>
<img src="Photos/photo_2021-12-17_08-58-21.jpg" width="100"/>
<img src="Photos/photo_2022-01-05_09-30-16.jpg" width="100"/></p>

### Watchface "Zubat"
Project logo on watchface.\
Designed by <b>Dr. Failov</b>.
Takes about <b>336 bytes</b> of FLASH memory. 
<p align="center"><img src="Photos/20220228_161255.jpg" width="250"/></p>

### Watchface "Xelibri"
Inspired by Siemens Xelibri product line. Very memory-hungry watchface.
Takes about <b>1528 bytes</b> of FLASH memory. 
<p align="center"><img src="Photos/20220228_162136.jpg" width="250"/>
<img src="Photos/photo_2022-01-01_05-27-44.jpg" width="100"/></p>

### Watchface "Matrix"
Inspired by Matrix film, like font on secret documents.
Takes about <b>886 bytes</b> of FLASH memory. 
<p align="center"><img src="Photos/20220228_162259.jpg" width="250"/>
<img src="Photos/photo_2022-03-01_17-50-55.jpg" width="100"/></p>

### Watchface "Minimal"
Shows only time. Press DOWN button to show more info.
Takes about <b>446 bytes</b> of FLASH memory. 
<p align="center"><img src="Photos/photo_2022-09-24_13-10-24.jpg" width="250"/>
<img src="Photos/photo_2022-09-24_13-10-24 (2).jpg" width="100"/></p>

### Watchface "Life"
Conway's Game of Life as background.\
Designed by <b>Dr. Failov</b>.
Takes about <b>684 bytes</b> of FLASH memory. 
<p align="center"><img src="Photos/20220228_160803.jpg" width="250"/>
<img src="Photos/game of life.jpg" width="100"/></p>

### Watchface "Calibri"
Simple but informative watchface with font "Calibri".\
Designed by <b>Dr. Failov</b>.
Takes about <b>1340 bytes</b> of FLASH memory. 
<p align="center"><img src="Photos/photo_2022-03-16_02-10-08.jpg" width="250"/>

### Watchface "Thermo"
The only information shown is temperature with font "Calibri". Very memory-hungry watchface.\
Designed by <b>Dr. Failov</b>.
Takes about <b>1466 bytes</b> of FLASH memory. 
<p align="center"><img src="Photos/thermo_demo.png" width="250"/>




## About project > Overview of screens
Here's detailed overview of every screen and mode with recomendations how to use it.
You also can add your own screens, more info about it in "Software" block.

### Init screen
Initial mode. Its goal to init Serial, init display, init RTC, show startup animation, and go to watchface.
Current firmware version is shown on this screen.
If RTC can not be initialized, watchface will not open.
No user input on this screen.
<p align="center">
<img src="Photos/20220228_160743.jpg" width="250"/>
<img src="Photos/rtc_err.jpg" width="150"/>
</p>

### Watchface screen
Screen with watchface. 
Watchfaces is only screen with deep sleep, so device can run for a long time if in watchface mode.

First 30 seconds after user input watchface is updating without sleep. After 30 seconds: draws 1 frame in 8 seconds.
When battery is low, 1 frame in 8s sleep is used for any watchface.
- To enter main menu, press <b>up</b> button once. 
- To force reboot watch, hold <b>up</b> button for 3 seconds. 
- To enable backlight for 7 seconds, press <b>down</b> button once. 
- To keep backlight on and continue animation (if any), hold <b>down</b> button. 
<p align="center">
<img src="Photos/20220228_160327.jpg" width="250"/>
</p>

### Main menu screen
Main menu to access all the features. 
Upper bar contains current temperature (read from RTC), battery status and icons.
Bottom bar contains description of selected item. 
Text available in russian and english. See "Software" block for more.
If inactive for 120 sec, will automatically go to watchface. 
Buttons are indicated on the side of the screen.
- Press <b>up</b> button to confirm selected item.
- Press <b>down</b> button to move cursor down.
<p align="center">
<img src="Photos/20220228_160333.jpg" width="250"/>
</p>

### Application list screen
List of useful applications.
Text available in russian and english. See "Software" block for more.
If inactive for 120 sec, will automatically go to watchface. 
Buttons are indicated on the side of the screen.
- Press <b>up</b> button to confirm selected item.
- Hold <b>up</b> button for 3 seconds to go back to watchface.
- Press <b>down</b> button to move cursor down.
<p align="center">
<img src="Photos/20220228_160342.jpg" width="250"/>
</p>

### Stopwatch application
Stopwatch designed to measure the amount of time that elapses between its activation and deactivation.
Stopwatch count time only while application is opened due to power consumption reasons.
There is no auto-exit from this menu, so if you leave watch untouched in this mode, it will discharge and power off (time will reset). 

Buttons are indicated on the side of the screen.
- Press <b>up</b> button Start/Pause stopwatch.
- Hold <b>up</b> button to Back to watchface. Stopwatch will reset.
- Press <b>down</b> button to Reset stopwatch to zero value.
<p align="center">
<img src="Photos/photo_2022-03-16_18-51-27.jpg" width="250"/>
</p>

### Alarm
You can select time and melody and alarm will play at that time. Alarm will start only if watchface is opened.
There is no auto-exit from this menu, so if you leave watch untouched in this mode, it will discharge and power off (time will reset). 

Menu items is:
- Back to apps list.
- Enable/Disable alarm.
- Alarm hour.
- Alarm Minute.
- Alarm Melody.

Buttons are indicated on the side of the screen.
- Press <b>up</b> button to confirm selected item or increment item.
- Press <b>down</b> button to move cursor down.
<p align="center">
<img src="Photos/20220228_160517.jpg" width="250"/>
<img src="Photos/20220228_160610.jpg" width="250"/>
</p>

### Zrada
Genegates random conscusion: "Peremoga" or "Zrada". This is local Ukrainian meme.
"Peremoga" is "win", "Zrada" is "treason".
Mechanics the same as heads and tails.
There is no user input, after message opens apps list.
<p align="center">
<img src="Photos/20220228_160539.jpg" width="250"/>
<img src="Photos/20220228_160543.jpg" width="250"/>
</p>

### Melodies list
Menu with list of melodies, which can be played.
If inactive for 120 sec, will automatically go to watchface. 
Buttons are indicated on the side of the screen.
- Press <b>up</b> button to confirm selected item.
- Hold <b>up</b> button for 3 seconds to go back to watchface.
- Press <b>down</b> button to move cursor down.\
When melody is playing:
- Press <b>up</b> button to exit back to list.
- Hold <b>up</b> button to loop melody.
There is no auto-exit from melody playing if loop, so if you leave watch untouched in this mode, it will discharge and power off (time will reset).
<p align="center">
<img src="Photos/20220228_160601.jpg" width="250"/>
<img src="Photos/20220228_160610.jpg" width="250"/>
</p>

### Life
Game of life is a cellular automaton.
There is no auto-exit from this menu, so if you leave watch untouched in this mode, it will discharge and power off(time will reset).
- Press <b>up</b> button to fill screen with random pattern.
- Hold <b>up</b> button to exit to watchface.

### Meow
Watch will meow until you stop it.
There is no auto-exit from this menu, so if you leave watch untouched in this mode, it will discharge and power off(time will reset).
- Press <b>up</b> button to exit to watchface.


### Settings screen
Main place where you can change parameters of wor DRM Watch.
If inactive for 120 sec, will automatically go to watchface. 

Menu items is:
- Back to main menu.
- Enable or disable silent mode. In silent mode watch will not play any sound except alarm.
- Flip screen. 
You can select optimal screen orientation for wearing watch on left or right hand. 
Every screen and application will adapt to selected screen orientation.
- Watchface selection.
You can choose watchface from list of watchfaces you included in firmware.
If watchface count set incorrectly, "-" option can appear in list.
If no watchface is included in firmware, "Select WTF" text will appear on watchfaces screen.
- Sound on keypress. 
There are different options for buttons sound: beep, click, tone, whistle, none.
After changing value you can immediately hear new sound.
- Set time and date.

Buttons are indicated on the side of the screen.
- Press <b>up</b> button to confirm/change selected item.
- Hold <b>up</b> button for 3 seconds to go back to watchface.
- Press <b>down</b> button to move cursor down.
<p align="center">
<img src="Photos/20220228_160650.jpg" width="250"/>
<img src="Photos/20220228_160658.jpg" width="250"/>
</p>

### Time setting screen
Menu to set correct time manually. 
There is no auto-exit from this menu, so if you leave watch untouched in this mode, it will discharge and power off (time will reset).
Time is storing in RTC while RTC is powered. If battery is discharged and watch power off, time will reset.
To prevent resetting time you can attach backup power to RTC's Vbat according to its datasheet.

Menu items is:
- Back to settings list.
- Current hour.
- Current minute.
- Current day of month.
- Current month.
- Current year (20xx).
- Save values: write data to RTC.

Buttons are indicated on the side of the screen.
- Press <b>up</b> button to confirm/change selected item.
- Press <b>down</b> button to move cursor down.
<p align="center">
<img src="Photos/20220228_160721.jpg" width="250"/>
</p>

### "About" screen
Information about developers and firmware version.
If inactive for 120 sec, will automatically go to watchface. 

Buttons:
- Press <b>up</b> button to go to watchface.
- Hold <b>up</b> button for 3 seconds to go to debug screen.
<p align="center">
<img src="Photos/20220228_160403.jpg" width="250"/>
</p>

### Debug screen
Technical status information about system.
Also, technical information is indicated in Serial logs.
There is no auto-exit from this menu, so if you leave watch untouched in this mode, it will discharge and power off (time will reset).

Information shown:
- `VLT`: Current battery voltage detected by Arduino.
Allows to check if voltage reading is correct and calibrate values if needed.
Value interpreting is 4092 = 4.092v.
Also this value indicated in battery indicator, but in form of bars.
- `RAM`: Remaining free RAM in runtime. 
To prevent overfilling while implementing new functions.
Value is in bytes. Also this value indicated in serial log when mode changes.
- `CHG`: Status of connected charger. 
Helps debug charger detection.
1 means charger connected, 0 means no charger connected.
Also this value indicated on battery indicator as lightning near icon.
- `aLD`: Last day (of month) when alarm was run.
Helps to debug alarm and process behavior on "empty" brand new Arduinos without any settings.
Value is important because it is not indicated anywhere else.
- `WTF`: Current value of selected watchface index.
System has protection in case of incorreclty set watchface number, 
so only way to get know about data in memory is this value.
Helps to process behavior on "empty" brand new Arduinos without any settings.

Buttons:
- Press <b>up</b> or <b>down</b> button to go to watchface.
<p align="center">
<img src="Photos/20220228_160415.jpg" width="250"/>
</p>

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
Why desoldering instead of buying components separately?
Because I had a lot of situations when received defective chips out of the box.
Buying modules can be more expencive, but more reliable.
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
You can fing GERBER files for DRM Watch board in `Circuit Board` folder. Case is designed to fit <b>1mm thick</b> board.
<p align="center">
<img src="Circuit Board\Плата DRMW2 v7\board_v7_view1.png" width="300"/>
</p>

### Board soldering plan, elements list
Description of elements on board:
<p align="center">
<img src="Circuit Board\Плата DRMW2 v7\board_v7_info1.png" width="300"/>
<img src="Circuit Board\Плата DRMW2 v7\board_v7_info2.png" width="300"/>
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
There's 2 types of case available. 
You can edit both of my cases for you, use my Fusion 360 project: `DRM Watch v85.f3d`.
<p align="center">
<img src="Photos/Screenshot 2023-04-08 161535.jpg" height="150"/>
<img src="Photos/Screenshot 2023-04-08 144433.jpg" height="150"/>
<img src="Photos/Screenshot 2023-04-08 161426.jpg" height="150"/>
</p>

One is more fancy, but can't be printed on FDM printer, better is to order SLS printing. 
You can fing use files `2022-10-12 Back v38.stl` and `2022-10-06 Front v35.stl`.
<p align="center">
<img src="Photos/Screenshot 2022-03-01 224852.jpg" height="270"/>
<img src="Photos/Screenshot 2022-03-01 224938.jpg" height="270"/>
</p>

Second is adapted to FDM printing. Now it's files `Front Case FDM v85.stl` and `Back Case FDM v85.stl`.
<p align="center">
<img src="Photos/Screenshot 2023-04-11 234327.jpg" height="200"/>
<img src="Photos/Screenshot 2023-04-11 234349.jpg" height="200"/>
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

### No any activity after connecting battery
- Battery protection is blocking power. Connect to USB or charger to start BMS.
- Connect charger and check for current by USB Charger Doctor. Correct value is about 200-600mA.
- Check if battery protection ICs soldered in correct orientation.
- Check voltage on Arduino.
- Replace battery protection ICs and its related components.

### No device connected or Unrecognized device on PC when USB connected
- Check if CH340 is soldered in correct orientation. 
- Check or replace resonator (if any). 
- Check USB wiring.
- Check if USB contacts is dirty.
- Wipe flux from USB port.
- Check for shorts between chip pins.
- Replace CH340 and its related components.

### No response from board when trying to flash firmware.
- Check if Atmel328 is soldered in correct orientation.
- Check your Arduino. (if pin13 LED is blinking when power on, arduino is alive) 
- Check wiring from CH340 to Atmel328.
- Check if resistance for UART line is not broken.
- Check if capacitance for RESET pin is not broken or shorted.
- Check for shorts between chip pins.
- Wipe flux from board.
- Replace CH340 and Atmel328 and its related components.

### Arduino is not working, pin13 LED is not blinking
- Check if Atmel328 is soldered in correct orientation.
- Check if battery is connected. Device will not work without battery.
- Check if Atmel328 is OK at all: if it was working on original Arduino board.
- Check for shorts between chip pins.
- Check or replace resonator (if any). 
- Wipe flux from board.
- Replace Atmel328 and its related components.

### RTC FAIL on startup
- Check if RTC is soldered in correct orientation.
- Check if resistance for i2c line is not shorted or broken.
- Check if power is present on RTC chip.
- Check for shorts between chip pins.
- Wipe flux from board.
- Replace RTC and its related components.

### Select WTF After flash firmware
- Check if watchfaces count set correctly
- Check if watchfaces is included in firmware. 
- Add or uncomment watchfaces and flash again.



# Software
Description of software components and how to build.

## Software > Firmware versions
There are different versions of firmware with different purposes.

### _DRMWatch2
Main version, full functionality, full memory usage.
<p align="center">
<img src="Photos/photo_2022-10-05_23-08-49.jpg" height="200"/>
</p>

### _DRMWatch2_MinimalEdition
Functional version available for daily use, but totally reduced memory usage. 
You can use it for write your own applications for watch.
<p align="center">
<img src="Photos/photo_2022-10-05_23-08-49 (2).jpg" height="200"/>
</p>

### _DRMWatch2_FactoryTest
Just testing hardware, you can use it to build your own firmware from scratch.
<p align="center">
<img src="Photos/photo_2022-10-05_23-04-28.jpg" height="200"/>
</p>


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


## Software > How to build
- Install Arduino IDE.
I used Arduino 1.8.16.
Link: https://www.arduino.cc/en/software ;
- Because Arduino IDE don't have drivers for CH340, you need to install drivers manually.
You can find drivers enywhere over Internet.
I found here: https://drive.google.com/file/d/1BqUo6f5WEd1vqdxt1UWzDh4OgjdQ7Mx1/view ;
- Copy libraries to your Arduino IDE libraries folder;
- Open project and try to build it. If all steps done correctly, project will build successfully.


## Software > How to set language
There is 2 options to select language: `Russian` and `English`.\
If you want use `Russian` language, uncomment `#define LANG_RU` string in `Generic.cpp` file.\
If you want use `English` language, uncomment `#define LANG_EN` string in `Generic.cpp` file.\
Only one string can be active at the time. If you select any language, you have to comment other one.


## Software > How to set watchfaces list
You can include multiple watcfaces in firmware. As much as enough FLASH memory.\
You can configure included wathfaces in file `_DRMWatch2.ino`.\
Update number of included watchfaces, comment or uncomment needed watchfaces, check memory usage.\
If no watchface is included in firmware, "Select WTF" text will appear on watchfaces screen.\
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


## Software > How to add your own application
You can modify source and add own application.
Program contains several screens (menus, applications).
Every screen is a separate `mode`. Every mode contains of: `modeSetup()`, `modeLoop()`, `modeFinish()`.
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
- When your mode is active, only your mode's `loop()` will be called. 
So mode have all control over device. 
If your mode will be empty, so device will do nothing after activation your mode, 
and you can't even exit to menu or reboot if you don't implemented this.
- If you stuck with your mode, the easiest way to reboot watch is connect it to USB and reflash.


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

Melody player: https://zserge.com/nokia-composer/ (link actual 2022-11)
Melody repository: https://nokia.nigelcoldwell.co.uk/tunes.html (link actual 2022-11)

Video describing this process you can see here:
https://www.youtube.com/watch?v=Ek3eQStupCs


# Project history
A long time ago...
## Project history > 2016, First steps
Back in 2016 me and my friend was playing with arduino and Nokia 5110 LCD.
Then idea of DRM Watch was born. Why "DRM"? It's first letters from my and my friend's nicknames:)
We've assembled one DIY working prototype and stopped development. \
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
<img src="Photos/photo_2021-12-19_16-08-34.jpg" height="150"/>
<img src="Photos/photo_2021-12-05_17-01-19.jpg" height="150"/> 
<img src="Photos/photo_2021-12-04_13-20-55.jpg" height="150"/>
<img src="Photos/photo_2021-12-08_22-34-49.jpg" height="150"/> 
<img src="Photos/photo_2021-12-19_19-43-52 (2).jpg" height="150"/> 
</p>

## Project history > 2022, Closer to complete device
In 2022 I had device with 3d printed case and used it as my daily watch.
<p align="center">
<img src="Photos/photo_2022-02-18_12-43-26 (2).jpg" width="170"/> 
<img src="Photos/photo_2022-02-18_12-43-26.jpg" width="170"/> 
<img src="Photos/photo_2022-02-18_12-43-26 (4).jpg" width="170"/>
<img src="Photos/photo_2022-02-18_12-43-26 (5).jpg" width="170"/> 
<img src="Photos/photo_2022-02-18_12-43-26 (3).jpg" width="170"/> 
<img src="Photos/photo_2022-02-18_00-19-38.jpg" width="170"/>
</p>


## Project history > Funny fails
Not every step is successful, here's some videos with funny fails:
<p align="center"> https://youtu.be/Ur8o4e1e8V8 </p>
<p align="center"> https://youtu.be/18OF_WzMhGE </p>




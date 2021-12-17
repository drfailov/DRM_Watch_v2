<!-- For new line: \ -->
<!-- Picture: <img src="Photos/" width="300"/>  -->

# DRM_Watch v2

Arduino-based watch with Nokia 1280 LCD. 

##Used components:
- Arduino Nano (MEGA328P chip)
- Nokia 1280 LCD (PCF8814 chip)
- RTC module (DS3231M chip)
- Li-Po charger module (TC4056A chip)


\
\
##To get components I've desoldered modules. 

<b>Arduino Nano, CH340C and MEGA328P</b> \
MEGA328P used as main controller.\
CH340C Is needed to allow programming with USB port.\
Link: https://aliexpress.ru/item/4000903444456.html  \
<img src="Photos/photo_2021-11-05_13-17-31.jpg" width="300"/>
<img src="Photos/Atmega328P-AU.thumb.png.db7299316d0d61c1b34ebc4f1f3128a0.png" width="300"/>
 \
 \
<b>Nokia 1280, PCF8814 LCD </b> \
Display is main output device. \
Link: https://aliexpress.ru/item/32864378445.html  \
<img src="Photos/photo_2021-10-24_09-22-21.jpg" width="300"/>
<img src="Photos/photo_2021-10-16_11-31-45.jpg" width="300"/>
 \
 \
<b>RTC module, DS3231M chip</b> \
DS3231M is needed to precisely calculate time. \
Link: https://aliexpress.ru/item/4000004876793.html  \
<img src="Photos/1PCS-DS3231-AT24C32-IIC-Precision-RTC-Real-Time-Clock-Memory-Module-For-Arduino-new-original.jpg_220x220xzq55.jpg" width="300"/>
<img src="Photos/photo_2021-12-08_22-56-06.jpg" width="300"/>
<img src="Photos/Screenshot 2021-12-09 004224.png" width="300"/>
\
\
<b>Passive buzzer, 5.2mm x 5.2mm </b> \
Buzzer allows to play sound signals and melodies. \
Link: https://aliexpress.ru/item/1005003227004618.html  \
<img src="Photos/buzzer.jpg" width="300"/>
<img src="Photos/photo_2021-12-03_20-30-06.jpg" width="300"/>
<img src="Photos/photo_2021-12-03_20-30-32.jpg" width="300"/>
 \
 \
 ## Code description
 
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
 - Don`t forget to call `goToWatchface()` or `setMode()` to exit your mode if needed.
\

### Mode description

#### ModeInit
Initial mode. Its goal to init Serial, init display, init RTC, show startup animation, and go to watchface.

#### ModeWatchFace1
Whow time, date. Watchfaces is only screen with deep sleep, so device can run for a long time if in watchface mode.

#### ModeMenuMain
Main menu, opens when you click bottom button. If inactive for 120 sec, will automatically go to watchface.
 
 \
 \
## Prototype photos:
 <img src="Photos/photo_2021-12-05_17-01-19.jpg" width="300"/>
 <img src="Photos/photo_2021-12-04_13-20-55.jpg" width="300"/>
 <img src="Photos/photo_2021-12-08_22-34-49.jpg" width="300"/>
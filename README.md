# Arduino Door Logger

Simple script used for logging date and time when the door is opened. (Not just for door. Anything with moving parts will do! example: window, refrigerator or even scanner cover!)

## Requirements

- Arduino compatible board (Arduino UNO R3)
- SD Card module (DFR0071)
- Real Time Clock module (DS3231)
- SD Card
Models I used for this project is in parentheses

## How to use

### 1.Connect all neccessary module to the board

#### Pin for SD module
 - MOSI > 11
 - MISO > 12
 - CLK > 13
 - CS > 4

#### Pin for RTC module
 - VCC > 5V
 - GND > GND
 - SCL > A5
 - SDA > A4
 Note: Sorry, No diagram.

### 2. Plug SD Card in your PC and create `text.txt` file
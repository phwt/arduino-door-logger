# Arduino Door Logger

Simple script used for logging date and time when the door is opened. (Not just for door. Anything with moving parts will do! example: window, refrigerator or even scanner cover!)

## Requirements

- Arduino compatible board (Arduino UNO R3)
- SD Card module (DFR0071)
- Real Time Clock module (DS3231)
- SD Card
Models I used for this project is in parentheses

## How to use

### 1. Connect all neccessary module to the board

Pin A0 for open/close detector. (Connected to the power source be default)

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

### 3. Connect the board to your PC then upload a sketch.
After upload is complete you can unplug it and power it with batteries. (Stay connected if you want to see logs.)

### 4. Insert SD Card in your PC and create `test.txt` file

Just empty simple text file. Then safely eject it.

### 5. Insert SD Card in SD module connected to the board.

### 6. Supply the board with power (Or simply turn the power on)

### 7. Wait for status update

If you see this.
```
Initializing SD card...
Initialization done.
```
It's working just fine!

But if you see this.
```
Initializing SD card...
Initialization failed.
```
You SD card or SD module has a problem. Try replacing SD card.

### 8. Test!

Try disconnecting A0 wire from power source. (Simulate door opening)

You should see this.
```
Writing to test.txt...
done.
```

But again if you see this.
```
error opening test.txt
```
You may not have created `test.txt` yet.

## Known Issue
- Sometime SD Card cannot be initialized. (Hardware issue possibly)

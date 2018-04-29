/*
  Door logger

  Script for logging time of door open/close into SD scard

  Pin number for SD module
  ** MOSI - 11
  ** MISO - 12
  ** CLK - 13
  ** CS - 4
*/
 
#include "Wire.h"
#define DS3231_I2C_ADDRESS 0x68
#include <SPI.h>
#include <SD.h>
int chk = 0;

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val){
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val){
  return( (val/16*10) + (val%16) );
}

File myFile;

void readDS3231time(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year){
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}

void setup() {
  // Open serial communications and wait for port to open:
  Wire.begin();
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("Initialization failed!");
    return;
  }
  Serial.println("Initialization done.");

int now;

void displayTime(){
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);
  //int now = hour + minute + second;
  String sc = ":";
  String sl = "/";
  String sp = " ";
  String ss = dayOfMonth + sl + month + sl + year + sp + hour + sc + minute + sc + second;
  //Example Output - 22/10/2017 22:35:17 Opened
  String sh = ss + sp + "Opened";
  //Serial.print(sh);
  myFile = SD.open("test.txt", FILE_WRITE);
  Serial.print("Writing to test.txt...");
  myFile.println(sh);
  // close the file:
  myFile.close();
  Serial.println("done.");
}

void loop() {
    // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  //Serial.println(voltage);

  if (voltage < 4 && chk == 0){
      chk = 1;
      myFile = SD.open("test.txt", FILE_WRITE);
    
      // if the file opened okay, write to it:
      if (myFile) {
        displayTime();
        delay(5000);
        chk = 0;
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
        chk = 0;
      }
    
      // re-open the file for reading:
      myFile = SD.open("test.txt");
      if (myFile) {
        Serial.println("test.txt:");
    
        // read from the file until there's nothing else in it:
        while (myFile.available()) {
          Serial.write(myFile.read());
        }
        // close the file:
        myFile.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
      }
  } else{
   //ss 
   }
}

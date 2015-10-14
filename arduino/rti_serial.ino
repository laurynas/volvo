#include <SoftwareSerial.h>

const byte rxPin = 3;
const byte txPin = 4;

enum display_mode_name {RTI_RGB, RTI_PAL, RTI_NTSC, RTI_OFF};
const char display_modes[] = {0x40, 0x45, 0x4C, 0x46};
const char brightness_levels[] = {0x20, 0x61, 0x62, 0x23, 0x64, 0x25, 0x26, 0x67, 0x68, 0x29, 0x2A, 0x2C, 0x6B, 0x6D, 0x6E, 0x2F};

int current_display_mode = RTI_RGB;
bool send_brightness = true;
char current_brightness_level = 15;

//delay between bytes, ms
const int rti_delay = 100;

// set up a new serial object
SoftwareSerial rtiSerial(rxPin, txPin, true);

void setup() {
  rtiSerial.begin(2400);
}

void loop() {
  rtiWrite(display_modes[current_display_mode]);
  
  if (send_brightness)
    rtiWrite(brightness_levels[current_brightness_level]);
  else
    rtiWrite(0x40);
    
  rtiWrite(0x83);
}

void rtiWrite(char byte) {
  rtiSerial.print(byte);
  delay(rti_delay);
}


// Code based on https://github.com/festlv/screen-control/blob/master/Screen_control/

const uint8_t RTI_SERIAL_TX = 4;
enum display_mode_name {RTI_RGB, RTI_PAL, RTI_NTSC, RTI_OFF};
const char display_modes[] = {0x40, 0x45, 0x4C, 0x46};
const char brightness_levels[] = {0x20, 0x61, 0x62, 0x23, 0x64, 0x25, 0x26, 0x67, 0x68, 0x29, 0x2A, 0x2C, 0x6B, 0x6D, 0x6E, 0x2F};

extern int current_display_mode;
extern char current_brightness_level;
extern bool send_brightness;

//delay between bytes, ms
const int rti_delay = 100;

void setup() {
  // put your setup code here, to run once:
  rti_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  rti_loop();
}

int current_display_mode = RTI_RGB;
bool send_brightness = true;
char current_brightness_level = 15;

const int rti_bit_delay = 410;

void rti_setup() {
  pinMode(RTI_SERIAL_TX, OUTPUT);
}

inline void rti_tx_bit_delay() {
  unsigned long wait = micros()+rti_bit_delay;
  while (wait>micros()) {};
}

void rti_loop() {
  rti_bitbang_tx(display_modes[current_display_mode]);
  delay(rti_delay);
  
  if (send_brightness)
    rti_bitbang_tx(brightness_levels[current_brightness_level]);
  else
    rti_bitbang_tx(0x40);
  
  delay(rti_delay);
  
  rti_bitbang_tx(0x83);
  delay(rti_delay); 
}

void rti_set_brightness(char level) {
  if (level>0 && level<16) {
    current_brightness_level = level;
    send_brightness = true;
  }
}

void rti_disable_screen() {
  current_display_mode = RTI_OFF;
}

void rti_enable_screen() {
  current_display_mode = RTI_PAL;
}

void rti_bitbang_tx(char byte_to_tx) {
  digitalWrite(RTI_SERIAL_TX, LOW);
  rti_tx_bit_delay();

  for (byte mask = 0x01; mask; mask <<= 1)
    {
      if (byte_to_tx & mask) // choose bit
        digitalWrite(RTI_SERIAL_TX, HIGH); // send 1
      else
        digitalWrite(RTI_SERIAL_TX, LOW); // send 0
    
      rti_tx_bit_delay();
    }
    digitalWrite(RTI_SERIAL_TX, HIGH); // restore pin to natural state
    rti_tx_bit_delay();
}

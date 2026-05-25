/*
   Wiegand26_HID.ino
   CH552G - 26-bit Wiegand Reader -> USB HID Keyboard Emulator

   REQUIRED Arduino IDE settings:
     Board:        CH552
     Clock:        24 MHz
     USB Settings: USER CODE w/ 148B USB ram   <-- critical!
     Upload:       USB

   Wiring:
     P3.1 (pin 7  on chip) -> Wiegand DATA1 (white wire)
     P3.0 (pin 8  on chip) -> Wiegand DATA0 (green wire)
     GND                   -> Reader GND
     Power reader from separate 5V/12V supply

   Output: 6 uppercase hex chars (24-bit payload, parity stripped) + Enter
   Example: FC=77, CN=26983 -> 4D6967
*/

#ifndef USER_USB_RAM
#error "Set USB Settings to: USER CODE w/ 148B USB ram"
#endif

#include "src/userUsbHidKeyboard/USBHIDKeyboard.h"

#define D0_HIGH()  ((P3 >> 0) & 1)   // P3.0 = DATA0
#define D1_HIGH()  ((P3 >> 1) & 1)   // P3.1 = DATA1

#define WIEGAND_BITS        26
#define WIEGAND_TIMEOUT_MS  200

__xdata uint32_t wRaw    = 0;
__xdata uint8_t  wCount  = 0;
__xdata uint32_t wLastMs = 0;

const char hexChars[] = "0123456789ABCDEF";

void typeChar(char c) {
  Keyboard_press(c);
  Keyboard_release(c);
}

void typeHex8(uint8_t v) {
  typeChar(hexChars[(v >> 4) & 0xF]);
  typeChar(hexChars[ v       & 0xF]);
}

void typeHex24(uint32_t v) {
  typeHex8((v >> 16) & 0xFF);
  typeHex8((v >>  8) & 0xFF);
  typeHex8( v        & 0xFF);
}

void setup() {
  USBInit();
  pinMode(30, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);
  delay(2000);
}

void loop() {
  static uint8_t prevD0 = 1;
  static uint8_t prevD1 = 1;

  uint8_t d0 = D0_HIGH();
  uint8_t d1 = D1_HIGH();

  if (prevD0 == 1 && d0 == 0) {
    if (wCount < WIEGAND_BITS) {
      wRaw = (wRaw << 1);
      wCount++;
      wLastMs = millis();
    }
  } else if (prevD1 == 1 && d1 == 0) {
    if (wCount < WIEGAND_BITS) {
      wRaw = (wRaw << 1) | 1;
      wCount++;
      wLastMs = millis();
    }
  }

  prevD0 = d0;
  prevD1 = d1;

  if (wCount > 0 && (millis() - wLastMs) >= WIEGAND_TIMEOUT_MS) {

    uint8_t  count = wCount;
    uint32_t raw   = wRaw;

    wRaw   = 0;
    wCount = 0;

    if (count == WIEGAND_BITS) {
      // Strip bit 25 (even parity) and bit 0 (odd parity), shift down by 1
      uint32_t payload = (raw >> 1) & 0xFFFFFF;
      typeHex24(payload);
    }

    Keyboard_press(KEY_RETURN);
    Keyboard_release(KEY_RETURN);
  }
}

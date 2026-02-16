/* TLC591 demo - 2 devices

make sure to include this in platformio.ini:
lib_deps =
  https://github.com/DanBarry00/TLC5916
*/

#include <Arduino.h>
#include "tlc5916.h"

// ================= SETUP =================

uint8_t shiftRegister[2]; // 2 devices in chain, 8 bits each = 16 total outputs

void setup() {  
  // Initialize TLC5916 library (configures pins)
  initTLC5916(2);

  // Set all LEDs on
  shiftRegister[0] = 0xFF;
  shiftRegister[1] = 0xFF;
  updateShiftRegisters(shiftRegister, 2);
}

// ================= MAIN LOOP =================

int t = 2000; // for testing timing

void loop() {
  shiftRegister[0] = 0xFF;
  shiftRegister[1] = 0xFF;
  updateShiftRegisters(shiftRegister, 2); // all on
  delay(t);
  shiftRegister[0] = 0x00;
  shiftRegister[1] = 0x00;
  updateShiftRegisters(shiftRegister, 2); // all off
  delay(t);
}
  



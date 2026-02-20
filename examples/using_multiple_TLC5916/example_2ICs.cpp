// TLC591 demo - 2 devices


#include <Arduino.h>
#include "tlc5916.h"

// ================= PIN DEFINITIONS =================
#define PIN_SDI 6  // Shift register serial data
#define PIN_CLK 5  // Shift clock
#define PIN_LATCH 4  // Latch clock
#define PIN_OE 3 // Output enable (active low)

#define NUM_DEVICES 2

// ================= HELPER FUNCTIONS =================
void flipBit(uint8_t *byte, uint8_t bit) {
  *byte ^= (1 << bit);
}

void setBit(uint8_t *byte, uint8_t bit, bool value) {
  if (value) {
    *byte |= (1 << bit);
  } else {
    *byte &= ~(1 << bit);
  }
}

// ================= SETUP =================

uint8_t shiftRegister[2]; // 2 devices in chain, 8 bits each = 16 total outputs

void setup() {  
  // Initialize TLC5916 library (configures pins)
  initTLC5916(PIN_SDI, PIN_CLK, PIN_LATCH, PIN_OE, NUM_DEVICES);

  // Set all LEDs off
  shiftRegister[0] = 0x00;
  shiftRegister[1] = 0x00;
  update_TLC5916(shiftRegister);
}

// ================= MAIN LOOP =================

void loop() {
  for (uint8_t byte = 0; byte < NUM_DEVICES ; byte++) {
    for (uint8_t bit = 0; bit < 8; bit++) {
      //turn on bit 
      setBit(&shiftRegister[byte], bit, true);
      update_TLC5916(shiftRegister);

      //turn off bit after delay
      delay(50);
      setBit(&shiftRegister[byte], bit, false);
      update_TLC5916(shiftRegister);
    }
  }
 
}
  
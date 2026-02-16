#include "tlc5916.h"

// ================= INITIALIZATION =================

bool initTLC5916(uint8_t numDevices) {
  // Configure pins as outputs
  pinMode(PIN_SDI, OUTPUT);
  pinMode(PIN_CLK, OUTPUT);
  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_OE, OUTPUT);

  // Initialize pins to safe state
  digitalWrite(PIN_LATCH, LOW);
  digitalWrite(PIN_OE, LOW);    // Enable outputs
  digitalWrite(PIN_CLK, LOW);
  digitalWrite(PIN_SDI, LOW);

  return true;
}

// ================= LOW-LEVEL SHIFT REGISTER CODE =================

void updateShiftRegisters(const uint8_t *data, uint8_t numDevices) {
  // Shift out data for all devices
  for (int dev = 0; dev < numDevices; dev++) {
    uint8_t value = data[dev];

    for (int bit = 0; bit < 8; bit++) {
      digitalWrite(PIN_CLK, LOW);

      if (value & 0x80) {
        digitalWrite(PIN_SDI, HIGH);
      } else {
        digitalWrite(PIN_SDI, LOW);
      }

      digitalWrite(PIN_CLK, HIGH);
      value <<= 1;
    }
  }

  // Latch all outputs simultaneously
  digitalWrite(PIN_LATCH, HIGH);
  digitalWrite(PIN_LATCH, LOW);
}
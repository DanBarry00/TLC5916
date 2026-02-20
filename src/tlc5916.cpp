#include "tlc5916.h"

// ================= INITIALIZATION =================

bool initTLC5916(uint8_t sdi_pin, uint8_t clk_pin, uint8_t latch_pin, uint8_t oe_pin, uint8_t numDevices) {
  // Configure pins as outputs
  pinMode(sdi_pin, OUTPUT);
  pinMode(clk_pin, OUTPUT);
  pinMode(latch_pin, OUTPUT);
  pinMode(oe_pin, OUTPUT);

  // Initialize pins to safe state
  digitalWrite(latch_pin, LOW);
  digitalWrite(oe_pin, LOW);    // Enable outputs
  digitalWrite(clk_pin, LOW);
  digitalWrite(sdi_pin, LOW);

  numberOfDevices = numDevices;
  return true;
}

// ================= LOW-LEVEL SHIFT REGISTER CODE =================

void update_TLC5916(const uint8_t *data) {
  // Shift out data for all devices
  for (int i = 0; i < numberOfDevices; i++) {
    uint8_t value = data[i];

    for (int bit = 0; bit < 8; bit++) {
      digitalWrite(clk_pin, LOW);

      if (value & 0x80) {
        digitalWrite(sdi_pin, HIGH);
      } else {
        digitalWrite(sdi_pin, LOW);
      }

      digitalWrite(clk_pin, HIGH);
      value <<= 1;
    }
  }

  // Latch outputs 
  digitalWrite(latch_pin, HIGH);
  digitalWrite(latch_pin, LOW);
}

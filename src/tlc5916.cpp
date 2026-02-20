#include "tlc5916.h"

// ================= INITIALIZATION =================

bool initTLC5916(uint8_t sdi_pin, uint8_t clk_pin, uint8_t latch_pin, uint8_t oe_pin, uint8_t numDevices) {
  // Validate number of devices
  if (numDevices == 0 || numDevices > 254) {
    return false; // Invalid number of devices
  }

  // Store pin configuration in global struct
  tlc5916_config.sdi_pin = sdi_pin;
  tlc5916_config.clk_pin = clk_pin;
  tlc5916_config.latch_pin = latch_pin;
  tlc5916_config.oe_pin = oe_pin;
  tlc5916_config.numDevices = numDevices;

  // Configure pins as outputs
  pinMode(tlc5916_config.sdi_pin, OUTPUT);
  pinMode(tlc5916_config.clk_pin, OUTPUT);
  pinMode(tlc5916_config.latch_pin, OUTPUT);
  pinMode(tlc5916_config.oe_pin, OUTPUT);

  // Initialize pins to safe state
  digitalWrite(tlc5916_config.latch_pin, LOW);
  digitalWrite(tlc5916_config.oe_pin, LOW);    // Enable outputs
  digitalWrite(tlc5916_config.clk_pin, LOW);
  digitalWrite(tlc5916_config.sdi_pin, LOW);

  return true;
}

// ================= LOW-LEVEL SHIFT REGISTER CODE =================

void update_TLC5916(const uint8_t *data) {
  // Shift out data for all devices
  for (int i = 0; i < tlc5916_config.numDevices; i++) {
    uint8_t value = data[i];

    for (int bit = 0; bit < 8; bit++) {
      digitalWrite(tlc5916_config.clk_pin, LOW);

      if (value & 0x80) {
        digitalWrite(tlc5916_config.sdi_pin, HIGH);
      } else {
        digitalWrite(tlc5916_config.sdi_pin, LOW);
      }

      digitalWrite(tlc5916_config.clk_pin, HIGH);
      value <<= 1;
    }
  }

  // Latch outputs 
  digitalWrite(tlc5916_config.latch_pin, HIGH);
  digitalWrite(tlc5916_config.latch_pin, LOW);
}

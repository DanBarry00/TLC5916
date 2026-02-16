#ifndef TLC5916_H
#define TLC5916_H

#include <Arduino.h>
#include <stdint.h>

// ================= PIN DEFINITIONS =================
static const int PIN_SDI   = 6;  // Shift register serial data
static const int PIN_CLK   = 5;  // Shift clock
static const int PIN_LATCH = 4;  // Latch clock
static const int PIN_OE    = 3;  // Output enable (active low)

// ================= FUNCTION DECLARATIONS =================

/**
 * Initialize TLC5916 library (configures pins)
 * @param numDevices Number of TLC5916 devices in the chain
 * @return true if initialization successful
 */
bool initTLC5916(uint8_t numDevices);

/**
 * Update shift registers with data for multiple TLC5916 devices
 * @param data Pointer to array of uint8_t values (one byte per device)
 * @param numDevices Number of devices in the chain
 */
void updateShiftRegisters(const uint8_t *data, uint8_t numDevices);

#endif
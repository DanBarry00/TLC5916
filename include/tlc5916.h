#ifndef TLC5916_H
#define TLC5916_H

#include <Arduino.h>
#include <stdint.h>


typedef struct {
    uint8_t sdi_pin;
    uint8_t clk_pin;
    uint8_t latch_pin;
    uint8_t oe_pin;
    uint8_t numDevices;
} TLC5916

TLC5916 tlc5916;

// ================= FUNCTION DECLARATIONS =================

/**
 * Initialize TLC5916 library (configures pins)
 * @param sdi_pin Pin number for shift register serial data (SDI)
 * @param clk_pin Pin number for shift clock (CLK)
 * @param latch_pin Pin number for latch clock (LATCH)
 * @param oe_pin Pin number for output enable (OE, active low)
 * @param numDevices Number of TLC5916 devices in the chain (1-254)
 * @return true if initialization successful
 */
bool initTLC5916(uint8_t sdi_pin, uint8_t clk_pin, uint8_t latch_pin, uint8_t oe_pin, uint8_t numDevices);

/**
 * Update shift registers with data for multiple TLC5916 devices
 * @param data Pointer to array of uint8_t values (one byte per device)
 * @param numDevices Number of devices in the chain
 */
void update_TLC5916(const uint8_t *data);



#endif

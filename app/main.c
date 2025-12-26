#include <stdint.h>
#include "platform.h"

/*
  Renesas S7G2 PORT registers:
    PCNTR1: pin direction control (and some mode bits)
    PCNTR3: output data register with "set/reset" halves:
      - lower 16 bits: set bits
      - upper 16 bits: clear bits (bit n in upper clears pin n)
*/

#define PORT_BASE         (0x40040000UL)
#define PORT_STRIDE       (0x20UL)
#define PORTx_PCNTR1(x)   (PORT_BASE + (x) * PORT_STRIDE + 0x00UL)
#define PORTx_PCNTR3(x)   (PORT_BASE + (x) * PORT_STRIDE + 0x08UL)

static inline void mmio_write(uint32_t addr, uint32_t v) {
  *(volatile uint32_t*)addr = v;
}
static inline uint32_t mmio_read(uint32_t addr) {
  return *(volatile uint32_t*)addr;
}

static void p8_pins_output_init(void) {
  volatile uint32_t *PCNTR1 = (volatile uint32_t*)PORTx_PCNTR1(8);
  uint32_t val = *PCNTR1;

  // Configure P8_7..P8_10 as outputs:
  // This matches the "known working" snippet you used.
  val |=    (1u<<10) | (1u<<9) | (1u<<8) | (1u<<7);
  val &= ~(((1u<<10) | (1u<<9) | (1u<<8) | (1u<<7)) << 16);
  *PCNTR1 = val;
}

static void p8_write_mask(uint32_t set_mask, uint32_t clr_mask) {
  volatile uint32_t *PCNTR3 = (volatile uint32_t*)PORTx_PCNTR3(8);
  // upper 16 clears, lower 16 sets
  *PCNTR3 = (clr_mask << 16) | (set_mask & 0xFFFFu);
}

int main(void) {
  bringup_run();
  p8_pins_output_init();

  while (1) {
    // Pattern A:
    // set P8_8 + P8_10, clear P8_7 + P8_9
    p8_write_mask((1u<<8) | (1u<<10), (1u<<7) | (1u<<9));
    delay_cycles(300000);

    // Pattern B:
    // set P8_7 + P8_9, clear P8_8 + P8_10
    p8_write_mask((1u<<7) | (1u<<9), (1u<<8) | (1u<<10));
    delay_cycles(300000);
  }
}

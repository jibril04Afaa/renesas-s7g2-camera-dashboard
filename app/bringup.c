#include <stdint.h>
#include "platform.h"

void delay_cycles(uint32_t cycles) {
  while (cycles--) {
    __asm volatile ("nop; nop; nop; nop");
  }
}

void bringup_run(void) {
  // Later: clocks, pinmux, peripherals
}

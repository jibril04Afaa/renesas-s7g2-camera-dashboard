#include <stdint.h>

static void noop(void) {
  while (1) { }
}

void reset(void);                 // defined in reset.c
extern unsigned long _stack_top;  // from linker script

__attribute__((section(".vector_table")))
void (*const vector_table[16 + 96])(void) = {
  (void (*)(void))(&_stack_top),  // Initial stack pointer
  reset,                          // Reset
  noop,                           // NMI
  noop,                           // HardFault
  noop,                           // MemManage
  noop,                           // BusFault
  noop,                           // UsageFault
  0, 0, 0, 0,                     // Reserved
  noop,                           // SVCall
  noop,                           // DebugMon
  0,                              // Reserved
  noop,                           // PendSV
  noop,                           // SysTick
  [16 ... (16 + 96 - 1)] = noop
};

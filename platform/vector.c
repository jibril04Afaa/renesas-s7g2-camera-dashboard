#include <stdint.h>


/* Interrupt handling */

extern uint32_t _stack_top;
extern void Reset_Handler(void);
extern void Default_Handler(void);

__attribute__((section(".vectors")))
void (* const vector_table[])(void) = {
  (void (*)(void))(&_stack_top), // initial Stack Pointer
  Reset_Handler, // reset
  Default_Handler, // NMI
  Default_Handler, // HardFault
};
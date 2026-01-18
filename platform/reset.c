#include <stdint.h>

extern uint32_t _sidata, _sdata, _edata;
extern uint32_t _sbss, _ebss;

void Reset_Handler(void)
{
  uint32_t *src = &_sidata;
  uint32_t *dst = &_sdata;

  // copy .data from flash to RAM
  while (dst < &_edata) *dst++ = *src++;

  // zero .bss
  dst = &_sbss;
  while (dst < &_ebss) *dst++ = 0;

  main();

  while (1);

}
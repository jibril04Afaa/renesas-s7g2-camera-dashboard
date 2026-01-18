#include <stdint.h>

extern uint32_t _end_text;
extern uint32_t _start_data, _end_data;
extern uint32_t _start_bss, _end_bss;

extern int main();

void Reset_Handler(void)
{
  uint32_t *src = &_end_data;
  uint32_t *dst = &_start_data;

  // copy .data from flash to RAM
  while (dst < &_end_data) *dst++ = *src++;

  // zero .bss
  dst = &_start_bss;
  while (dst < &_end_bss) *dst++ = 0;

  main();

  while (1);

}
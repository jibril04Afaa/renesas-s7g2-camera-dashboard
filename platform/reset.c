#include <stdint.h>

extern uint32_t _end_text;
extern uint32_t _start_data;
extern uint32_t _end_data;
extern uint32_t _start_bss;
extern uint32_t _end_bss;

int main(void);

void reset(void) {
  // Copy .data from flash to RAM
  uint32_t *src = &_end_text;
  uint32_t *dst = &_start_data;
  while (dst < &_end_data) {
    *dst++ = *src++;
  }

  // Zero .bss
  dst = &_start_bss;
  while (dst < &_end_bss) {
    *dst++ = 0;
  }

  (void)main();

  // If main returns, hang.
  while (1) { }
}

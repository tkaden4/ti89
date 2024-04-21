#include "delay.h"

void delay(long long ms)
{
  while (--ms)
  {
    __asm__("nop");
  }
}

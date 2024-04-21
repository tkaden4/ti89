#include <tigcclib.h>
#include "bitutil.h"
#include "defs.h"
#include "ports.h"
#include "delay.h"

int _ti89;

int __main()
{
  link_init();
  ClearScreen();

  char bits[9] = {0};
  // until the user presses a key
  while (!kbhit())
  {
    for (int i = 0; i < 8; ++i)
    {
      bits[i] = '0';
    }

    char data = 0;
    for (int i = 0; i < 8; ++i)
    {
      bool bit = !link_read_bit();
      data = (data & ~(1 << i)) | (bit << i);

      bits[7 - i] = bit ? '1' : '0';
      ClearScreen();
      DrawStr(0, 0, bits, A_NORMAL);
    }

    if (data)
    {
      DrawChar(0, 10, data, A_NORMAL);
      data = 0;
    }
    for (int i = 0; i < 10; ++i)
    {
    }
  }

  link_reset();
}

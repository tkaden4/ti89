#include <tigcclib.h>
#include "bitutil.h"
#include "defs.h"
#include "ports.h"
#include "delay.h"
#include "TILink.h"

int _ti89;

int __main()
{
  link_init();
  ClearScreen();

  ti_bit_link_t tib;
  ti_bit_link_init(&tib, link_full_read, link_full_set);

  ti_link_t ti;
  ti_link_init(&ti, &tib);

  ti_link_read(&ti);

  while (!kbhit())
  {
    if (ti_link_update(&ti))
    {
      u8 b = ti.byte;
      char byteString[9] = {0};
      for (int i = 0; i < 8; ++i)
      {
        byteString[7 - i] = (b & (1 << i)) ? '1' : '0';
      }

      ClearScreen();
      DrawStr(0, 0, byteString, A_NORMAL);
      DrawChar(0, 10, b, A_NORMAL);

      // Start another read
      ti_link_read(&ti);
    }
  }

  link_reset();
}

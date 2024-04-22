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

  ti_bit_link_t ti;
  ti_bit_link_init(&ti, link_full_read, link_full_set);

  short wrapX = 16;
  short wrapY = 10;
  short pos = 0;

  do
  {
    if (!ti.busy)
    {
      ti_bit_link_read_start(&ti);
    }
    if (ti_bit_link_update(&ti))
    {
      bool bit = ti.bit_in;
      short x = pos % wrapX;
      short y = ((pos - pos % wrapX) / wrapX) % wrapY;
      DrawChar(x * 10, y * 10, bit ? '1' : '0', A_NORMAL);
      ++pos;
      if (pos == wrapX * wrapY)
      {
        ClearScreen();
        pos = 0;
      }
    }
  } while (!kbhit());
}

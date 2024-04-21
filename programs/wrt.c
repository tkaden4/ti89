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

  DrawStr(0, 0, "0: 0, 1: 1, ESC: stop", A_NORMAL);

  short c0 = 0;
  short c = 0;
  while ((c0 = ngetchx()) != KEY_ESC)
  {
    if (c0 != c)
    {
      c = c0;
      ClearScreen();
      DrawChar(0, 10, c, A_NORMAL);
    }
    switch (c)
    {
    case '0':
      link_write_bit(0);
      break;
    case '1':
      link_write_bit(1);
      break;
    default:
      break;
    }
  }

  link_reset();
}

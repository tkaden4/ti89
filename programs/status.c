#include <tigcclib.h>
#include "bitutil.h"
#include "defs.h"
#include "ports.h"
#include "delay.h"

int _ti89;

int __main()
{

  ClearScreen();
  link_init();
  // Disable outputs
  link_set(0, 0);

  bool a = 0;
  bool b = 0;

  // until the user presses a key
  while (!kbhit())
  {
    u8 state = link_full_read() & 0b11;
    bool a1 = state & 0b1;
    bool b1 = (state & 0b10) >> 1;

    if (a != a1 || b != b1)
    {
      ClearScreen();
      a = a1;
      b = b1;
    }

    DrawStr(0, 0, "A | B", A_NORMAL);
    char status[6] = "     ";
    status[0] = a ? '1' : '0';
    status[4] = b ? '1' : '0';
    DrawStr(0, 10, status, A_NORMAL);
  }

  link_reset();
}

#include <tigcclib.h>
#include "bitutil.h"
#include "defs.h"
#include "ports.h"

static volatile int _ti89;

int __main()
{

  int period = 10;
  link_ctrl(0b01100000);

  bool state = 0;
  while (!kbhit())
  {
    link_set(state, state);
    for (int j = 0; j < period; ++j)
    {
    }
    state = !state;
  }

  OSLinkReset();
}

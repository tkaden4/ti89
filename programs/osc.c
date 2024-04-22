#include <tigcclib.h>
#include "bitutil.h"
#include "defs.h"
#include "ports.h"
#include "delay.h"

int _ti89;

int __main()
{

  int period = 1000000;
  link_init();

  bool state = 0;
  while (!kbhit())
  {
    link_set(state, state);
    delay(period);
    state = !state;
  }
}

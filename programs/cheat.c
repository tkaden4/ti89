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

  link_reset();
}

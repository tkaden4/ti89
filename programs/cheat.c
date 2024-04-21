#include <tigcclib.h>
#include "bitutil.h"
#include "defs.h"
#include "ports.h"
#include "delay.h"

int _ti89;

/*
Cheating Application

Connect: <0x00> <SSID> <PASS>

User Commands: GetAnswer, SetAnswer

GetAnswer: <0x01> <path>

SetAnswer: <0x02> <path> <answer>

<path>: <byte[]>

<answer>: <type> <value>
        : <0x00> <byte>   // single choice
        : <0x01> <byte[]> // multiple choices
        : <0x02> <byte[]> // long answer

*/

int __main()
{
  link_init();
  ClearScreen();

  link_reset();
}

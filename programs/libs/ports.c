#include <tigcclib.h>
#include "ports.h"

static long long _link_timeout = -1;
static volatile u8 *CTRL_PORT = (u8 *)0x60000C;
static volatile u8 *STATUS_PORT = (u8 *)0x60000D;
static volatile u8 *DATA_PORT = (u8 *)0x60000E;

inline void link_ctrl(u8 ctrl)
{
  *CTRL_PORT = ctrl;
}

inline u8 link_status()
{
  return *STATUS_PORT;
}

inline bool link_read_port(enum PORT port)
{
  return !((*DATA_PORT & (1 << (port + 2))) >> (port + 2));
}

inline void link_write_port(enum PORT port, bool value)
{
  *DATA_PORT = (*DATA_PORT & (~(0b1 << port))) | (value << port);
}

inline void link_set(bool porta, bool portb)
{
  *DATA_PORT = (*DATA_PORT & ~0b11) | (porta << PORTA) | (portb << PORTB);
}

inline void link_get(bool *porta, bool *portb)
{
  *porta = link_read_port(PORTA);
  *portb = link_read_port(PORTB);
}

inline void link_init()
{
  // Disable any interrupts and force manual control
  link_ctrl(0b01100000);
}

inline void link_reset()
{
  OSLinkReset();
}

inline u8 link_full_read()
{
  return 0b11 & ~((*DATA_PORT & (0b11 << 2)) >> 2);
}

bool link_read_bit(void)
{
  u8 link = 0b11;
  bool bit = 0;

  // Wait for one of the lines to go low
  while ((link = link_full_read() & 0b11) == 0b11)
    ;
  // 1: PORTA is high, PORTB must be low
  if (link & 1)
  {
    bit = 1;
    link_set(1, 0);
    while ((link_full_read() & 0b10) == 0x00)
      ;
    link_set(0, 0);
  }
  else
  {
    bit = 0;
    link_set(0, 1);
    while ((link_full_read() & 0b01) == 0x00)
      ;
    link_set(0, 0);
  }
  return bit;
}

u8 link_read_byte(void)
{
  u8 data = 0;

  for (int i = 0; i < 8; i++)
  {
    bool bit = !link_read_bit();
    data = (data & ~(1 << i)) | (bit << i);
  }
}

void link_write_bit(bool bit)
{
  // Make sure bus is open
  link_set(0, 0);

  u8 mask = bit ? 0b10 : 0b01;
  u8 inverseMask = bit ? 0b01 : 0b10;

  // pull send line low
  link_set(bit ? 1 : 0, bit ? 0 : 1);

  // Wait for ack to go low
  while (link_full_read() & inverseMask)
    ;

  // release bus
  link_set(0, 0);

  // Wait for the bus to become open again
  while (!(link_full_read() & inverseMask))
    ;
}

void link_write_byte(u8 data)
{
  for (int bit = 0; bit < 8; bit++)
  {
    link_write_bit(data & 1);
    data >>= 1;
  }
}

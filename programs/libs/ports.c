#include "ports.h"

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
  return (*DATA_PORT & (1 << (port + 2))) >> (port + 2);
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

#pragma once

#include "defs.h"

enum PORT
{
  PORTA = 0,
  PORTB = 1
};

inline void link_ctrl(u8 ctrl);
inline u8 link_status();

inline bool link_read_port(enum PORT port);
inline void link_write_port(enum PORT port, bool value);
inline void link_set(bool porta, bool portb);
inline void link_get(bool *porta, bool *portb);

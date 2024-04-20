#pragma once

#include "defs.h"

extern inline u8 bit_set(u8 number, u8 n);
extern inline u8 bit_clear(u8 number, u8 n);
extern inline u8 bit_toggle(u8 number, u8 n);
extern inline bool bit_check(u8 number, u8 n);
extern inline u8 bit_set_to(u8 number, u8 n, bool x);

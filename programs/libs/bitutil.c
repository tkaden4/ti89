#include "bitutil.h"

inline u8 bit_set(u8 number, u8 n)
{
  return number | ((u8)1 << n);
}

inline u8 bit_clear(u8 number, u8 n)
{
  return number & ~((u8)1 << n);
}

inline u8 bit_toggle(u8 number, u8 n)
{
  return number ^ ((u8)1 << n);
}

inline bool bit_check(u8 number, u8 n)
{
  return (number >> n) & (u8)1;
}

inline u8 bit_set_to(u8 number, u8 n, bool x)
{
  return (number & ~((u8)1 << n)) | ((u8)x << n);
}

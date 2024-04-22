#pragma once

typedef long long time_t;

// BIT PROTOCOL

struct ti_bit_link_s;

typedef void (*ti_state_fp)(struct ti_bit_link_s *);

typedef unsigned char (*ti_link_get_state_f)();
typedef void (*ti_link_set_state_f)(unsigned char);

struct ti_bit_link_s
{
  // Config
  time_t timeout;
  ti_link_get_state_f get_state;
  ti_link_set_state_f set_state;

  // state machine
  ti_state_fp state;
  unsigned char busy;

  // timeout state
  time_t _timeout_timer;

  // write state
  unsigned char bit_out;

  // read state
  unsigned char bit_in;
};

typedef struct ti_bit_link_s ti_bit_link_t;

void ti_bit_link_init(ti_bit_link_t *ti, ti_link_get_state_f get, ti_link_set_state_f set);

void ti_bit_link_write_start(ti_bit_link_t *ti, unsigned char bit);
void ti_bit_link_read_start(ti_bit_link_t *ti);

// returns true when an operation has completed
unsigned char ti_bit_link_update(ti_bit_link_t *ti);

// BYTE PROTOCOL
struct ti_link_s;

typedef void (*ti_link_state_fp)(struct ti_link_s *);

struct ti_link_s
{
  ti_bit_link_t *bit_link;
  int busy;
  int bit;
  unsigned char byte;
  ti_link_state_fp state;
};

typedef struct ti_link_s ti_link_t;

void ti_link_init(ti_link_t *ti, ti_bit_link_t *bit_link);

void ti_link_read(ti_link_t *ti);
void ti_link_write(ti_link_t *ti, unsigned char byte);

int ti_link_update(ti_link_t *ti);

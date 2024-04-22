#include "TILink.h"

void _link_idle(ti_bit_link_t *link)
{
  link->busy = 0;
  link->_timeout_timer = 0;
}

void ti_bit_link_init(ti_bit_link_t *ti, ti_link_get_state_f get, ti_link_set_state_f set)
{
  ti->timeout = -1;
  ti->_timeout_timer = 0;

  ti->bit_in = 0;
  ti->bit_out = 0;
  ti->busy = 0;
  ti->get_state = get;
  ti->set_state = set;
}

unsigned char ti_bit_link_update(ti_bit_link_t *ti)
{
  ti->state(ti);
  return !ti->busy;
}

// WRITE LOGIC

void _link_write_wait_line_open(ti_bit_link_t *link)
{
  if (link->get_state() != 0b11)
  {
    return;
  }
  // go back to idle state
  link->state = _link_idle;
}

void _link_write_wait_ack(ti_bit_link_t *link)
{
  unsigned char inverseMask = link->bit_out ? 0b01 : 0b10;

  // wait for ack to go low
  if (link->get_state() & inverseMask)
  {
    return;
  }

  // release bus
  link->set_state(0b00);

  // wait for bus to open again
  link->state = _link_write_wait_line_open;
}

void _link_write_start(ti_bit_link_t *link)
{
  // pull send line low
  link->set_state(link->bit_out ? 0b10 : 0b01);

  link->state = _link_write_wait_ack;
}

void ti_bit_link_write_start(ti_bit_link_t *ti, unsigned char bit)
{
  ti->bit_out = bit;
  ti->busy = 1;
  ti->_timeout_timer = 0;

  ti->state = _link_write_start;
}

// READ LOGIC

void _link_read_wait_ack(ti_bit_link_t *ti)
{

  unsigned char mask = ti->bit_in ? 0b10 : 0b01;

  // Wait for the original line to go back high
  if ((ti->get_state() & mask) == 0)
  {
    return;
  }

  // Reset the line
  ti->set_state(0b00);
  ti->state = _link_idle;
}

void _link_read_start(ti_bit_link_t *ti)
{
  unsigned char link = 0b11;
  unsigned char bit = 0;

  // wait for one of the lines to go low
  if ((link = ti->get_state() & 0b11) == 0b11)
  {
    return;
  }

  bit = link & 1 ? 1 : 0;

  ti->bit_in = bit;
  // Set the other line low
  ti->set_state(bit ? 0b01 : 0b10);
  ti->state = _link_read_wait_ack;
}

void ti_bit_link_read_start(ti_bit_link_t *ti)
{
  ti->bit_in = 0;
  ti->busy = 1;
  ti->_timeout_timer = 0;

  ti->state = _link_read_start;
}

// Byte Reading logic

void _ti_link_idle(ti_link_t *ti)
{
  ti->busy = 0;
}

void ti_link_init(ti_link_t *ti, ti_bit_link_t *bit_link)
{
  ti->bit_link = bit_link;
  ti->bit = 0;
  ti->busy = 0;
  ti->byte = 0;
  ti->state = _ti_link_idle;
}

int ti_link_update(ti_link_t *ti)
{
  ti->state(ti);
  return !ti->busy;
}

// Read logic

void _ti_link_read_bit(ti_link_t *ti)
{
  // wait for bit to be received
  if (!ti_bit_link_update(ti->bit_link))
  {
    return;
  }

  // shift in the received bit
  ti->byte = (ti->byte) | (ti->bit_link->bit_in << ti->bit);
  // move to next bit
  ti->bit++;
  // if there are more bits to go, restart the process
  if (ti->bit < 8)
  {
    ti_bit_link_read_start(ti->bit_link);
  }
  // if we shifted in the last bit, go to idle state
  else
  {
    ti->state = _ti_link_idle;
  }
}

void ti_link_read(ti_link_t *ti)
{
  ti->busy = 1;
  ti->bit = 0;
  ti->byte = 0;

  ti_bit_link_read_start(ti->bit_link);
  ti->state = _ti_link_read_bit;
}

// Write logic

void _ti_link_write_bit(ti_link_t *ti)
{
  // wait for bit to be written
  if (!ti_bit_link_update(ti->bit_link))
  {
    return;
  }

  // shift out the written bit
  ti->byte >>= 1;
  // move to next bit
  ti->bit++;
  // if there are more bits to go, restart the process
  if (ti->bit < 8)
  {
    ti_bit_link_write_start(ti->bit_link, ti->byte & 0b1);
  }
  // if we shifted out the last bit, go to idle state
  else
  {
    ti->state = _ti_link_idle;
  }
}

void ti_link_write(ti_link_t *ti, unsigned char byte)
{
  ti->busy = 1;
  ti->bit = 0;
  ti->byte = byte;

  ti_bit_link_write_start(ti->bit_link, ti->byte & 0b1);
  ti->state = _ti_link_write_bit;
}

#include <Wire.h>
#include <TILink.h>


constexpr int PORTA_PIN = D2;
constexpr int PORTA_READ_PIN = D6;
constexpr int PORTB_PIN = D1;
constexpr int PORTB_READ_PIN = D5;

// A 1 means that its not pulled down (actual voltage state)
unsigned char get_state() {
  unsigned char a = digitalRead(PORTA_READ_PIN) == HIGH;
  unsigned char b = digitalRead(PORTB_READ_PIN) == HIGH;
  return a | (b << 1);
}

// A 1 means that its pulled down (corresponding input should be 0)
void set_state(unsigned char state) {
  unsigned char a = state & 0b1 ? LOW : HIGH;
  unsigned char b = (state >> 1) & 0b1 ? LOW : HIGH;

  digitalWrite(PORTB_PIN, b);
  digitalWrite(PORTA_PIN, a);
}

ti_link_t ti;
ti_bit_link_t tib;
bool state = 0;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(PORTA_PIN, OUTPUT_OPEN_DRAIN);
  pinMode(PORTA_READ_PIN, INPUT);

  pinMode(PORTB_PIN, OUTPUT_OPEN_DRAIN);
  pinMode(PORTB_READ_PIN, INPUT);

  ti_bit_link_init(&tib, get_state, set_state);
  ti_link_init(&ti, &tib);

  ti_link_write(&ti, state ? 0x0A : 0xA0);
}


void loop() {
  delay(50);
  digitalWrite(LED_BUILTIN, state);
  if (ti_link_update(&ti)) {
    ti_link_write(&ti, state ? 0x0A : 0xA0);
    state = !state;
  }
}

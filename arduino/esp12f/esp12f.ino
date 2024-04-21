constexpr int PORTA_PIN = D1;
constexpr int PORTB_PIN = D2;

bool receive(int onePin, int zeroPin) {
  pinMode(onePin, INPUT_PULLUP);
  pinMode(zeroPin, INPUT_PULLUP);

  bool one = 0;
  bool zero = 0;
  // Wait for one of the lines to go low
  while((one = digitalRead(onePin)) && (zero = digitalRead(zeroPin)));

  bool data = one ? 0 : 1;
  int recvPin = one ? zeroPin : onePin;
  int ackPin = one ? onePin : zeroPin;

  // Pull ack low
  pinMode(ackPin, OUTPUT_OPEN_DRAIN);
  digitalWrite(ackPin, 0);

  // Wait for recv to go high 
  while(!digitalRead(recvPin));

  // Reset pin and bus state
  pinMode(ackPin, INPUT_PULLUP);
  pinMode(recvPin, INPUT_PULLUP);

  return data;
}

uint8_t link_read() {
  uint8_t data = 0;
  for (int i = 0; i < 8; i++) {
    bool bit = receive(PORTB_PIN, PORTA_PIN);
    data = (data & ~(1 << i)) | (bit << i);
  }
  return data;
}


void transmit(int send, int ack) {
  // Setup pins (write to send, recv from ack)
  pinMode(send, OUTPUT_OPEN_DRAIN);
  pinMode(ack, INPUT_PULLUP);

  // Pull "send" pin low
  digitalWrite(send, 0);

  // Wait for the "ack" pin to go low
  while (digitalRead(ack))
    ;

  // reset the bus (pull ack & send high)
  pinMode(send, INPUT_PULLUP);
  pinMode(ack, INPUT_PULLUP);

  // Wait for the bus to become open again
  while (!digitalRead(ack))
    ;
}

/*
I stole this code from
https://merthsoft.com/linkguide/hardware.html
and modified it a bit
*/
void link_write(char data) {
  for (int bit = 0; bit < 8; bit++) {
    if (data & 1) {
      transmit(PORTB_PIN, PORTA_PIN);
    } else {
      transmit(PORTA_PIN, PORTB_PIN);
    }
    data >>= 1;
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(PORTA_PIN, INPUT_PULLUP);
  pinMode(PORTB_PIN, INPUT_PULLUP);
  delay(2000);
}

void loop() {
  digitalWrite(LED_BUILTIN, receive(PORTB_PIN, PORTA_PIN));
}

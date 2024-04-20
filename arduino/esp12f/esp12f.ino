void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

bool state = HIGH;

void loop() {
  delay(100);
  state = !state;
  digitalWrite(LED_BUILTIN, !state);
}

/*
Blink
Turn on an LED for 1 second, repeatedly.
*/

void setup() {
  pinMode(0, OUTPUT);
}

void loop() {
  digitalWrite(0, HIGH);
  delay(200);
  digitalWrite(0, LOW);
  delay(200);
}

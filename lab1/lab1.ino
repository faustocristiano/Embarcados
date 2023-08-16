int state = 0;


void setup() {
  pinMode(13, OUTPUT);
}
void loop() {
  if (state == 0) {
  state = 1;
  digitalWrite(13, HIGH); // LED on

} else /* state == 1 */ {
  state = 0;
  digitalWrite(13, LOW); // LED off

}
delay(1000);  // wait 1000ms = 1s
}


void setup() {
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);// open serial port to host
}
  
void loop() {
  
  //int v = digitalRead(2);// sense voltage at pin 2
  Serial.println(digitalRead(2));// send voltage to host
  if (digitalRead(2)) {
  digitalWrite(13, HIGH); // LED on

} else {
  digitalWrite(13, LOW); // LED off
  delay(100);  // wait 100ms
  }
}

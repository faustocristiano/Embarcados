volatile byte state = LOW;

void setup(){
  pinMode (2, INPUT);
  pinMode (13, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2),verificaBotao,RISING); 
}

void loop() {
  digitalWrite(13,state);
  delay(100);
}

void verificaBotao(){
  state=!state;
}

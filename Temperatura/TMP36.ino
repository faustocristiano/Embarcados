void setup(){
  Serial.begin(9600);
}

float Tmap(int d) {
  float v = 5. * d / 1024.;
  if (v < 0.1)
    return -40.;
  else if (v <= 1.75)
    return 100. * v - 50.;
  else
    return 125.;
}
void loop() {
  int temp = analogRead(A0);
  Serial.print("Temp: ");
  Serial.println(Tmap(temp));
  
  delay(1000);
}
  

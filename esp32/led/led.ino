/************************************************
 * RoboCore - Blink IoT DevKit
 *
 * Codigo que faz o LED interno da ESP32
 * piscar com intervalos de 1 segundo
 ***********************************************/

//Declaracao da variavel do pino do LED
const int LED_ESP32 = 2;

void setup() {

  //Declaracao do pino como saida
  pinMode(LED_ESP32, OUTPUT);
  
}

void loop() {

  //Acende o LED durante 1 segundo
  digitalWrite(LED_ESP32, HIGH);
  delay(1000);

  //Apaga o LED durante 1 segundo
  digitalWrite(LED_ESP32, LOW);
  delay(1000);
  
}
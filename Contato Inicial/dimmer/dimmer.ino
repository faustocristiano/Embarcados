const int pinoPOT = A0; //pino analógico utilizado pelo potenciômetro
const int pinoLED = 10; //pino digital utilizado pelo led
float luminosidadeLED = 0; //variável que armazena o valor da luminosidade do led

#define minPot 0
#define maxPotLed 255
#define maxPotPotenc 1023
#define resPoten 10000
#define Vcc 5

  
void setup(){
  pinMode(pinoPOT, INPUT); //define o pino do potenciômetro como entrada
  pinMode(pinoLED, OUTPUT); //define o pino do led como saída
  Serial.begin(9600);

}
  
void loop(){

  luminosidadeLED = map(analogRead(pinoPOT), minPot, maxPotPotenc, minPot, maxPotLed);  //executa a função "map" de acordo com os parâmetros passados
  
  float valor=analogRead(pinoPOT);
  
  Serial.println((valor/maxPotPotenc)*Vcc);
  
  analogWrite(pinoLED, luminosidadeLED);  //aplica ao led o valor de luminosidade gerado pela função "map"

  delay(1000);

}

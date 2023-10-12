/************************************************
* RoboCore - IoT DevKit - LoRaWAN   
*
* Aprendendo a utilizar o sensor de temperatura e
* umidade do kit, em conjunto com o sensor de 
* luminosidade e botao.
***********************************************/

//Inclusao da bilbioteca do sensor DHT11 
#include "DHT.h"

//Declaracao das variaveis dos pinos dos sensores e botao
const int pinoDHT = 12;
const int pinoBotao = 4;
const int pinoLDR = 15;

//Declaracao das variaveis que receberao a leitura do botao e sensor de luz
int estadoBotao = 0;
int valorLDR = 0;

//Criacao da instancia DHT, em funcao do pino do sensor e do tipo do DHT
DHT dht(pinoDHT, DHT11);

void setup() {
  //Abrimos uma comunicacao serial para imprimir dados no Monitor Serial
  Serial.begin(115200);
  
  //Inicializamos nosso sensor DHT11
  dht.begin();
      
  //Informamos que o pino do botao atuara como entrada
  pinMode(pinoBotao, INPUT);
}

void loop() {

  //Assimilamos a variavel estadoBotao a leitura digital do pino do botao    
  estadoBotao = digitalRead(pinoBotao);

  //Se o botao estiver pressionado, entramos nesta rotina condicional
  if (estadoBotao == LOW) {
    delay(30);
    estadoBotao = digitalRead(pinoBotao);
	
   	//Criamos duas variaveis locais para armazenar a temperatura e a umidade lidas
    float temperatura = dht.readTemperature();
    float umidade = dht.readHumidity();
	
    //Mostramos no Monitor Serial os valores de temperatura e umidade
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.print(" *C - Umidade: ");
    Serial.print(umidade);
    Serial.print(" % - Luminosidade: ");
	
    //Lemos entao o sensor LDR e mapeamos seu valor de 0 a 100 %
    valorLDR = analogRead(pinoLDR);
    valorLDR = map(valorLDR, 4095, 2500, 0, 100);
	
    //Finalizamos a linha impressa no Monitor Serial com a luminosidade em % 
    Serial.print(valorLDR);
    Serial.println(" %");

    while (digitalRead(pinoBotao) == LOW) {
      //Esperamos soltar o botao para nao haver duas leituras
    }
  }
}
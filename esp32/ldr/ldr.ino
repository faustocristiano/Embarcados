/************************************************
* RoboCore - IoT DevKit - LoRaWAN   
*
* Aprendendo a utilizar o sensor de luminosidade LDR do kit
***********************************************/

//Declaracao da variavel do pino do sensor LDR 
const int pinoLDR = 15;

//Declaracao da variavel que recebera a leitura dos valores do sensor
int valorLDR = 0;

void setup() {
  //Iniciamos uma comunicacao serial para fazermos as leituras no Monitor Serial
  Serial.begin(115200);
}

void loop() {
  //Assimilamos a variavel valorLDR ao que eh lido de forma analogica no pino do LDR
  valorLDR = analogRead(pinoLDR);
  
  //Atraves dessa leitura, chegamos as seguintes conclusoes:
  //Quanto maior a luminosidade, mais proximo de 0 temos a variavel valorLDR 
  //Quanto menor a luminosidade, mais proximo de 4096 temos a variavel valorLDR
	
  //Mapeamos o valor do LDR para, ao inves de mostrar valor de 4095 a 0, mostrar valores de 0 a 100%    
  valorLDR = map(valorLDR, 4095, 2500, 0, 100);
  
  //Finalmente imprimimos no Monitor Serial o valor do LDR convertido em porcentagem
  Serial.print(valorLDR);
  Serial.println(" ");
  delay(250);
}
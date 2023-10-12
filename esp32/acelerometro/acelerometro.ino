/************************************************
* RoboCore - IoT DevKit - LoRaWAN   
*
* Aprendendo a utilizar o sensor acelerometro
* do IoT DevKit
***********************************************/

//Declaracao da biblioteca do sensor acelerometro 
#include "RoboCore_MMA8452Q.h"

//Criamos a instancia que nos ajudara a fazer as leituras
MMA8452Q acel;

void setup() {
  
  //Iniciamos uma comunicacao serial para exibir os valores no Monitor Serial
  Serial.begin(115200);
      
  //Inicializamos o acelerometro com uma funcao interna da biblioteca
  acel.init();

}

void loop() {
  
  //Com um unico comando fazemos a leitura do acelerometro e a partir dai ja temos as componentes X, Y e Z de uma forma simples para analise
  acel.read();

  //Se houver movimento no dispositivo, imprimimos no Monitor Serial uma mensagem
  if((acel.x > 0.40) || (acel.y > 0.40) || (acel.z < 0.80)){
    Serial.println("ALERTA! MOVIMENTO DETECTADO");
  }
  
}
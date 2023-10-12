/*******************************************************************************
* IoT DevKit - Envio de Mensagens pelo LoRaWAN Bee (v1.0)
* 
* Codigo usado para enviar as leituras do LDR do IoT DevKit atraves de mensagens
* LoRaWAN. As leituras do sensor sao convertidas para mensagens JSON, e entao 
* enviadas por texto para a plataforma PROIoT.
* 
* Copyright 2020 RoboCore.
* Escrito por Giovanni de Castro (25/08/2020).
* Creditos: @francois - RoboCore
* 
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version (<https://www.gnu.org/licenses/>).
*******************************************************************************/

//Verifica se o modelo de placa selecionado esta correto
#if !defined(ARDUINO_ESP32_DEV) // ESP32
#error Use this example with the ESP32
#endif

//Inclusao das bibliotecas
#include <RoboCore_SMW_SX1276M0.h>
#include <HardwareSerial.h>
#include <ArduinoJson.h>
#include "DHT.h"


//Declaracao dos pinos de comunicacao serial do Kit
HardwareSerial LoRaSerial(2);
#define RXD2 16
#define TXD2 17

//Criacao do objeto lorawan para a biblioteca SMW_SX1276M0
SMW_SX1276M0 lorawan(LoRaSerial);

//Declaracao da variavel que armazena as respostas do modulo
CommandResponse resposta;

//Declaracao das variaveis que armazenam as informacoes da rede
const char APPEUI[] = "0000000000000001"; //Application EUI
const char APPKEY[] = "e2a0fd2699095a975ebcb4489fb3d1f2"; //Application Key
//As variaveis acima devem ser alteradas de acordo com os codigos gerados na plataforma PROIoT

//Declaracao da variavel que armazena o "ALIAS" da variavel da PROIoT
const char ALIAS[] = "Luminosidade"; //Altere essa variavel de acordo com o ALIAS configurado na plataforma
const char ALIAS1[] = "Temperatura"; //Altere essa variavel de acordo com o ALIAS configurado na plataforma
const char ALIAS2[] = "Umidade"; //Altere essa variavel de acordo com o ALIAS configurado na plataforma
//Declaracao das variaveis de intervalo de tempo
const unsigned long TEMPO_ESPERA = 5000; //10S minutos
unsigned long intervalo;

//Declaracao das variaveis para o LDR
const int PINO_LDR = 15;
const int pinoDHT = 12;
int leitura_LDR = 0;
float temperatura = 0;
float umidade = 0;

//Criacao da instancia DHT, em funcao do pino do sensor e do tipo do DHT
DHT dht(pinoDHT, DHT11);


//Declaracao da funcao que verifica a conexao do modulo
void event_handler(Event);

//------------------------------------------------------------------------
void setup() {

  //Inicia o monitor serial e imprime o cabecalho
  Serial.begin(115200);
  Serial.println(F("Envio de Luminosidade para a Plataforma PROIoT"));

  //Definicao do pino de reset do modulo
  lorawan.setPinReset(5);
  lorawan.reset(); //Realiza um reset no modulo

  //Inicia a comunicacao serial com o modulo
  LoRaSerial.begin(115200, SERIAL_8N1, RXD2, TXD2);

  //Define o pino conectado ao sensor como uma entrada
  pinMode(PINO_LDR,INPUT);
   //Inicializamos nosso sensor DHT11
  dht.begin();
      
  //Informamos que o pino do botao atuara como entrada
  pinMode(pinoDHT, INPUT);

  //Associa a funcao que verifica a conexao do modulo ao objeto "lorawan"
  lorawan.event_listener = &event_handler;
  Serial.println(F("Evento configurado."));

  //Requisita e imprime o Device EUI do modulo
  char deveui[16];
  resposta = lorawan.get_DevEUI(deveui);
  if(resposta == CommandResponse::OK){
    Serial.print(F("DevEUI: "));
    Serial.write((uint8_t *)deveui, 16);
    Serial.println();
  } else {
    Serial.println(F("Erro ao obter o Device EUI"));
  }

  //Configura o Application EUI no modulo
  resposta = lorawan.set_AppEUI(APPEUI);
  if(resposta == CommandResponse::OK){
    Serial.print(F("Application EUI configurado ("));
    Serial.write((uint8_t *)APPEUI, 16);
    Serial.println(')');
  } else {
    Serial.println(F("Erro ao configurar o Application EUI"));
  }

  //Configura o Application Key no modulo
  resposta = lorawan.set_AppKey(APPKEY);
  if(resposta == CommandResponse::OK){
    Serial.print(F("Application Key configurado ("));
    Serial.write((uint8_t *)APPKEY, 32);
    Serial.println(')');
  } else {
    Serial.println(F("Erro ao configurar o Application Key"));
  }

  //Condfigura o metodo de conexao como OTAA
  resposta = lorawan.set_JoinMode(SMW_SX1276M0_JOIN_MODE_OTAA);
  if(resposta == CommandResponse::OK){
    Serial.println(F("Metodo de Conexao Configurado como OTAA"));
  } else {
    Serial.println(F("Erro ao configurar o metodo OTAA"));
  }

  //Requisita conexao com a rede
  Serial.println(F("Conectando a Rede"));
  lorawan.join();
  
}

//------------------------------------------------------------------------
void loop() {

  //Recebe informacoes do modulo
  lorawan.listen();

  if(lorawan.isConnected()){  //Verifica se o modulo esta conectado
  
    //Executa o envio da mensagem uma vez a cada 5 minutos
    if(intervalo < millis()){
      
      //Realiza a leitura do LDR e mapeia a leitura entre 0 e 100
      leitura_LDR = analogRead(PINO_LDR);
      temperatura = dht.readTemperature();
      umidade = dht.readHumidity();
      leitura_LDR = map(leitura_LDR, 0, 4095, 100, 0);
      
      // Cria o objeto dinâmico "json" com tamanho "3" para a biblioteca
      DynamicJsonDocument json(JSON_OBJECT_SIZE(3));

      // Atrela ao objeto "json" a leitura do LDR com o nome do Alias definido
      json[ALIAS] = leitura_LDR;

      // Adiciona a temperatura ao objeto "json" com um Alias específico (ALIAS1)
      json[ALIAS1] = temperatura;

      // Adiciona a umidade ao objeto "json" com um Alias específico (ALIAS2)
      json[ALIAS2] = umidade;

      // Mede o tamanho da mensagem "json" e atrela o valor somado em uma unidade ao objeto "tamanho_mensagem"
      size_t tamanho_mensagem = measureJson(json) + 1;

      // Cria a string "mensagem" de acordo com o tamanho do objeto "tamanho_mensagem"
      char mensagem[tamanho_mensagem];

      // Copia o objeto "json" para a variável "mensagem" e com o "tamanho_mensagem"
      serializeJson(json, mensagem, tamanho_mensagem);

      //Imprime a mensagem e envia a mensagem como texto pelo modulo
      Serial.print(F("Mensagem: "));
      Serial.println(mensagem);
      resposta = lorawan.sendT(1, mensagem); //Envio como texto  
     

      intervalo = millis() + TEMPO_ESPERA; //Atualiza a contagem de tempo
      
    }
  } else {    //Se o modulo nao estiver conectado
  
    //Imprime um "." a cada 5 segundos
    if(intervalo < millis()){
  
      Serial.println('.');
      intervalo = millis() + 5000; //Atualiza a contagem de tempo
      
    }
  }

}

//------------------------------------------------------------------------
void event_handler(Event type){
  
  //Verifica se o modulo esta conectado e atualiza essa informacao
  if(type == Event::JOINED){
    Serial.println(F("Conectado!"));
  }
  
}
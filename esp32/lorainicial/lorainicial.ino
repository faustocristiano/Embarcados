/*******************************************************************************
* IoT DevKit - Primeiro contato com o modulo LoRaWAN Bee (v1.0)
* 
* Codigo usado para enviar comandos "AT" para o modulo e imprimir
* suas respostas.
* 
* Copyright 2020 RoboCore.
* Escrito por Giovanni de Castro (21/08/2020).
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

//Inclusao da biblioteca
#include "RoboCore_SMW_SX1276M0.h"

//Declaracao dos pinos de comunicacao serial do Kit
#include <HardwareSerial.h>
HardwareSerial LoRaSerial(2);
#define RXD2 16
#define TXD2 17

//Criacao do objeto lorawan para a biblioteca SMW_SX1276M0
SMW_SX1276M0 lorawan(LoRaSerial);

void setup() {
  
  //Inicia o monitor serial e imprime o cabecalho
  Serial.begin(115200);
  Serial.println(F("--- SMW_SX1276M0 Bridge ---"));

  //Definicao do pino de reset do modulo
  lorawan.setPinReset(5);
  lorawan.reset(); //Realiza um reset no modulo
  
  //Inicia a comunicacao serial com o modulo
  LoRaSerial.begin(115200, SERIAL_8N1, RXD2, TXD2);
  
}

void loop() {
  
  //Recebe as informacoes do modulo e exibe no monitor serial
  if(LoRaSerial.available()){
    Serial.write(LoRaSerial.read());
  }

  //Recebe as informacoes do monitor serial e envia para o modulo
  if(Serial.available()){
    LoRaSerial.write(Serial.read());
  }
  
}
// Valores constantes
float R0 = 10000.0; // Resistência nominal do termistor em ohms
float Vin = 5.0;    // Tensão de alimentação em volts
float fator = 0.7194949494949725;


// Coeficientes para o cálculo da temperatura
float coeficiente[3] = {-1.1011e-03, 5.9740e-04, -1.3336e-06};

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(9600);
}

// Função para calcular a resistência do termistor
float resistencia(float V) {
  return float (R0 * (Vin - V)) / V;
}

// Função para calcular a tensão do termistor
float tensao(float coeficiente) {
  return float (coeficiente / 1023) * Vin;
}

// Função para calcular a temperatura usando a equação de Steinhart-Hart
float temperatura(float R) {
  return 1.0 / ((coeficiente[0] + coeficiente[1] * log(R) + coeficiente[2] * pow(log(R), 3))) - 273.0 + fator;
}

void loop() {
  // Realiza a leitura analógica do pino A0
  float leitura = analogRead(A0);
  
  // Calcula a tensão do termistor
  float V0 = tensao(leitura);
  
  // Calcula a resistência do termistor
  float resistor = resistencia(V0);
  
  // Calcula a temperatura usando a equação de Steinhart-Hart
  float temp = temperatura(resistor);

  // Imprime a temperatura no monitor serial
  Serial.print(temp);
  Serial.println(" °C");

  // Aguarda 10 segundos antes de realizar a próxima leitura
  delay(2000);
}

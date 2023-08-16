const int pinoBotao = 2;
const int pinoLed = 13;

volatile int estadoBotao = LOW; // Variável para armazenar o estado atual do botão
volatile unsigned long ultimoDebounceTime = 0; // Variável para armazenar o último tempo de debounce
const unsigned long debounceDelay = 200; // Intervalo de debounce em milissegundos
int estado = 0; // Variável para controlar o estado da máquina de estados

void setup() {
  pinMode(pinoLed, OUTPUT); // Define o pino do LED como saída
  pinMode(pinoBotao, INPUT_PULLUP); // Define o pino do botão como entrada com resistor de pull-up interno
}

// Função de interrupção para lidar com o debounce do botão
void interrupcaoBotao() {
  unsigned long debounceAtual = millis(); // Obtém o tempo atual em milissegundos

  // Verifica se o intervalo de debounce foi atingido
  if ((debounceAtual - ultimoDebounceTime) > debounceDelay) {
    // Atualiza o estado do botão apenas se o intervalo de debounce foi atingido
    if (digitalRead(pinoBotao)) {
      // Botão foi pressionado, inverte o estado do LED
      digitalWrite(pinoLed, estadoBotao);
      estadoBotao = !estadoBotao;
    }

    ultimoDebounceTime = debounceAtual; // Atualiza o último tempo de debounce
  }
}

void loop() {
  switch (estado) {
    case 0:
      // Estado inicial - aguarda o botão ser pressionado
      if (digitalRead(pinoBotao)) {
        estado = 1;
        attachInterrupt(digitalPinToInterrupt(pinoBotao), interrupcaoBotao, RISING);
        // Habilita a interrupção no pino do botão (borda de subida)
        // para tratar a ação do botão pressionado
      }
      break;

    case 1:
      // Aguarda um pequeno atraso para evitar transições indesejadas
      estado = 2;
      delay(20);
      break;

    case 2:
      // Aguarda o botão ser solto
      if (!digitalRead(pinoBotao)) {
        estado = 3;
        attachInterrupt(digitalPinToInterrupt(pinoBotao), interrupcaoBotao, RISING);
        // Habilita a interrupção no pino do botão (borda de subida)
        // para tratar a ação do botão solto
      }
      break;

    case 3:
      // Aguarda um pequeno atraso para evitar transições indesejadas
      estado = 0;
      delay(20);
      break;
  }

  delay(1); // Pequeno atraso para evitar execução muito rápida do loop
}

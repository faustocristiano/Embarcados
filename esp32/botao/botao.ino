/************************************************
* RoboCore - IoT DevKit - LoRaWAN   
*
* Aprendendo a utilizar o botao e o LED do kit
***********************************************/

//Declaracao da variavel do pino do LED e do botao
const int pinoLED = 13;
const int pinoBotao = 4;

//Cria a variavel que verificara o estado do botao
int estadoBotao = 0;

//Cria a variavel que salvara o estado atual do botao
int flag = 0;

void setup() {
  //Informa que o pino do LED eh saida e o pino botao eh entrada
  pinMode(pinoLED, OUTPUT);
  pinMode(pinoBotao, INPUT);
}

void loop() {
  //Grava na variavel estadoBotao o estado atual do botao
  estadoBotao = digitalRead(pinoBotao);
  
  //Se o botao estiver pressionado aguarda 30 milisegundos, faz nova leitura e altera o estado atual do LED, salvando na variavel flag o novo estado.
  if (estadoBotao == LOW) {
    delay(30);
    estadoBotao = digitalRead(pinoBotao);

    if (flag == 0) {
      digitalWrite(pinoLED, HIGH);
      flag = 1;
    } else {
      digitalWrite(pinoLED, LOW);
      flag = 0;
    }

    while(digitalRead(pinoBotao) == LOW){
      // fica aqui aguardando soltar o botao
    }
  }
}
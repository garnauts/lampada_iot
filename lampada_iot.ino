// Programa : Liga ou Desliga uma lampada, no bocal ou na tomada.
// Autor : Gilberto Carlos Arnauts

//Pino 4: Inverte as configurações de ligado e desligado.

//Pino 7: Entrada de um interruptor 5 V que quando tem o status alerado, provoca o desligamento ou ligamento da lampada.
//Pino 11: Entrada do sensor de infravermelho.
//Pino 12: Liga ou desliga o rele, e o pino 13 tem sempre o status inverso dele.
//Pino 13: Liga ou desliga o rele, inverso ao 12. 

#include <IRremote.h>

int RECV_PIN = 11;
float armazenavalor;
int pinorele = 13;
int pinorele2 = 12;
int pininterruptor = 7;
int pininverteconfiguracoes = 4;
long milisQueFoiLigado = 0;
int ultimoStatusInterruptor;

boolean ligado = true;

IRrecv irrecv(RECV_PIN);
decode_results results;

void dlg() {
  if (digitalRead(pininverteconfiguracoes) == LOW){
    digitalWrite(pinorele, LOW);
    digitalWrite(pinorele2, HIGH);
  } else {
    digitalWrite(pinorele, HIGH);
    digitalWrite(pinorele2, LOW);
  }
  ligado = false;
  Serial.println("Desligado");
}

void lg() {
  if (digitalRead(pininverteconfiguracoes) == LOW){
    digitalWrite(pinorele, HIGH);
    digitalWrite(pinorele2, LOW);
  } else {
    digitalWrite(pinorele, LOW);
    digitalWrite(pinorele2, HIGH);
  }
  ligado = true;
  milisQueFoiLigado = millis();
  Serial.println("Ligado");
}

void liga(){
  if (digitalRead(pininverteconfiguracoes) == LOW){
    lg();
  } else {
    dlg();
  }
}

void desliga(){
   if (digitalRead(pininverteconfiguracoes) == LOW){
    dlg();
  } else {
    lg();
  }
}

void setup()
{
  pinMode(pinorele, OUTPUT);
  pinMode(pinorele2, OUTPUT);
  pinMode(pininterruptor, INPUT);
  pinMode(pininverteconfiguracoes, INPUT);
  ultimoStatusInterruptor = digitalRead(pininterruptor);
  Serial.begin(9600);
  liga();
  irrecv.enableIRIn(); // Inicializa o receptor IR
}

void loop()
{
  //Serial.println(millis());
  //Desliga após algumm tempo esquecido ligado (7200000):
  boolean muitoTempoLigado = ligado == true and (millis() - milisQueFoiLigado) > 7200000;
  if (muitoTempoLigado) Serial.println("Muito tempo ligado...");
  int statusInterruptor = digitalRead(pininterruptor);
  if (irrecv.decode(&results) or muitoTempoLigado or statusInterruptor != ultimoStatusInterruptor)
  {
    ultimoStatusInterruptor = statusInterruptor;
    Serial.print("Valor lido : ");
    Serial.println(results.value, HEX);
    armazenavalor = (results.value);
    //if (armazenavalor == 0xFF30CF) //Verifica se a tecla 1 foi acionada
    //{
    //digitalWrite(pinorele, HIGH);  //Acende o led vermelho
    //}
    if (ligado) {
      desliga();
    } else {
      liga();
    }
    delay(1000);
    irrecv.resume(); //Le o próximo valor
  }
  delay(150);
}

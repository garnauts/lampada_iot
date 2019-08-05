// Programa : Teste Controle Remoto IR
// Autor : Arduino e Cia

#include <IRremote.h>

int RECV_PIN = 11;
float armazenavalor;
int pinorele = 13;
int pinorele2 = 12;
long milisQueFoiLigado = 0;

boolean ligado = true;

IRrecv irrecv(RECV_PIN);
decode_results results;

void desliga() {
  digitalWrite(pinorele, LOW);
  digitalWrite(pinorele2, HIGH);
  ligado = false;
  Serial.println("Desligado");
}

void liga() {
  digitalWrite(pinorele, HIGH);
  digitalWrite(pinorele2, LOW);
  ligado = true;
  milisQueFoiLigado = millis();
  Serial.println("Ligado");
}

void setup()
{
  pinMode(pinorele, OUTPUT);
  pinMode(pinorele2, OUTPUT);
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
  if (irrecv.decode(&results) or muitoTempoLigado)
  {
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

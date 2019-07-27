// Programa : Teste Controle Remoto IR  
// Autor : Arduino e Cia  
  
#include <IRremote.h>  
  
int RECV_PIN = 11;  
float armazenavalor;  
int pinorele = 13; 

boolean ligado = true;
  
IRrecv irrecv(RECV_PIN);  
decode_results results;  
  
void setup()  
{  
  pinMode(pinorele, OUTPUT);   
  digitalWrite(pinorele, HIGH);
  Serial.begin(9600);  
  irrecv.enableIRIn(); // Inicializa o receptor IR  
}  
   
void loop()  
{  
  if (irrecv.decode(&results))  
  {  
    Serial.print("Valor lido : ");  
    Serial.println(results.value, HEX);  
    armazenavalor = (results.value);  
    //if (armazenavalor == 0xFF30CF) //Verifica se a tecla 1 foi acionada  
    //{  
      //digitalWrite(pinorele, HIGH);  //Acende o led vermelho  
    //}  
    if(ligado){
      digitalWrite(pinorele, LOW);
      ligado = false;
    } else {
      digitalWrite(pinorele, HIGH);
      ligado = true;
    }
    delay(1000);
    irrecv.resume(); //Le o próximo valor  
  }  
} 

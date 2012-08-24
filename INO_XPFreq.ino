// INO_XPFreq
// Visualizador de frequencias do X-Plane
// 2012 - josenildo.nascimento@gmail.com

// Importa a biblioteca para o Display de Cristal Liquido
#include <LiquidCrystal.h>

// Inicializa a interface da biblioteca com os seguintes pinos:
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


char buffer[41];        // Buffer de caracteres tamnaho 41
int pointer = 0;        // Inicializa ponteiro do Buffer
byte inByte = 0;        // Inicializa a variavel onde serao armazenados os dados seriais

// Inicializacao
void setup() {
  lcd.begin(20, 4);      // Inicializa o Display informando 4 linhas de 20 Caracteres
  Serial.begin(115200);  // Abre a serial port 
  
  // texto inicial
  lcd.clear();
  lcd.print("X-Plane - Freq"); 
  lcd.setCursor(14, 3);   
  lcd.print("by JOZ");    
 
  } // fim do setup
  
void loop() {

  // Se existir dados via serial:
  if (Serial.available() >0) {
    
    // leitura dos dados:
    inByte = Serial.read();
    delay(1); // atraso para evitar que o dado seja lido na proxima iteracao
    
    // Se o caractere inicial eh encontrado, serao armazado
    if (inByte == 'F') {
      while (pointer < 40) { // acumula 40 characteress
        buffer[pointer] = Serial.read(); // armazena no buffer
        delay(1); // atraso para minimizar leituras incorretas
      
      pointer++; // move o ponteiro no buffer
      } // fim do while
      
      
      // Inicializa texto
      lcd.setCursor(0, 0);
      lcd.print("COM1: ");
      lcd.setCursor(0, 1);
      lcd.print("COM2: ");
      lcd.setCursor(0, 2);
      lcd.print("NAV1: ");
      lcd.setCursor(0, 3);
      lcd.print("NAV2: ");      
      
      for(int i = 0; i < 4; i++){ // para cada linha
                
        lcd.setCursor(6, i); // Posiciona cursor onde comecara a escrever
        
        // Escreve os valores armazenados no buffer
        for(int x = 0; x < 10; x++){
          if (x == 3){
          lcd.print(",");
          }
          else if (x == 5){
          lcd.print("<>");
          }
          else if (x == 8){
          lcd.print(",");
          }
          lcd.print(buffer[x+(i*10)]);
        } // fim do "for buffer itarations'"
      } // fim do "for LCD lines"

    pointer = 0; // reseta o ponteiro para ser utilizado novamente
    } // fim do "if caractere inicial"
  } // fim do "if serial available"
  

} // fim do loop

#include <Servo.h> 

Servo servoPitch;  // Cria um um objeto Servo para controlar o servo motor da arfagem 
Servo servoRoll;  // Cria um um objeto Servo para controlar o servo motor da rolagem 
int posPitch = 0;
int posRoll = 0;

// Cria a variável que irá receber os dados seriais.
int serCom;

// Criam as variáveis para armazenar dados em formato de texto.
String pitch, pitchold, roll, rollold;

// Inicializa o hardware
void setup() 
{

  servoPitch.attach(8);  // Correlaciona o objeto Servo (Arfagem) ao pino 8 do arduino
  servoRoll.attach(9);  // Correlaciona o objeto Servo (rolagem) ao pino 9 do arduino

  Serial.begin(115200);  // inicializa a comunicação serial na velocidade de 115200bps
  
Serial.flush(); // Aguarda terminar alguma comunicação serial
}

// O programa em si 

void loop() {
  
  // Verifica se a comunicação serial está disponível
   if (Serial.available() > 0) {
     
    // Lê o último byte recebido via comunicação serial
    serCom = Serial.read();
    
    if (serCom == 'A'){     // verifica o simbolo que representa o início da informação de arfagem
              
              delay (11); // Espera necessária para evitar erro de leitura
              
              pitch = ""; // Inicializa a variável para a arfagem
              pitch += char(Serial.read());// sinal
              pitch += char(Serial.read()); // Caractere para representar centena de Graus
              pitch += char(Serial.read()); // Caractere para representar dezena de Graus
              pitch += char(Serial.read()); // Caractere para representar unidade de Graus
              pitch += char(Serial.read()); // ponto decimal
              pitch += char(Serial.read()); // Caractere para representar a parte decimal dos graus
              if (pitch != pitchold){  // Verifica se a leitura atual é diferente da última leitura
                   
                   // Convertemos a partir da tabela ASCII os bytes recebidos para um valor decimal
                   posPitch = ((pitch[2]-48)*10+(pitch[3]-48));
                   
                   // Se o sinal for negatvo, multiplicamos por -1 para obter um valor negativo
                   if (pitch[0] == '-'){
                       posPitch = (posPitch * -1);
                    }
                   
                   // Adicionamos o valor da arfagem ao valor "neutro" do servo motor 
                   posPitch = posPitch + 90;
                   servoPitch.write(posPitch);
                   delay(11); // Aguarda o servo se posicionar

                   pitchold = pitch; // O valor recebido será considerado como último valor.
                    }        
              }
    
   if (serCom == 'B'){    // verifica o simbolo que representa o início da informação de rolagem
              
              delay (11); // Espera necessária para evitar erro de leitura
              
              roll = ""; // Inicializa a variável para a rolagem
              roll += char(Serial.read()); // sinal
              roll += char(Serial.read()); // Caractere para representar centena de Graus 
              roll += char(Serial.read()); // Caractere para representar dezena de Graus
              roll += char(Serial.read()); // Caractere para representar unidade de Graus
              roll += char(Serial.read()); // ponto decimal
              roll += char(Serial.read()); // Caractere para representar a parte decimal dos graus
              
              if (roll != rollold){ // Verifica se a leitura atual é diferente da última leitura
                   
                   // Convertemos a partir da tabela ASCII os bytes recebidos para um valor decimal
                   posRoll = ((roll[2]-48)*10+(roll[3]-48));
                   
                   // Se o sinal for negatvo, multiplicamos por -1 para obter um valor negativo
                   if (roll[0] == '-'){
                       posRoll = (posRoll * -1);
                    }
                    
                   // Adicionamos o valor da rolagem ao valor "neutro" do servo motor
                   posRoll = posRoll + 90;
                   servoRoll.write(posRoll);
                   delay(11); // Aguarda o servo se posicionar
                   
                   rollold = roll; // O valor recebido será considerado como último valor.
                    }        
              } 
      
   }

}

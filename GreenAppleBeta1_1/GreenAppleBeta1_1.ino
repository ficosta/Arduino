// ------------------------------------------------- //
// Carga de bibliotecas
#include <LiquidCrystal.h>
#include "pitches.h"
// ------------------------------------------------- //




// ------------------------------------------------- //
// Pinos do arduino e definicoes de hardware
LiquidCrystal lcd1(A3,A4,10,11,12,13);   // LiquidCrystal(rs(4), enable(6), d4(11), d5(12), d6(13), d7(14)) 
byte ledPins[] = {2, 3, 4, 5, 6, 7, 8};   // array com os pinos dos leds
byte totalLeds = 7;    // numero total de leds
byte buzzerPin = A0;  //Pino com o buzzer de sons
byte buttonPin = A2; // Pino com witcher para os tiros do jogador A.
// ------------------------------------------------- //




// ------------------------------------------------- //
// Variaveis globais
int placar=0;
int velocidade = 250;
byte partida = 70;
int pontuacaoVencedora = 7;
int melodiaVenceu[] = {NOTE_C5, NOTE_B4, NOTE_C5, NOTE_G4, NOTE_GS4, NOTE_C5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4 };
int melodiaPerdeu[] = {NOTE_G4, NOTE_C5, NOTE_D5, NOTE_G5, NOTE_G4, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_G4, NOTE_A4, NOTE_B4};
int duracaoNota[] = {8, 8, 4, 4, 4, 8, 8, 4, 4, 4, 4 };






// ------------------------------------------------- //





// ------------------------------------------------- //
// Funcao inicial executada uma unica vez
void setup() {
  Serial.begin(9600); // <-- Iniciai a porta serial.
  lcd1.begin(16,2); // < -- Inicia a matrix do LCD.
  pinMode(buttonPin, INPUT); // <-- Modo do pino da chave do jogador.
  pinMode(buzzerPin, OUTPUT); // <-- Modo do pino do buzzer.
  // Definir todos os modos de pino dos leds 
  for (byte ledAtual = 0; ledAtual < totalLeds; ledAtual++) {
      pinMode(ledPins[ledAtual], OUTPUT); 
  }
}
// ------------------------------------------------- //





// ------------------------------------------------- //
// Funcao do loop geral so sistema
void loop() {
  
  while((partida <= 70) && (partida != 0) && (placar != pontuacaoVencedora)){
    exibeDisplay(" Pegue a verde! ", 10);
    for (byte ledAtual = 0; ledAtual < totalLeds; ledAtual++) { // <-- Sequencia leds ...
      digitalWrite(ledPins[ledAtual], HIGH);
      delay(velocidade);
      if ((ledAtual == 3) && (digitalRead(buttonPin) == HIGH)){ // <-- Acerto do alvo
        placar++;
        acertou_alvo();
        velocidade=velocidade-25; // <-- Aumenta a dificuldade do acerto no alvo
      }
      else if((ledAtual != 3) && (digitalRead(buttonPin) == HIGH)){ // <-- Erro do alvo
        placar--;
        errou_alvo();
        velocidade=velocidade+25; // <-- Diminui a dificuldade do acerto no alvo
      }
      digitalWrite(ledPins[ledAtual], LOW);
    } // fim do for()
    partida--;    
  } // fim do while 
  if (placar == pontuacaoVencedora) { // venceu o jogo 
    venceu_o_jogo();
    placar= 0;
    partida = 70;
   } 
  else {
    perdeu_o_jogo();
    placar=0;
    partida=70;
  }
} // fim do looop
// ------------------------------------------------- //









// FUNCOES AUXILIARES  ------------------------------//
// --------------------------------------------------//




// --------------------------------------------------//
// Funcao jogo vencido
void venceu_o_jogo(){
    exibeDisplay(" VENCEU O JOGO ", 100);
    for (byte ledAtual = 0; ledAtual < totalLeds; ledAtual++) {
       digitalWrite(ledPins[ledAtual], HIGH);
       // Inicio da musica
       // créditos: http://www.instructables.com/id/Musical-Table/step10/Play-music-with-toys/
        for (int thisNote = 0; thisNote < 11; thisNote++) {
              // to calculate the note duration, take one second 
              // divided by the note type.
              //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
              int tempoNoBuzzer = 1000/ duracaoNota[thisNote];
              tone(buzzerPin, melodiaVenceu[thisNote],tempoNoBuzzer);
              // to distinguish the notes, set a minimum time between them.
              // the note's duration + 30% seems to work well:
              int pauseBetweenNotes = tempoNoBuzzer * 1.30;
              delay(pauseBetweenNotes);
              noTone(buzzerPin);
       } // fim da musica
     } // fim do for
}
// --------------------------------------------------//





// --------------------------------------------------//
// Funcao fim do jogo.
void perdeu_o_jogo(){
exibeDisplay("** GAME  OVER **", 100);
    for (byte ledAtual = 0; ledAtual < totalLeds; ledAtual++) {
       digitalWrite(ledPins[ledAtual], LOW);
       for (int thisNote = 0; thisNote < 11; thisNote++) {
              // to calculate the note duration, take one second 
              // divided by the note type.
              //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
              int tempoNoBuzzer = 1000/ duracaoNota[thisNote];
              tone(buzzerPin, melodiaPerdeu[thisNote],tempoNoBuzzer);
              // to distinguish the notes, set a minimum time between them.
              // the note's duration + 30% seems to work well:
              int pauseBetweenNotes = tempoNoBuzzer * 1.30;
              delay(pauseBetweenNotes);
              // stop the tone playing:
              noTone(buzzerPin);
       } // fim da musica
    } // fim do for dos leds
}
// --------------------------------------------------//





// ------------------------------------------------- //
// Funcao para registrar o placar do jogo e Informaces no LCD
void exibeDisplay(String primeiraLinha, int tempoExibicao){ // <-- Informe frase a ser exibida e tempo de exibicao
lcd1.clear();
lcd1.setCursor(0,0);
lcd1.print(primeiraLinha);
lcd1.setCursor(0,1);
lcd1.print("Suas: ");
lcd1.setCursor(5,1);
lcd1.print(placar);
lcd1.setCursor(9,1);
lcd1.print("Time:");
lcd1.setCursor(14,1);
lcd1.print(partida);
delay(tempoExibicao);
} 
// ------------------------------------------------- //





// ------------------------------------------------- //
// Funcao com as acoes quando se acerta o alvo
void acertou_alvo(){
        tone(buzzerPin,1600,500);
        exibeDisplay("PEGOU MAIS UMA!!", 10);
        delay(1000);
        noTone(buzzerPin);
        digitalWrite(ledPins[3], HIGH);
        delay(200);
        digitalWrite(ledPins[3], LOW);
        delay(200);
        digitalWrite(ledPins[3], HIGH);
        delay(100);
        digitalWrite(ledPins[3], LOW);
        delay(100);
        digitalWrite(ledPins[3], HIGH);
        delay(50);
        digitalWrite(ledPins[3], LOW);
        delay(50);
        digitalWrite(ledPins[3], HIGH);
        delay(25);
        digitalWrite(ledPins[3], LOW);
        delay(25);       
        tone(buzzerPin,2300,100);
        delay(120);
        noTone(buzzerPin);
     } 
// ------------------------------------------------- //





// ------------------------------------------------- //
// Funcao com as acoes quando se erra o alvo
void errou_alvo(){
        tone(buzzerPin,480,500);
        exibeDisplay("* ERA VERMELHA *", 10);
        delay(1000);
        noTone(buzzerPin);
    } 
// ------------------------------------------------- //

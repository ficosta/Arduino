// USANDO O LCD
// Quinto estudo arduino   -  31/08/2012

// chama a biblioteca do Display
#include <LiquidCrystal.h>
// Instancia como lcd1 e define os pinos usados no arduino para:
// LiquidCrystal(rs, enable, d4, d5, d6, d7) 


LiquidCrystal lcd1(8,9,10,11,12,13);
char recebe_entrada_serial;


void setup() {
  Serial.begin(9600);
  lcd1.begin(16,2);
  lcd1.clear();
    }



void loop() {
  recebe_entrada_serial = Serial.read();
   // exibindo dados na entrada seral 
  lcd1.println(char(recebe_entrada_serial));
  delay(200);
  }



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
  lcd1.setCursor(0,0);
  lcd1.print("Mon petit vulcan");
  crowler(16);

  lcd1.setCursor(0,1);
  lcd1.print("You're eruptions and disasters");
  crowler(16);

  lcd1.setCursor(0,0);
  lcd1.print("I keep calm ");
  crowler(16);

  lcd1.setCursor(0,1);
  lcd1.print("Admiring the lava");
  crowler(16); 

  lcd1.setCursor(0,0);
  lcd1.print("I keep calm");
  crowler(16);

  }



void crowler(int desloca){
   delay(900);
   for (int i=0 ; i < desloca ; i++) {
      lcd1.scrollDisplayLeft();
      delay(250);
    }
    delay(1200);
    lcd1.clear(); 
  }

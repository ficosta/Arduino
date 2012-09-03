// REcebe dados pela Serial do Processing
// Terceiro estudo arduino   -  30/08/2012

const int totalLeds = 12;    // numero total de leds



int ledPins[] = { 2, 3, 4, 5, 6, 7,8,9,10,11,12,13 };   // array com os pinos dos leds


void setup() {
  Serial.begin(9600);
    // Definir todos os modos de pino dos leds 
    for (int thisLed = 0; thisLed < totalLeds; thisLed++) {
      pinMode(ledPins[thisLed], OUTPUT); 
    }
}

void loop() {
  // Le o resultado do sensor
  int sensorReading = Serial.read();
  // mapeia o resultado do sensor de 0 ate o numero de leds
  int ledLevel = map(sensorReading, 0, 255, 0, totalLeds);
  // Loop no vetor de leds
  for (int thisLed = 0; thisLed < totalLeds; thisLed++) {
    // se o led atual for menor que o total de leds,
    // acende os leds
      if (thisLed < ledLevel) {
        digitalWrite(ledPins[thisLed], HIGH);
        delay(3);
       } 
      // desliga todos os leds menores que ledLevel:
      else {
        digitalWrite(ledPins[thisLed], LOW); 
      }
  }
float voltagem = map(sensorReading, 60, 490, 0, 5);;
Serial.println (voltagem);

}

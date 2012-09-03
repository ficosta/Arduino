// Termometro simples
// Terceiro estudo arduino   -  30/08/2012

const int sensor = A0;   // Sensor de Luz
const int totalLeds = 11;    // numero total de leds



int ledPins[] = { 2, 3, 4, 5, 6, 7,8,9,10,11,12};   // array com os pinos dos leds


void setup() {
  Serial.begin(9600);
    // Definir todos os modos de pino dos leds 
    for (int thisLed = 0; thisLed < totalLeds; thisLed++) {
      pinMode(ledPins[thisLed], OUTPUT); 
    }
    //define o pino 13 para saida fora do vetor de leds
    pinMode(13,OUTPUT);
}

void loop() {
  // Le o resultado do sensor
  int sensorReading = analogRead(sensor);
  // mapeia o resultado do sensor de 0 ate o numero de leds
  int ledLevel = map(sensorReading, 60, 490, 0, totalLeds);
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
int nota = map(sensorReading, 60, 490, 440, 1760);
tone(13,nota,200);
float voltagem = map(sensorReading, 60, 490, 0, 5);;
Serial.println (sensorReading);
}

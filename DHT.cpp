// /*---Includes---*/
// #include <Arduino.h>
// #include "DHT.h"

// /*---Hardware mapping---*/
// const uint8_t PIN_INPUT = 26;

// /*---Constants---*/
// #define DHTTYPE DHT11

// /*---Variables---*/
// DHT dht(PIN_INPUT, DHTTYPE);

// /*---Setup---*/
// void setup() 
// {
//   dht.begin();

//   //Print
//   Serial.begin(115200); 
//   //velocidade de comunicação, quantidade de bits por segundo que vai passar. Na ESP32 é 115200.
// }

// /*---Loop---*/
// void loop() 
// {
//   float humidade = dht.readHumidity();
//   float temperatura = dht.readTemperature();
//   if(isnan(humidade) || isnan(temperatura))
//   {
//     Serial.println("Falha na leitura do sensor DHT.");
//     return;
//   }
  
//   Serial.printf("Humidade: %4.2f Temperatura: %7.2f\n\n", humidade, temperatura);
//   delay(2000);
// }
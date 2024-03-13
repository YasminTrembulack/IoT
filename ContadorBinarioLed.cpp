// #include <Arduino.h>
// const uint8_t PINOS_LED[] = {12, 14, 27, 26}; 

// void setup() {
//   for (auto pino : PINOS_LED)
//   {
//     pinMode(pino, OUTPUT);
//   }
// }

// void loop() {
//   for(uint8_t i = 0; i < 15; i++)
//   {
//     for(uint8_t j = 0; j < 4; j++)
//     {
//       digitalWrite(PINOS_LED[j], ((i % (2<< j)) - (i % (1 << j))) > 0);
//     }
//     delay(1000);
//   }
// }
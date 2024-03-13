// #include <Arduino.h>
// const uint8_t PIN_BOTAO = 25; 
// const uint8_t PIN_LED = 26; 

// //Variables
// bool led_state = LOW;
// bool botao_anterior = LOW;
// bool pressionado = LOW;

// void setup() {
//   pinMode(PIN_BOTAO, INPUT);
//   pinMode(PIN_LED, OUTPUT);
// }

// void loop() {
//   botao_anterior = pressionado;
//   pressionado = digitalRead(PIN_BOTAO);

//   if(pressionado && !botao_anterior)
//   {
//     led_state = !led_state;
//     digitalWrite(PIN_LED, led_state);
//   }
// }

/*-----------------------------------------*/

// const uint8_t PIN_BOTAO = 25; 
// const uint8_t PIN_LED = 26; 

// /*---Variables---*/
// bool led_state = LOW;
// bool botao_anterior = LOW;
// bool pressionado = LOW;
// long tempo = 0;

// /*---Setup---*/
// void setup() {
//   pinMode(PIN_BOTAO, INPUT);
//   pinMode(PIN_LED, OUTPUT);
// }

// /*---Loop---*/
// void loop() {
//   botao_anterior = pressionado;
//   pressionado = digitalRead(PIN_BOTAO);

//     if(pressionado && !botao_anterior && millis() - tempo > 50)
//     {
//       led_state = !led_state;
//       digitalWrite(PIN_LED, led_state);

//       //retorna o tempo em milisegundos que a esp ta ligada
//       tempo = millis();
//     }
// }
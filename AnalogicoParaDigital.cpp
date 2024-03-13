// #include <Arduino.h>

// /*---Hardware mapping---*/
// const uint8_t PIN_INPUT = 26;

// /*---Constants---*/
// const uint16_t ADC_MAX = 4095; // valor maximo do conversor analogico digital
// const float VCC = 3.3f; // tensao de referencia dos esp32

// /*---Variables---*/

// /*---Setup---*/
// void setup() 
// {
//   pinMode(PIN_INPUT, INPUT);

//   //Print
//   Serial.begin(115200); 
//   //velocidade de comunicação, quantidade de bits por segundo que vai passar. Na ESP32 é 115200.
// }

// /*---Loop---*/
// void loop() 
// {
//  uint16_t input_value = analogRead(PIN_INPUT);

//  //Na divisao pelo menos um valor precisa ser float
//  float voltage =  static_cast<float>(input_value) * VCC / static_cast<float>(ADC_MAX);

//  //Serial.write()://   char
  
//  //Serial.print(voltage);//   print tudo em uma linha só sem separar
//  Serial.println(voltage);

//  //Serial.println()://  print pulando linha \n
 
// }
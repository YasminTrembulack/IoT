// /*---Includes---*/
// #include <WiFi.h>
// #include <Arduino.h>
// #include "PubSubClient.h"
// #include <FirebaseESP32.h>

// /*---Hardware mapping---*/
// const uint8_t PIN_NTC_00 = 35;
// const uint8_t PIN_NTC_01 = 34;

// const uint8_t PIN_BOTAO = 21;

// const uint8_t PIN_LED_00 = 33;
// const uint8_t PIN_LED_01 = 32;
// const uint8_t PIN_LED_02 = 19;
// const uint8_t PIN_LED_03 = 18;


// /*---Constants---*/

// const uint16_t ADC_MAX = 4095; // valor maximo do conversor analogico digital
// const float VREF = 3.3f; // tensao de referencia dos esp32
// const float R1 = 10000.0f;

// const char* WIFI_SSID = "Vivo-Internet-BF17";
// const char* WIFI_PW = "78814222";

// const char* FB_HOST = "https://iiot-dta-default-rtdb.firebaseio.com";
// const char* FB_KEY = "Ag5gJMhAnTWQgDVhegkDRF1uTjJfpMUDkXB8WBEa";

// //MQTT
// const char* MQTT_BROKER = "test.mosquitto.org";
// const uint16_t MQTT_PORT = 1883;
// const char* MQTT_USERNAME = "";
// const char* MQTT_PASSWORD = "";

// /*---Variables---*/

// FirebaseData fbdo; //informações do banco de dados
// FirebaseAuth fbauth; //metodo de autenticação
// FirebaseConfig fbconfig; 

// bool button_state = 0;

// float a = 12.9611833;
// float b = -0.0761498101;
// float c = 3.40889111;
// float d = -64.5957953;
// float e = 390.218793;


// //MQTT
// WiFiClient wifi_client;
// PubSubClient mqtt_client(wifi_client);

// /*---Function---*/
// bool connectWiFi(const char* ssid, const char* pw)
// {
//   WiFi.mode(WIFI_STA);
//   WiFi.disconnect();

//   //Conectar a uma rede
//   Serial.print("Conectando");
//   int tentativa = 0;
//   WiFi.begin(ssid, pw);
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     tentativa++;

//     if(tentativa > 300)
//     {
//       return false;
//     }

//     Serial.print(".");
//     delay(200);
    
//   }
//   Serial.print("\nConectado com o IP: ");
//   Serial.println(WiFi.localIP());

//   return true;
// }

// //printar a mensagem que é recebida no topico.
// void callback(char* topic, byte* payload, unsigned int lenght)
// {
//   String message = "";

//   Serial.printf("Mensagem recebida no topico %s: ", topic);
  
//   for(int i = 0; i < lenght; i++)
//   {
//     Serial.print((char)payload[i]);
//     message += static_cast<char>(payload[i]);
//   }
//   Serial.println();

//   // verifica o codigo do MQTT é 100 ou 200 nos topicos certos e faz as func 

//   if ((strcmp(topic, "iiot-dta/avaliacao")) == 0 && message == "100")
//   {
//     digitalWrite(PIN_LED_03, HIGH);
//     FirebaseJson json;

//     /*---NTC10K_00---*/
//     uint16_t input_valueNTC_00 = analogRead(PIN_NTC_00);  
//     float voltageNTC_00 =  static_cast<float>(input_valueNTC_00) * VREF / static_cast<float>(ADC_MAX);

//       //Resistencia a partir da temperatura
//     float resistence_00 = R1 * voltageNTC_00 / (VREF - voltageNTC_00);

//     float temperature_00 = b * pow((log(resistence_00 - a)), 3) + c * pow((log(resistence_00 - a)), 2) + d *(log(resistence_00 - a)) + e;
    
//     /*---NTC10K_01---*/
//     uint16_t input_valueNTC_01 = analogRead(PIN_NTC_01);
//     float voltageNTC_01 =  static_cast<float>(input_valueNTC_01) * VREF / static_cast<float>(ADC_MAX);

//         //Resistencia a partir da temperatura
//     float resistence_01 = R1 * voltageNTC_01 / (VREF - voltageNTC_01);

//     float temperature_01 = b * pow((log(resistence_01 - a)), 3) + c * pow((log(resistence_01 - a)), 2) + d *(log(resistence_01 - a)) + e;

//     float mean = (temperature_00 + temperature_01) / 2;
//     float desvio = temperature_00 - temperature_01;
//     if(desvio < 0)
//     {
//       desvio = desvio * -1;
//     }

//     desvio = desvio / 1.414213;

//     json.set("/mean_temperature", mean);
//     json.set("/standard_deviation", desvio);

//     Serial.printf("NTC 1:\tADC %8i Voltage: %8.2f Resistence: %8.2f Temperature: %8.2f\n", input_valueNTC_00, voltageNTC_00, resistence_00, temperature_00);
//     Serial.printf("NTC 2:\tADC %8i Voltage: %8.2f Resistence: %8.2f Temperature: %8.2f\n", input_valueNTC_01, voltageNTC_01, resistence_01, temperature_01);
//     Serial.printf("Media: %f Desvio: %f\n", mean, desvio);
//     Serial.println();

//     /*---Enviar dados para o Firebase---*/
//     bool status = Firebase.updateNode(fbdo, "/avaliacao/subsys_04", json); 
    
//     if(!status) 
//     {
//       //Caso de algum erro para enviar o o json para o banco de dados, retorna o erro que aconteceu
//       Serial.println(fbdo.errorReason().c_str());
//     }
//     digitalWrite(PIN_LED_03, LOW);

//   }
// }



// /*---Setup---*/
// void setup() 
// {
//   pinMode(PIN_LED_00, OUTPUT);
//   pinMode(PIN_LED_01, OUTPUT);
//   pinMode(PIN_LED_02, OUTPUT);
//   pinMode(PIN_LED_03, OUTPUT);


//   pinMode(PIN_NTC_00, INPUT);
//   pinMode(PIN_NTC_01, INPUT);

//   pinMode(PIN_BOTAO, INPUT);

//   Serial.begin(115200);

//   connectWiFi(WIFI_SSID, WIFI_PW);

//   fbconfig.database_url = FB_HOST;
//   fbconfig.signer.tokens.legacy_token = FB_KEY;

//   fbdo.setBSSLBufferSize(4096, 1024);
//   Firebase.reconnectWiFi(true); // quando tentar acessar o banco e não tiver conectado na net ele conecta

//   Firebase.begin(&fbconfig, &fbauth);

//   //MQTT
//   mqtt_client.setServer(MQTT_BROKER, MQTT_PORT);
//   mqtt_client.setCallback(callback);

//   while(!mqtt_client.connected())
//   {
//     String client_id = "dts_esp32_yas";
//     client_id += String(WiFi.macAddress());

//     if(mqtt_client.connect(client_id.c_str(), MQTT_USERNAME, MQTT_PASSWORD))
//     {
//       Serial.println("Conexão MQTT bem sucedida");
//     }
//   }

//   //Receber informação
//   mqtt_client.subscribe("iiot-dta/avaliacao");
// }

// /*---Loop---*/
// void loop() 
// {
//   FirebaseJson json;

//   //Receber 
//   mqtt_client.loop();

//   /*---Botao---*/
//   button_state = digitalRead(PIN_BOTAO);


//   /*---NTC10K_00---*/
//   uint16_t input_valueNTC_00 = analogRead(PIN_NTC_00);  
//   float voltageNTC_00 =  static_cast<float>(input_valueNTC_00) * VREF / static_cast<float>(ADC_MAX);

//       //Resistencia a partir da temperatura
//   float resistence_00 = R1 * voltageNTC_00 / (VREF - voltageNTC_00);

//   float temperature_00 = b * pow((log(resistence_00 - a)), 3) + c * pow((log(resistence_00 - a)), 2) + d *(log(resistence_00 - a)) + e;

//   /*---NTC10K_01---*/
//   uint16_t input_valueNTC_01 = analogRead(PIN_NTC_01);
//   float voltageNTC_01 =  static_cast<float>(input_valueNTC_01) * VREF / static_cast<float>(ADC_MAX);

//       //Resistencia a partir da temperatura
//   float resistence_01 = R1 * voltageNTC_01 / (VREF - voltageNTC_01);

//   float temperature_01 = b * pow((log(resistence_01 - a)), 3) + c * pow((log(resistence_01 - a)), 2) + d *(log(resistence_01 - a)) + e;

//   float mean = (temperature_00 + temperature_01) / 2;
//   float desvio = temperature_00 - temperature_01;
//   if(desvio < 0)
//   {
//     desvio = desvio * -1;
//   }

//   desvio = desvio / 1.414213;

//   json.set("/mean_temperature", mean);
//   json.set("/standard_deviation", desvio);
  

//   if(mean >= 27)
//   {
//     digitalWrite(PIN_LED_00, HIGH);
//     digitalWrite(PIN_LED_01, HIGH);
//     digitalWrite(PIN_LED_02, HIGH);
//   }
//   else if(mean >= 24)
//   {
//     digitalWrite(PIN_LED_00, HIGH);
//     digitalWrite(PIN_LED_01, HIGH);
//     digitalWrite(PIN_LED_02, LOW);
//   }
//   else if(mean >= 21)
//   {
//     digitalWrite(PIN_LED_00, HIGH);
//     digitalWrite(PIN_LED_01, LOW);
//     digitalWrite(PIN_LED_02, LOW);
//   }
//   else
//   {
//     digitalWrite(PIN_LED_00, LOW);
//     digitalWrite(PIN_LED_01, LOW);
//     digitalWrite(PIN_LED_02, LOW);
//   }

//   if(button_state == HIGH)
//   { 
//     digitalWrite(PIN_LED_03, HIGH);
//     /*---Enviar dados para o Firebase---*/
//     bool status = Firebase.updateNode(fbdo, "/avaliacao/subsys_04", json); 
    
//     Serial.printf("NTC 1:\tADC %8i Voltage: %8.2f Resistence: %8.2f Temperature: %8.2f\n", input_valueNTC_00, voltageNTC_00, resistence_00, temperature_00);
//     Serial.printf("NTC 2:\tADC %8i Voltage: %8.2f Resistence: %8.2f Temperature: %8.2f\n", input_valueNTC_01, voltageNTC_01, resistence_01, temperature_01);
//     Serial.printf("Media: %f Desvio: %f\n", mean, desvio);
//     Serial.println();

//     if(!status) 
//     {
//       //Caso de algum erro para enviar o o json para o banco de dados, retorna o erro que aconteceu
//       Serial.println(fbdo.errorReason().c_str());
//     }
//     digitalWrite(PIN_LED_03, LOW);
//   }
// }
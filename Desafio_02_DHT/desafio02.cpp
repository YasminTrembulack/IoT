// /*---Includes---*/
// #include <WiFi.h>
// #include <Arduino.h>
// #include "PubSubClient.h"
// #include "DHT.h"
// #include <FirebaseESP32.h>

// /*---Hardware mapping---*/
// const uint8_t PIN_INPUT = 33;
// const uint8_t PIN_LED = 32;

// /*---Constants---*/
// #define DHTTYPE DHT11 //dht

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
// DHT dht(PIN_INPUT, DHTTYPE);//dht

// FirebaseData fbdo; //informações do banco de dados
// FirebaseAuth fbauth; //metodo de autenticação
// FirebaseConfig fbconfig; 

// long tempo = 0;
// long tempo_led = 0;


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

//   if ((strcmp(topic, "iiot-dta/check")) == 0)
//   {
//     if (message == "100")
//     {
//       mqtt_client.publish("iiot-dta/check", "1 y");
//     }
//     if (message == "200")
//     {
//       digitalWrite(PIN_LED, HIGH);
//       tempo_led = millis();
//     }
//   }
//   if ((strcmp(topic, "iiot-dta/request")) == 0)
//   {
//     if (message == "100")
//     {
//       FirebaseJson json;

//       /*---DHT---*/
//       float humidade = dht.readHumidity();
//       float temperatura = dht.readTemperature();
//       if(isnan(humidade) || isnan(temperatura))
//       {
//         Serial.println("Falha na leitura do sensor DHT.");
//         return;
//       }

//       if(temperatura > 30)
//       {
//         mqtt_client.publish("iiot-dta/request", "10 y");
//       }

//       json.set("/temperature", temperatura);
//       json.set("/humidity", humidade);
  
//       /*---Enviar dados para o Firebase---*/
//       bool status = Firebase.updateNode(fbdo, "/challenge02/subsys_04", json); 
  
//       if(!status) 
//       {
//         //Caso de algum erro para enviar o o json para o banco de dados, retorna o erro que aconteceu
//         Serial.println(fbdo.errorReason().c_str());
//       }
//     }
//   }
// }



// /*---Setup---*/
// void setup() 
// {
//   dht.begin();//dht

//   pinMode(PIN_LED, OUTPUT);

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
//   mqtt_client.subscribe("iiot-dta/check");
//   mqtt_client.subscribe("iiot-dta/request");
// }

// /*---Loop---*/
// void loop() 
// {
//   FirebaseJson json;

//   //Receber 
//   mqtt_client.loop();

//   /*---DHT---*/
//     float humidade = dht.readHumidity();
//     float temperatura = dht.readTemperature();

//     if(isnan(humidade) || isnan(temperatura))
//     {
//       Serial.println("Falha na leitura do sensor DHT.");
//       return;
//     }

//     if(temperatura > 30)
//     {
//       mqtt_client.publish("iiot-dta/request", "10 y");
//     }

//   if((millis() - tempo_led) > 5000)
//   {
//     digitalWrite(PIN_LED, LOW);
//     tempo_led = millis();
//   }

//   if((millis() - tempo) > 30000 )
//   {  
//     Serial.printf("Humidade: %4.2f Temperatura: %7.2f\n\n", humidade, temperatura);

//     json.set("/temperature", temperatura);
//     json.set("/humidity", humidade);
    
//     /*---Enviar dados para o Firebase---*/
//     bool status = Firebase.updateNode(fbdo, "/challenge02/subsys_04", json); 
    
//     if(!status) 
//     {
//       //Caso de algum erro para enviar o o json para o banco de dados, retorna o erro que aconteceu
//       Serial.println(fbdo.errorReason().c_str());
//     }

//     tempo = millis();
//   }
// }
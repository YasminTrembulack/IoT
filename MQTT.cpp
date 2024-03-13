// /*---Includes---*/
// #include <WiFi.h>
// #include<Arduino.h>
// #include "PubSubClient.h"

// /*---Constants---*/
// const char* WIFI_SSID = "belisarius";
// const char* WIFI_PW = "senhaaaa";

// const char* MQTT_BROKER = "test.mosquitto.org";
// const uint16_t MQTT_PORT = 1883;
// const char* MQTT_USERNAME = "";
// const char* MQTT_PASSWORD = "";

// /*---Variables---*/
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
//   Serial.printf("Mensagem recebida no topico %s:\n", topic);
  
//   for(int i = 0; i < lenght; i++)
//   {
//     Serial.print((char)payload[i]);
//   }
//   Serial.println();
// }

// /*---Hardware mapping---*/

// /*---Setup---*/
// void setup()
// {
//   Serial.begin(115200);
//   connectWiFi(WIFI_SSID, WIFI_PW);
//   // MQTT
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
//   mqtt_client.subscribe("testdta");
// }

// /*---Loop---*/
// void loop()
// {
//   //Enviar informação
//   mqtt_client.publish("testdta","olaaaaaa!!!");

//   //Receber 
//   mqtt_client.loop();

//   delay(5000);

// }
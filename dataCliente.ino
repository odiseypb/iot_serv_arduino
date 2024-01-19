
#include <ArduinoJson.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

//declarar las credenciales de la red -- DOIT ESP32 DEVKIT v1 --ESPRESSIF
const char* ssid = "who";
const char* password = "87654320";
//declarar la ip del servidor Web (La que nos va a dar flask)
const char* server_address = "http://192.11.21.47:8090/sensor";

void setup() {
  /*Inicia la velocidad de transmisión de datos 115200 bits
  por segundo*/
  
  Serial.begin(115200);
  //Inicia la conexión
  WiFi.begin(ssid, password);
  //Intentar conectarse cada segundo si el estatus de la WiFi es dif conectado
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println(WiFi.localIP());
  
}

void loop() {
  // Obtener los datos que se quieren enviar al servidor
  String sensor = "DHT11";
  float temperatura= 23.50;
  float humedad= 85.50;
 
  //Crear objeto de cliente
  WiFiClient client;
  // Crear una solicitud HTTP POST con los datos
  HTTPClient http;
  
  http.begin(client, server_address);
 
  http.addHeader("Content-Type", "application/json");
  http.POST("{\"sensor\":\"" + sensor + "\", \"temp\":\"" + temperatura + "\", \"hum\":\"" + humedad + "\"}");
  
  // Obtener la respuesta del servidor
  String response = http.getString();
  Serial.println(response);
  
  // Esperar antes de enviar nuevos datos
  delay(1000);
}

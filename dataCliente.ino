#include <ArduinoJson.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

// Declarar las credenciales de la red -- DOIT ESP32 DEVKIT v1 --ESPRESSIF
const char* ssid = "who";
const char* password = "0987654321";
// Declarar la IP del servidor Web (La que nos va a dar Flask)
const char* server_address = "http://192.168.181.183:3500/sensor";

void setup() {
  // Inicia la velocidad de transmisión de datos 115200 bits por segundo
  Serial.begin(115200);

  // Inicia la conexión WiFi
  WiFi.begin(ssid, password);

  // Intentar conectarse cada segundo si el estatus de la WiFi es diferente de conectado
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la WiFi...");
  }

  Serial.println(WiFi.localIP());
}

void loop() {
  // Datos que se quieren enviar al servidor
  const char* sensor = "DHT11";
  float temperatura = 23.50;
  float humedad = 85.50;

  // Crear objeto de cliente y solicitud HTTP POST
  WiFiClient client;
  HTTPClient http;
  http.begin(client, server_address);

  // Crear y enviar JSON
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["sensor"] = sensor;
  jsonDoc["temp"] = temperatura;
  jsonDoc["hum"] = humedad;

  String estructura_solicitud;
  serializeJson(jsonDoc, estructura_solicitud);

  http.addHeader("Content-Type", "application/json");
  int codigo_respuesta_http = http.POST(estructura_solicitud);

  // Obtener y mostrar la respuesta del servidor
  if (codigo_respuesta_http > 0) {
    String respuesta = http.getString();
    Serial.println(respuesta);
  } else {
    Serial.println("Error en la solicitud HTTP");
  }

  // Cerrar conexión
  http.end();

  // Esperar antes de enviar nuevos datos
  delay(10000);
}

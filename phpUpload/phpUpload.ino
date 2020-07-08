#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "ppp";
const char* password = "0000003940";
String SERVER = "192.168.43.87";
String host = "/insert_data.php?temp=10";

WiFiServer server(80);
WiFiClient client;
HTTPClient http;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
}

void loop() {
  WiFiClient client;

  if (client.connect(SERVER, 80))
  {
    client.print(String("GET ") + host + " HTTP/1.1\r\n" +
    "Host: " + SERVER + "\r\n" +
    "Connection: close\r\n\r\n");
  }

  delay(1000);
}

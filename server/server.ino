// script ESP8266 sebagai server
#include <ESP8266WiFi.h>

#define LED 14
const char* ssid = "SYKRNDPFF"; // Nama AP/Hotspot
const char* password = "bayardulu"; // Password AP/Hotspot

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  // Mengatur WiFi ----------------------------------------------------------
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.mode(WIFI_AP); // Mode AP/Hotspot
  WiFi.softAP(ssid, password);
  // Start the server -------------------------------------------------------
  server.begin();
  Serial.println("Server dijalankan");
  // Print the IP address ---------------------------------------------------
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  // Wait untilthe client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }
  // Read the first line of the request -------------------------------------
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  //Command LED -------------------------------------------------------------
  if (req.indexOf("LED ON") != -1) {
    digitalWrite(LED, HIGH);
  }
  else if (req.indexOf("LED OFF") != -1) {
    digitalWrite(LED, LOW);
  }
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }
  client.flush();
  Serial.println("Client disonnected");
  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
}

// program code created
// by Ferdian Firmansyah

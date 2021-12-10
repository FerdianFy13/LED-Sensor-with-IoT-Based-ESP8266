// import library 
#include <ESP8266WiFi.h>

// script ESP8266 sebagai client
#define button 5 // ded
const char* ssid = "SYKRNDPFF"; // Nama SSID AP/Hotspot
const char* password = "bayardulu"; // Password Wifi
const char* host = "192.168.0.102"; // IPAdrress Lenovo Server
int buttonstate = 0; // sensor initialization pushbutton

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  pinMode(button, INPUT);
  // Connect to WiFi network ------------------------------------------------
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  // Mengatur WiFi ----------------------------------------------------------
  WiFi.mode(WIFI_STA); // Mode Station
  WiFi.begin(ssid, password); // MencocokanSSID dan Password
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print status Connect ---------------------------------------------------
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IPaddress: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //put your main code here, to run repeatedly:
  buttonstate = digitalRead(button);

  //  create a URL to connect to the server
  const char* url;
  if (buttonstate == LOW) {
    url = "LED OFF";
  }
  else {
    url = "LED ON";
  }
  int value = 0;
  delay(1000);
  ++value;
  Serial.print("connecting to ");
  Serial.println(host);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  // We now create a URI for the request
  Serial.print("Requesting URL: ");
  Serial.println(url);
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if
    (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  // Read allthe lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");
}

// program code created
// by Ferdian Firmansyah

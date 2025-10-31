#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>

const char* ssid = "htamsah";
const char* password = "17081973";

WebServer server(80);

//Pin Segmen
const int segPins[] = {14, 27, 26, 25, 33, 32, 13}; // a,b,c,d,e,f,g

// Pola angka 0–9 (common cathode)
const byte numbers[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

void displayNumber(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], numbers[num][i]);
  }
}

void handleRoot() {
  File file = LittleFS.open("/index.html", "r");
  server.streamFile(file, "text/html");
  file.close();
}

void handleStyle() {
  File file = LittleFS.open("/style.css", "r");
  server.streamFile(file, "text/css");
  file.close();
}

void handleNumber() {
  if (server.hasArg("value")) {
    int num = server.arg("value").toInt();
    if (num >= 0 && num <= 9) {
      displayNumber(num);
      server.send(200, "text/plain", "OK");
    } else {
      server.send(400, "text/plain", "Nilai tidak valid");
    }
  } else {
    server.send(400, "text/plain", "Parameter 'value' tidak ditemukan");
  }
}

void setup() {
  Serial.begin(115200);

  // Setup pin
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
    digitalWrite(segPins[i], LOW);
  }

  // Mount filesystem
  if (!LittleFS.begin(true)) {
    Serial.println("Gagal mount LittleFS!");
    return;
  }

  // WiFi connect
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nTerhubung ke WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/style.css", handleStyle);
  server.on("/number", handleNumber);
  server.begin();
  Serial.println("Web server dimulai!");
}

void loop() {
  server.handleClient();
}

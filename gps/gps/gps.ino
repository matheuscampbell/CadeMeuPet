#include <Arduino.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#define GPS_RX 33
#define GPS_TX 26
#define GPS_Serial_Baud 9600

bool isWIFIConnected;
WiFiMulti WiFiMulti;

// The serial connection to the GPS device
SoftwareSerial gpsSerial(GPS_RX, GPS_TX);
TinyGPSPlus gps;
HTTPClient http;
void setup()
{
  Serial.begin(115200); // Beginning the serial monitor at Baudrate 115200 and make sure you select same in serial monitor
  gpsSerial.begin(GPS_Serial_Baud);



  isWIFIConnected = false;
  WiFiMulti.addAP("LAPTOP", "12345678");

  Serial.println();
  Serial.println();
  Serial.print("Waiting for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);
  isWIFIConnected = true;


}
void loop()
{
  //Mostra os dados crus do GPS
  while (gpsSerial.available() > 0)
  {
    if (gps.encode(gpsSerial.read())) {
      displayInfo();
      if (true) {
        http.begin("http://192.168.18.4:3000/api/setLocation/"+(String)gps.location.lat()+"/"+(String)gps.location.lng());
        Serial.print("[HTTP] GET...\n");
        int httpCode = http.GET();
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        String payload = http.getString();
        Serial.println(payload);
        http.end();
      }else{
        Serial.println("Erro, wifi desconectado.");
      }
      delay(1000);
    }
    if (millis() > 6000 && gps.charsProcessed() < 10)
    {
      Serial.println(F("No GPS detected: check wiring."));
    }
  }
}

void displayInfo() {
  Serial.print(F("Location: "));
  if (true) {
    Serial.print("Lat: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print("Lng: ");
    Serial.print(gps.location.lng(), 6);
    Serial.print("N SAT: ");
    Serial.print(gps.satellites.value());
    Serial.println();
  }
  else {
    Serial.print(F("INVALID"));
  }
}

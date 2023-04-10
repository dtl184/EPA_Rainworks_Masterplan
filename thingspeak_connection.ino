
#include "ThingSpeak.h"


unsigned long myChannelNumber = 2026236;
const char * myWriteAPIKey = "I1ZT1SAD4N2PQF0Q";

#include <ESP8266WiFi.h>

char ssid[] = "vuDevices";   // your network SSID (name)
char pass[] = "Acorn1873";   // your network password
int keyIndex = 0;            // your network key index number (needed only for WEP)
WiFiClient  client;

void setup() {
  Serial.begin(115200);
  delay(100);
//  pinMode(13, OUTPUT)

  WiFi.mode(WIFI_STA);

  ThingSpeak.begin(client);
}

void loop() {



  // Connect or reconnect to WiFi
  Serial.print("Print this");
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    //Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }

  // Measure Analog Input (A0)
  int valueA0 = analogRead(A0);

  // Write value to Field 1 of a ThingSpeak Channel
  int httpCode = ThingSpeak.writeField(myChannelNumber, 1, valueA0, myWriteAPIKey);

  if (httpCode == 200) {
    Serial.println("Channel write successful.");
  }
  else {
    Serial.println("Problem writing to channel. HTTP error code " + String(httpCode));
  }

  // Wait 20 seconds to update the channel again
  delay(5000);
}

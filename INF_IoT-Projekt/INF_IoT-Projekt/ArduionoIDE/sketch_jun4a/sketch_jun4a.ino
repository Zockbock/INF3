#include <WiFiNINA.h>
#include <ArduinoMqttClient.h>

#define WIFI_SSID       "your_network_ssid"
#define WIFI_PASS       "your_network_password"

#define MQTT_SERVER     "your_mqtt_server_address"
#define MQTT_PORT       your_mqtt_server_port
#define MQTT_USERNAME   "your_mqtt_username"
#define MQTT_PASSWORD   "your_mqtt_password"

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

// Definieren Sie Ihre MQTT-Topics und Rückruffunktionen hier

void setup() {
  // Starten Sie die serielle Kommunikation
  Serial.begin(9600);

  // Verbinden Sie das WLAN
  while (WiFi.begin(WIFI_SSID, WIFI_PASS) != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Verbinden Sie den MQTT-Server
  connectToMQTT();
}

void loop() {
  // Halten Sie die Verbindung zum MQTT-Server aufrecht
  if (!mqttClient.connected()) {
    connectToMQTT();
  }

  // Führen Sie MQTT-Schleifenfunktionen aus
  mqttClient.loop();

  // Fügen Sie hier Ihren eigenen Code hinzu
}

void connectToMQTT() {
  Serial.print("Connecting to MQTT server...");

  while (!mqttClient.connected()) {
    if (mqttClient.connect(MQTT_SERVER, MQTT_PORT)) {
      Serial.println("Connected to MQTT server.");

      // Abonnieren Sie Ihre MQTT-Topics hier

    } else {
      Serial.print("Failed to connect to MQTT server. Trying again in 5 seconds...");
      delay(5000);
    }
  }
}
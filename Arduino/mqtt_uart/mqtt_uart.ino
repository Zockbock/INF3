#include <HardwareSerial.h>
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

#define SPIWIFI       SPI  // The SPI port
#define SPIWIFI_SS    10   // Chip select pin
#define ESP32_RESETN  5    // Reset pin
#define SPIWIFI_ACK   7    // a.k.a BUSY or READY pin
#define ESP32_GPIO0   -1

// values for UART communication:
unsigned char currentMode = 'i'; // a = audio, i = illuminence
unsigned char audio = 'a';
unsigned char illuminence = 'i';
unsigned char illuminenceData;
unsigned char audioData;
unsigned char mode;
unsigned char percentage = 0;
unsigned char nextPercentage= 0;

unsigned char modeChange = 0;
unsigned char changeIndicator = 105;

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID
char pass[] = SECRET_PASS;    // your network password

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "test.mosquitto.org";
int        port     = 1883;
const char topic2publish[]  = "room_illuminence";
const char topic2publish2[]  = "room_volume";
const char topic2subscribe[]  = "led_percentage";
const char topic2subscribe2[]  = "led_mode";

// ------------------- [PUBLISHER] ---------------
//set interval for sending messages (milliseconds)
const long interval = 8000;
unsigned long previousMillis = 0;

int count = 0;

void setup() {

  // ------------------- [SUBSCRIBER] ---------------
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  // ------------------- [SUBSCRIBER] ---------------
  // set the message receive callback
  mqttClient.onMessage(onMqttMessage);

  Serial.print("Subscribing to topic: ");
  Serial.println(topic2subscribe);
  Serial.println();
  mqttClient.subscribe(topic2subscribe);

  Serial.print("Subscribing to topic: ");
  Serial.println(topic2subscribe2);
  Serial.println();
  mqttClient.subscribe(topic2subscribe2);

  // topics can be unsubscribed using:
  // mqttClient.unsubscribe(topic);

  Serial.print("Topic (Subscribe): ");
  Serial.println(topic2subscribe);
  Serial.print("Topic (Subscribe): ");
  Serial.println(topic2subscribe2);

  Serial.println();
  // ------------------- [SUBSCRIBER] ---------------
}

void loop() {
  // ------------------- [SUBSCRIBER] ---------------
  // call poll() regularly to allow the library to receive MQTT messages and
  // send MQTT keep alive which avoids being disconnected by the broker
  mqttClient.poll();
  // ------------------- [SUBSCRIBER] ---------------
  // ------------------- [UART] ---------------
  if (Serial.available())
  {
    unsigned char receivedData = Serial.read();

    // Do something with received data
    if(currentMode == illuminence){
      illuminenceData = receivedData;
    } else { // currentMode == audio
      audioData = receivedData;
    }
    if(Serial.availableForWrite()){
    if(modeChange){
      Serial.write(changeIndicator);
      modeChange = 0;
      Serial.print("uart transmit m: ");
      Serial.println(currentMode);
    } else {
      Serial.write(percentage);
      Serial.print("uart transmit p: ");
      Serial.println(percentage);
    }
  }
    //Serial.write(currentMode);
  }
  
  // ------------------- [UART] ---------------

  // ------------------- [PUBLISHER] ---------------
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time a message was sent
    previousMillis = currentMillis;

    if(currentMode == illuminence){
      mqttClient.beginMessage(topic2publish);
      mqttClient.print(illuminenceData);
      mqttClient.endMessage();
      Serial.print("published illuminence data: ");
      Serial.println(illuminenceData);
    } else { // currentMode == audio
      mqttClient.beginMessage(topic2publish2);
      mqttClient.print(audioData);
      mqttClient.endMessage();
      Serial.print("published audio data: ");
      Serial.println(audioData);
    }
    Serial.println();
  }
  // ------------------- [PUBLISHER] ---------------
}

// ------------------- [SUBSCRIBER] ---------------
void onMqttMessage(int messageSize) {
  // we received a message, print out the topic and contents
  Serial.println("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  // use the Stream interface to print the contents
  while (mqttClient.available()) {
    if(mqttClient.messageTopic() == "led_percentage"){ 
      nextPercentage = (unsigned char)mqttClient.read();
      checkPercentage(nextPercentage);
    }
    if(mqttClient.messageTopic() == "led_mode"){
      mode = (unsigned char)mqttClient.read();
      checkMode(mode);
    }
  }
  Serial.println();
  Serial.println();
}
// ------------------- [SUBSCRIBER] ---------------

 void checkPercentage(unsigned char p){
  if(p != percentage){
    percentage = p;
    Serial.print("updated percentage value: ");
    Serial.println(percentage);
  } else {
    Serial.println("same percentage value transmitted");
  }
}

void checkMode(unsigned char m){
  if(m != currentMode){
    if(m != audio && m != illuminence){
    } else {
      currentMode = m;
      modeChange = 1;
      Serial.print("updated mode (modeChange was set to 1): ");
      Serial.println(currentMode);
    }
  } else {
    Serial.println("same mode transmitted");
  }
}
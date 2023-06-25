#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

// values for UART communication:
unsigned char currentMode = 'i'; // a = audio, i = illuminence
unsigned char audio = 'a';
unsigned char illuminence = 'i';
unsigned char mode;
unsigned char percentage = 0;
unsigned char nextPercentage;
unsigned char sensorValue = 0;

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

  // ------------------- [UART] ---------------
  if (Serial.available())
  {
    unsigned char receivedData = Serial.read();
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      // save the last time a message was sent
      previousMillis = currentMillis;

      // Do something with received data
      if(currentMode == illuminence){
        mqttClient.beginMessage(topic2publish);
        mqttClient.print(receivedData);
        mqttClient.endMessage();
      } else { // currentMode == audio
        mqttClient.beginMessage(topic2publish2);
        mqttClient.print(receivedData);
        mqttClient.endMessage();
      }
    }
    // ...

    Serial.write(receivedData);
  }
  // ------------------- [UART] ---------------

  // ------------------- [SUBSCRIBER] ---------------
  // call poll() regularly to allow the library to receive MQTT messages and
  // send MQTT keep alive which avoids being disconnected by the broker
  mqttClient.poll();
  // ------------------- [SUBSCRIBER] ---------------
  // ------------------- [PUBLISHER] ---------------
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time a message was sent
    previousMillis = currentMillis;

    /*
    //record random value from A0, A1 and A2
    int Rvalue = analogRead(A0);
    int Rvalue2 = analogRead(A1);
  
    Serial.print("Sending message to topic: ");
    Serial.println(topic2publish);
    Serial.println(Rvalue);

    Serial.print("Sending message to topic: ");
    Serial.println(topic2publish2);
    Serial.println(Rvalue2);
    */  
    // send message, the Print interface can be used to set the message contents
    /*
    mqttClient.beginMessage(topic2publish);
    mqttClient.print(Rvalue);
    mqttClient.endMessage();

    mqttClient.beginMessage(topic2publish2);
    mqttClient.print(Rvalue2);
    mqttClient.endMessage();
    */
    Serial.println();
  }
  // ------------------- [PUBLISHER] ---------------
  checkMode(mode);
  Serial.print("Mode: ");
  Serial.println(currentMode);
  checkPercentage(nextPercentage);
  Serial.print("Percentage: ");
  Serial.println(percentage);
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
    }
    if(mqttClient.messageTopic() == "led_mode"){
      mode = (unsigned char)mqttClient.read();
    }
  }
  Serial.println();
  Serial.println();
}
// ------------------- [SUBSCRIBER] ---------------

void checkPercentage(unsigned char p){
  if(p != percentage){
    percentage = p;
  } else {
    Serial.print("no significant change, last transmitted percentage-value: ");
    Serial.println(percentage);
  }
}

void checkMode(unsigned char m){
  if(m != currentMode){
    if(m != audio && m != illuminence){
      Serial.print("no such mode");
    } else {
      currentMode = m;
    }
  } else {
    if(m != audio && m != illuminence){
      Serial.print("no such mode");
    } else {
      Serial.print("allready in mode: ");
      Serial.println(currentMode);
    }
  }
}
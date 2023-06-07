#include <SoftwareSerial.h>

#define rxPin 0
#define txPin 1

SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin); // RX, TX

void setup() {
  // Begin serial communication
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);



  // Transmit 'A' character
  //mySerial.write(42);
}

void loop() {
  mySerial.write(42);
 
  //Serial.println(mySerial.isListening());
  //Serial.println(mySerial.available());

  if (mySerial.available() > 0) {
    // Read data from the software serial
    char receivedData = mySerial.read();

    // Process received data as needed
    // ...

    mySerial.write(42);

    // Transmit the received data back
    mySerial.write(receivedData);
  }
}

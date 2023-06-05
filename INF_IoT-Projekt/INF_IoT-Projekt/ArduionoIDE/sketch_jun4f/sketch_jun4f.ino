#include <SoftwareSerial.h>

SoftwareSerial mySerial(1, 2); // RX, TX

void setup() {
  // Begin serial communication
  Serial.begin(9600);
  mySerial.begin(9600);

  // Transmit 'A' character
  mySerial.write(42);
}

void loop() {
  mySerial.write(42);
  if (mySerial.available()) {
    // Read data from the software serial
    char receivedData = mySerial.read();

    // Process received data as needed
    // ...

    mySerial.write("test");

    // Transmit the received data back
    mySerial.write(receivedData);
  }
}

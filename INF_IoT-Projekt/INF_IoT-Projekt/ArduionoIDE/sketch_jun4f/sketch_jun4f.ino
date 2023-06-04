#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
  // Begin serial communication
  Serial.begin(9600);
  mySerial.begin(9600);

  // Transmit 'A' character
  mySerial.write('A');
}

void loop() {
  if (mySerial.available()) {
    // Read data from the software serial
    char receivedData = mySerial.read();

    // Process received data as needed
    // ...

    // Transmit the received data back
    mySerial.write(receivedData);
  }
}

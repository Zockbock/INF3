#include <HardwareSerial.h>

//#define rxPin 19
//#define txPin 18
#define FOSC 16000000UL  // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

//HardwareSerial SerialTFMini(1);
//HardwareSerial SerialBrain(2);

//HardwareSerial mySerial = HardwareSerial(); // RX, TX

int receivedData;

void setup() {
  // Begin serial communication
  Serial.begin(BAUD);
  Serial1.begin(BAUD);
  //mySerial.begin(MYUBRR);

  //pinMode(rxPin, INPUT);
  //pinMode(txPin, OUTPUT);



  // Transmit 'A' character
  //mySerial.write(42);
}

void loop() {

  receivedData = Serial1.read();
  Serial.println((char)receivedData);
 
  /**
  if (Serial1.available() > 0) {
    // Read data from the software serial


    // Process received data as needed
    // ...

    // Transmit the received data back
  }
  **/
}

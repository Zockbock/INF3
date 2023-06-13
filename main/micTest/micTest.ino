/***************************
  Simple Example Sketch for the SparkFun MEMS Microphone Breakout Board

**************************/

// Connect the MEMS AUD output to the Arduino A0 pin
int mic = A0;

// Variable to hold analog values from mic
int micOut;
int db;

void setup() {
  Serial.begin(9600);

}

void loop() {
  // read the input on analog pin 0:
  micOut = analogRead(mic);

  db = (micOut + 83.2073) / 11.003;
  // print out the value you read:
  Serial.println(db);

  //delay(10);

}
unsigned char audio = 'a';
unsigned char illuminence = 'i';
unsigned char currentMode = illuminence;
unsigned char mode;

void setup() {
  Serial.begin(9600);
  Serial.println("--->");
  Serial.println(currentMode);
  mode = 'a';
  if(mode != currentMode){
    currentMode = mode;
  } else {

  }
  Serial.println(currentMode);
  Serial.println(audio);
  Serial.println(illuminence);
  Serial.println("--->");
  

}

void loop() {
  // put your main code here, to run repeatedly:

}

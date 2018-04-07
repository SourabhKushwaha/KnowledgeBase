short int incomingByte  = 0;   // for incoming serial data
short int outLEDPin     = LED_BUILTIN;
short int inPin         = 7;     // pushbutton connected to digital pin 7
int val                 = 0;       // variable to store the read value
short int counter       = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Started Listening");  
  pinMode(outLEDPin, OUTPUT); // initialize digital pin LED_BUILTIN as an output.
  pinMode(inPin, INPUT);        // sets the digital pin 7 as input
}

void serialReadEvent() {
   // send data only when you receive data:
        if (Serial.available() > 0) {
                incomingByte = Serial.read(); // read the incoming byte:
             
                Serial.print(incomingByte, DEC);
                Serial.print(",");

                if(incomingByte == 115) {
                  glowLED(1000);
                }
        }
}

void glowLED(int t) {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(t);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
}

// the loop function runs over and over again forever
void loop() {
  counter++;
  unsigned long currentMillis = millis();
  serialReadEvent();

  if(counter == 1000) {
    counter = 0;
    val = digitalRead(inPin);     // read the input pin
    Serial.println(val);
  }  

  delay(1);
}

int incomingByte = 0;   // for incoming serial data
int outLEDPin = LED_BUILTIN;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Started Listening");  
  pinMode(outLEDPin, OUTPUT); // initialize digital pin LED_BUILTIN as an output.
}
void serialReadEvent()
{
   // send data only when you receive data:
        if (Serial.available() > 0) {
                incomingByte = Serial.read(); // read the incoming byte:
             
                Serial.print(incomingByte, DEC);
                Serial.print(",");

                if(incomingByte == 115){
                  glowLED(1000);
                }
        }
}

void glowLED(int t){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(t);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
}

// the loop function runs over and over again forever
void loop() {
  serialReadEvent();
  /*Serial.println("1234");
  glowLED(1000);
  delay(1000);                       // wait for a second*/
}

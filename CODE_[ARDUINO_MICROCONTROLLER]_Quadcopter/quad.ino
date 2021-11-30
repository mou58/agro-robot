     
/*
 RC PulseIn Serial Read out
 By: Nick Poole
 SparkFun Electronics
 Date: 5
 License: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute. Let me know if you make hugely, awesome, great changes.
 */
 
int ch1; // Here's where we'll keep our channel values

void setup() {

  pinMode(12, INPUT); // Set our input pins as such
pinMode(11, OUTPUT); // Set our input pins as suchSerial
Serial.begin(9600);
}

void loop() {

  ch1 = pulseIn(12, HIGH, 25000); // Read the pulse width of 
  Serial.println(ch1);
 if(ch1>1200){
  digitalWrite(11,HIGH);
 }
 else if(ch1<1200&&ch1>0){
  digitalWrite(11,LOW);
 }
}

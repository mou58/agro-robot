#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8);
RF24 radio1(5, 6);
const byte rxAddr[6] = "00001";
const byte rxAddr1[6] = "00002";
int dd;
int motor=4;
void setup() {
 radio.begin();
  radio.openReadingPipe(0, rxAddr); 
  radio.startListening();
  delay(2000);
  radio1.begin();
  radio1.setRetries(15, 15);
  radio1.openWritingPipe(rxAddr1);
  radio1.stopListening();
  delay(2000); // put your setup code here, to run once:int 
  
  pinMode(motor, OUTPUT);
}

void loop() {
   while (radio.available())
{
  char data;
  radio.read(&data, sizeof(data));
  if(data=='L'){
 int soil = analogRead(A0); 
 unsigned int moister=map(soil, 515, 1023, 100, 0);
radio1.write(&moister , sizeof(unsigned int) );
}
else if(data=='M'){
  dd=1;
  while(dd){
   while( radio.available() )
    {
      unsigned int d;
       radio.read( &d, sizeof(unsigned int) );
         if(d==0){
     dd=0;
   }
     if(d>0){
   digitalWrite(motor, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(d);              // wait for a second
  digitalWrite(motor, LOW); 
   dd=0;
     }
    
}
  }
 } 
} // put your main code here, to run repeatedly:

}

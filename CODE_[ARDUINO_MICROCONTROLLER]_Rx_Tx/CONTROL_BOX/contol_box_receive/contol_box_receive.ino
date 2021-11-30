#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(5, 6);
RF24 radio1(7, 8);
const byte rxAddr1[6] = "00002";
const byte rxAddr[6] = "00001";
unsigned int ee=0;
int xx=0;
int d=0;
void setup() {
  Serial.begin(9600);
  radio1.begin();
  radio1.openReadingPipe(0, rxAddr1); 
  radio1.startListening();
delay(2000);
radio.begin();
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);
  radio.stopListening();
delay(2000);
}

void loop() {
   while (Serial.available()>0)
{
  char data=Serial.read();
  if(data=='F'){
    char text[] = "F";
  radio.write(&text, sizeof(text));
  }
   else if(data=='G'){
    char text[] = "G";
  radio.write(&text, sizeof(text));
  }
   else if(data=='L'){
    char text[] = "L";
  radio.write(&text, sizeof(text));
  }
   else if(data=='M'){
   radio.write(&ee , sizeof( unsigned int) );
   delay(200);
    char text[] = "M";
  radio.write(&text, sizeof(text));
   xx=1;
  while(xx){
   while (Serial.available()>0){
    //int send
    d=Serial.parseInt();
         if(d>0){
          unsigned int dd= d;
radio.write(&dd , sizeof( unsigned int) );
delay(300);
     xx=0;
   }
   }
  }
 }
}
while( radio1.available() )
    {
      // Dump the payloads until we've gotten everything
      unsigned int message;
        // Fetch the payload, and see if this was the last one.
       radio1.read( &message, sizeof(unsigned int) );
         Serial.print(message);
    }
}

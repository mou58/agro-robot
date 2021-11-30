#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
int xx=0;
int yy=0;
int d=0;
int c=0;
int joy0=A0;
int joy1=A1;
int MODE=2;
int state=0;
int flag=0;
unsigned int ee=0;
RF24 radio(7, 8);
const byte rxAddr[6] = "00001";
void setup() {
  Serial.begin(9600);
  pinMode(joy0, INPUT);
   pinMode(joy1, INPUT);
   pinMode(MODE, INPUT);
  //radio setup
 radio.begin();
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);
  radio.stopListening();
delay(2000);
}

void loop() {
 state = digitalRead(MODE);
  if(state==1){
     int forw= analogRead(joy0); 
     int lef=analogRead(joy1);
    if(forw>600&&flag==1){     
   char text[] = "A";
  radio.write(&text, sizeof(text));
  // put your main code here, to run repeatedly:
  flag=0;
  }
  else if(forw<490&&flag==1){
     char text[] = "B";
  radio.write(&text, sizeof(text));
  flag=0;
  }
  else if(lef>600&&flag==1){
     char text[] = "C";
  radio.write(&text, sizeof(text));
  flag=0;
  }
   else if(lef<490&&flag==1){
    const char text[] = "D";
  radio.write(&text, sizeof(text));
  flag=0;
  }
   else if(forw>500&&forw<600&&lef>500&&forw<600&&flag==0){
    char text[] = "E";
  radio.write(&text, sizeof(text));
  flag=1;
  }
  }
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
     else if(data=='H'){
    char text[] = "H";
  radio.write(&text, sizeof(text));
  }
     else if(data=='I'){
    char text[] = "I";
  radio.write(&text, sizeof(text));
  }
     else if(data=='J'){
    char text[] = "J";
  radio.write(&text, sizeof(text));
  }
     else if(data=='K'){
    char text[] = "K";
  radio.write(&text, sizeof(text));
  }
     else if(data=='L'){
    char text[] = "L";
  radio.write(&text, sizeof(text));
  }
     else if(data=='M'){
    char text[] = "M";
  radio.write(&text, sizeof(text));
  }
     else if(data=='N'){
    char text[] = "N";
  radio.write(&text, sizeof(text));
  }
     else if(data=='O'){
    char text[] = "O";
  radio.write(&text, sizeof(text));
  }
     else if(data=='P'){
    char text[] = "P";
  radio.write(&text, sizeof(text));
  }
     else if(data=='K'){
    char text[] = "K";
  radio.write(&text, sizeof(text));
  }
       else if(data=='Q'){
    char text[] = "Q";
  radio.write(&text, sizeof(text));
  }
       else if(data=='R'){
    char text[] = "R";
  radio.write(&text, sizeof(text));
  }
       else if(data=='S'){
    char text[] = "S";
  radio.write(&text, sizeof(text));
  }
       else if(data=='T'){
    char text[] = "T";
  radio.write(&text, sizeof(text));
  }
       else if(data=='W'){
    char text[] = "W";
  radio.write(&text, sizeof(text));
  }
  //send fruit position to x axis
         else if(data=='X'){
   radio.write(&ee , sizeof( unsigned int) );
   delay(200);
    char text[] = "X";
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
 //send fruit position send to y axis 
     else if(data=='Y'){
   radio.write(&ee , sizeof( unsigned int) );
   delay(200);
    char text[] = "Y";
  radio.write(&text, sizeof(text));
   yy=1;
  while(yy){
   while (Serial.available()>0){
    c=Serial.parseInt();
         if(c>0){
          unsigned int dd= c;
radio.write(&dd , sizeof( unsigned int) );
delay(300);
     yy=0;
   }
   }
  }
  }
         else if(data=='Z'){
    char text[] = "Z";
  radio.write(&text, sizeof(text));
  }
   if(state==0){
    if(data=='A'){
   char text[] = "A";
  radio.write(&text, sizeof(text));
  // put your main code here, to run repeatedly:
  }
  else if(data=='B'){
     char text[] = "B";
  radio.write(&text, sizeof(text));
  }
  else if(data=='C'){
     char text[] = "C";
  radio.write(&text, sizeof(text));
  }
   else if(data=='D'){
    const char text[] = "D";
  radio.write(&text, sizeof(text));
  }
   else if(data=='E'){
    char text[] = "E";
  radio.write(&text, sizeof(text));
  }
  }
}
}


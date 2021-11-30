#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <NewPing.h>
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200
 int uS;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int distance;
Servo myservo0;
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
Servo myservo7;
int lamp=30;
int pos = 0; 
int rgg=0; 
int aa=0;
int bb=0;
int cc=0;
int dd=0;
int d;
int c;
int b;
int a;
int f;
RF24 radio(7, 8);
RF24 radio1(5, 6);
const byte rxAddr[6] = "00001";
const byte rxAddr1[6] = "00002";
unsigned int FR1=43;
unsigned int FR2=45;
unsigned int FRE=10;
unsigned int BR1=42;
unsigned int BR2=44;
unsigned int BRE=3;
unsigned int FL1=46;
unsigned int FL2=48;
unsigned int FLE=4;
unsigned int BL1=47;
unsigned int BL2=49;
unsigned int BLE=9;
int Speed=255;
int Speedl=200;
int flag=0;
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, rxAddr); 
  radio.startListening();
  delay(2000);
  radio1.begin();
  radio1.setRetries(15, 15);
  radio1.openWritingPipe(rxAddr1);
  radio1.stopListening();
  delay(2000);
  pinMode(FR1,OUTPUT);
  pinMode(FR2,OUTPUT);
  pinMode(FRE,OUTPUT);
  pinMode(BR1,OUTPUT);
  pinMode(BR2,OUTPUT);
  pinMode(BRE,OUTPUT);
  pinMode(FL1,OUTPUT);
  pinMode(FL2,OUTPUT);
  pinMode(FLE,OUTPUT);
  pinMode(BL1,OUTPUT);
  pinMode(BL2,OUTPUT);
  pinMode(BLE,OUTPUT);
    pinMode(lamp, OUTPUT);
  myservo0.attach(22);
    myservo1.attach(23);
    myservo2.attach(24);
    myservo3.attach(25);
    myservo4.attach(26);
    myservo5.attach(28);
    myservo7.attach(27);
    myservo6.attach(29);
   myservo0.write(70);  
   myservo1.write(100);
   myservo2.write(43); 
   myservo3.write(23); 
   myservo4.write(15);
   myservo5.write(180); 
   myservo6.write(180); 
   myservo7.write(73);
}
void forward(){
  digitalWrite(FR1,HIGH);
  digitalWrite(FR2,LOW);
  digitalWrite(BR1,HIGH);
  digitalWrite(BR2,LOW);
  digitalWrite(FL1,HIGH);
  digitalWrite(FL2,LOW);
  digitalWrite(BL1,HIGH);
  digitalWrite(BL2,LOW);
}
void reverse(){
  digitalWrite(FR1,LOW);
  digitalWrite(FR2,HIGH);
  digitalWrite(BR1,LOW);
  digitalWrite(BR2,HIGH);
  digitalWrite(FL1,LOW);
  digitalWrite(FL2,HIGH);
  digitalWrite(BL1,LOW);
  digitalWrite(BL2,HIGH);
}
void left(){
  digitalWrite(FR1,HIGH);
  digitalWrite(FR2,LOW);
  digitalWrite(BR1,HIGH);
  digitalWrite(BR2,LOW);
  digitalWrite(FL1,LOW);
  digitalWrite(FL2,LOW);
  digitalWrite(BL1,LOW);
  digitalWrite(BL2,LOW);
   analogWrite(FRE,Speed);
  analogWrite(BRE,Speed);
}
void right(){
  digitalWrite(FR1,LOW);
  digitalWrite(FR2,LOW);
  digitalWrite(BR1,LOW);
  digitalWrite(BR2,LOW);
  digitalWrite(FL1,HIGH);
  digitalWrite(FL2,LOW);
  digitalWrite(BL1,HIGH);
  digitalWrite(BL2,LOW);
  analogWrite(FLE,Speed);
  analogWrite(BLE,Speed);
}
void Stop(){
  digitalWrite(FR1,LOW);
  digitalWrite(FR2,LOW);
  digitalWrite(BR1,LOW);
  digitalWrite(BR2,LOW);
  digitalWrite(FL1,LOW);
  digitalWrite(FL2,LOW);
  digitalWrite(BL1,LOW);
  digitalWrite(BL2,LOW);
}
void Speed_C(){
  analogWrite(FRE,Speed);
  analogWrite(BRE,Speed);
  analogWrite(FLE,Speed);
  analogWrite(BLE,Speed);
}

void loop() {
         delay(50);
  int uS = sonar.ping();
distance=uS / US_ROUNDTRIP_CM;
 while (radio.available())
{
//Serial.println(distance);
  char data;
  radio.read(&data, sizeof(data));// put your main code here, to run repeatedly:
  Serial.println(data);
  //robot forward
if(data=='A'){
  forward();
  Speed_C();
}
//robot backward
else if(data=='B'){
  reverse();
  Speed_C();
}
//robot left
else if(data=='C'){
  left();
}
//robot right 
else if(data=='D'){
  right();
}
//robot stop
else if(data=='E'){
  Stop();
  Speed_C();
}
else if(data=='J'){
digitalWrite(lamp, HIGH);
}
else if(data=='K'){
digitalWrite(lamp, LOW);
}
//send temperature
else if(data=='F'){
 int tempValue = analogRead(A0); 
float  voltage_temp = ((tempValue*5.0)/1024.0);
 unsigned int temperature=(5.26*pow(voltage_temp,3))-(27.34*pow(voltage_temp,2))+(68.87*voltage_temp)-17.81;
radio1.write(&temperature , sizeof(unsigned int) );
} 
//send humidity 
else if(data=='G'){
  int humValue = analogRead(A1); 
float  voltage = ((humValue*5.0)/1024.0); 
unsigned int humidity= (3.26*pow(voltage,3))-(20.65*pow(voltage,2))+(64.81*voltage)-27.44;
radio1.write(&humidity , sizeof( unsigned int) );
}
// enter picking mode
else if(data=='H'){
   b=70;
int rgg1=myservo2.read();
    delay(100);
   if(rgg1<b && b>0){
      for (pos = rgg1; pos <= b; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg1>b && b>0){
     for (pos = rgg1; pos >= b; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
       d=70;
   int rgg3=myservo4.read();
    delay(100);
   if(rgg3<d && d>0){
      for (pos = rgg3; pos <= d; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo4.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg3>d && d>0){
     for (pos = rgg3; pos >= d; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo4.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
 }
}
     for (pos = 70; pos >= 5; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
      for (pos = 70; pos <= 110; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo4.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
    c=18;
   int rgg2=myservo3.read();
    delay(100);
   if(rgg2<c && c>0){
      for (pos = rgg2; pos <= c; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  } 
   }
   else if(rgg2>c && c>0){
     for (pos = rgg2; pos >= c; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }  
   }
a=100;
   int rgg=myservo1.read();
    delay(100);
   if(rgg<a&& a>0){
      for (pos = rgg; pos <= a; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
 myservo1.write(pos); // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg>a && a>0){
     for (pos = rgg; pos >= a; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
    myservo0.write(65); 
      digitalWrite(lamp, HIGH);
}
// after picking initial postion 
else if(data=='I'){
  a=100;
   int rgg=myservo1.read();
    delay(100);
   if(rgg<a&& a>0){
      for (pos = rgg; pos <= a; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
 myservo1.write(pos); // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg>a && a>0){
     for (pos = rgg; pos >= a; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
   b=2;
int rgg1=myservo2.read();
    delay(100);
   if(rgg1<b && b>0){
      for (pos = rgg1; pos <= b; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg1>b && b>0){
     for (pos = rgg1; pos >= b; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
    c=23;
   int rgg2=myservo3.read();
    delay(100);
   if(rgg2<c && c>0){
      for (pos = rgg2; pos <= c; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  } 
   }
   else if(rgg2>c && c>0){
     for (pos = rgg2; pos >= c; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }  
   }
    d=70;
   int rgg3=myservo4.read();
    delay(100);
   if(rgg3<d && d>0){
      for (pos = rgg3; pos <= d; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo4.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg3>d && d>0){
     for (pos = rgg3; pos >= d; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo4.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
 }
}
 for (pos = 5; pos <= 70; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 70; pos >= 15; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo4.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
 }
 for (pos = 70; pos >= 43; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
     digitalWrite(lamp, LOW);
}
//piking end
//recive  x 
 else if(data=='X'){
  dd=1;
  while(dd){
   while( radio.available() )
    {
      unsigned int d;
       radio.read( &d, sizeof(unsigned int) );
         if(d==0){
     dd=0;
   }
     if(d>300&&d<450){
    d = map(d, 225, 535, 145, 80); 
   myservo0.write(75);
   int rgg=myservo4.read();
    delay(100);
   if(rgg<d && d>0){
      for (pos = rgg; pos <= d; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo4.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg>d && d>0){
     for (pos = rgg; pos >= d; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo4.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
   dd=0;
     }
    
}
  }
 }
 //end x
 //receive y
else if(data=='Y'){
  cc=1;
  while(cc){
  while( radio.available() )
    {
      unsigned int c;
       radio.read( &c, sizeof(unsigned int) );
 if(c==0){
     cc=0;
 }
  if(c>181){
    c = map(c, 261, 448, 23, 65); 
    a=75;
   int rgg9=myservo1.read();
    delay(100);
   if(rgg9<a&& a>0){
      for (pos = rgg9; pos <= a; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
 myservo1.write(pos); // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg9>a && a>0){
     for (pos = rgg9; pos >= a; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
   int rgg=myservo3.read();
    delay(100);
   if(rgg<c && c>0){
      for (pos = rgg; pos <= c; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg>c && c>0){
     for (pos = rgg; pos >= c; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
    b=27;
int rgg1=myservo2.read();
    delay(100);
   if(rgg1<b && b>0){
      for (pos = rgg1; pos <= b; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg1>b && b>0){
     for (pos = rgg1; pos >= b; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
    myservo0.write(55);
     delay(2000);
  int uS = sonar.ping();
distance=uS / US_ROUNDTRIP_CM;
Serial.println(distance);
   delay(300);
   ///
   //
   //
   if(distance>10&& distance<15){
   myservo0.write(75);
  delay(1000);
   //
   rgg1=myservo2.read();
  b=(rgg1+19);
    delay(100);
   if(rgg1<b && b>0){
      for (pos = rgg1; pos <= b; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg1>b && b>0){
     for (pos = rgg1; pos >= b; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
   //
   rgg=myservo3.read();
    delay(100);
 int Q=(rgg+distance+8);
 Serial.println(distance);
c=Q;
   int rgg2=myservo3.read();
    delay(100);
   if(rgg2<c && c>0){
      for (pos = rgg2; pos <= c; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  } 
   }
   else if(rgg2>c && c>0){
     for (pos = rgg2; pos >= c; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }  
   }
rgg1=myservo2.read();
  b=(rgg1+distance);;
    delay(100);
   if(rgg1<b && b>0){
      for (pos = rgg1; pos <= b; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg1>b && b>0){
     for (pos = rgg1; pos >= b; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
      //
   //
  //
  myservo0.write(55);
  delay(1000);
 uS = sonar.ping();
distance=uS / US_ROUNDTRIP_CM;
Serial.println(distance);
 if(distance<3){
    myservo0.write(75);
    delay(1000);
 rgg=myservo3.read();
    delay(100);
 int Q=(rgg-10);
 Serial.println(distance);
c=Q;
   int rgg2=myservo3.read();
    delay(100);
   if(rgg2<c && c>0){
      for (pos = rgg2; pos <= c; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  } 
   }
   else if(rgg2>c && c>0){
     for (pos = rgg2; pos >= c; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }  
   }
  b=15;
int rgg1=myservo2.read();
    delay(100);
   if(rgg1<b && b>0){
      for (pos = rgg1; pos <= b; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg1>b && b>0){
     for (pos = rgg1; pos >= b; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
    a=70;
   int rgg9=myservo1.read();
    delay(100);
   if(rgg9<a&& a>0){
      for (pos = rgg9; pos <= a; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
 myservo1.write(pos); // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg9>a && a>0){
     for (pos = rgg9; pos >= a; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
   }
///
//
//
//
   }
   //
   //
  else if(distance>=15){
    myservo0.write(75);
    delay(200);
   rgg=myservo4.read();
    delay(100);
    if(rgg>=113){
    d=(rgg-8);
       if(rgg<d && d>0){
      for (pos = rgg; pos <= d; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo4.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg>d && d>0){
     for (pos = rgg; pos >= d; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo4.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
b=22;
int rgg1=myservo2.read();
    delay(100);
   if(rgg1<b && b>0){
      for (pos = rgg1; pos <= b; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg1>b && b>0){
     for (pos = rgg1; pos >= b; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
    a=80;
   int rgg9=myservo1.read();
    delay(100);
   if(rgg9<a&& a>0){
      for (pos = rgg9; pos <= a; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
 myservo1.write(pos); // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg9>a && a>0){
     for (pos = rgg9; pos >= a; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
   
   }
    else if(rgg<113){
      d=(rgg+3);
         if(rgg<d && d>0){
      for (pos = rgg; pos <= d; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo4.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg>d && d>0){
     for (pos = rgg; pos >= d; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo4.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }

     b=15;
int rgg1=myservo2.read();
    delay(100);
   if(rgg1<b && b>0){
      for (pos = rgg1; pos <= b; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg1>b && b>0){
     for (pos = rgg1; pos >= b; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
    a=80;
   int rgg9=myservo1.read();
    delay(100);
   if(rgg9<a&& a>0){
      for (pos = rgg9; pos <= a; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
 myservo1.write(pos); // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg9>a && a>0){
     for (pos = rgg9; pos >= a; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
    }
    myservo0.write(55);
    delay(2000);
   uS = sonar.ping();
distance=uS / US_ROUNDTRIP_CM;
Serial.println(distance);
   delay(300);
   if(distance>10&& distance<35){
   myservo0.write(75);
  delay(1000);
   //
   rgg1=myservo2.read();
  b=(rgg1+19);
    delay(100);
   if(rgg1<b && b>0){
      for (pos = rgg1; pos <= b; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg1>b && b>0){
     for (pos = rgg1; pos >= b; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
   //
   rgg=myservo3.read();
    delay(100);
 int Q=(rgg+distance+8);
 Serial.println(distance);
c=Q;
   int rgg2=myservo3.read();
    delay(100);
   if(rgg2<c && c>0){
      for (pos = rgg2; pos <= c; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  } 
   }
   else if(rgg2>c && c>0){
     for (pos = rgg2; pos >= c; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }  
   }
rgg1=myservo2.read();
  b=(rgg1+distance);;
    delay(100);
   if(rgg1<b && b>0){
      for (pos = rgg1; pos <= b; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg1>b && b>0){
     for (pos = rgg1; pos >= b; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
   }
  myservo0.write(55);
  delay(2000);
 uS = sonar.ping();
distance=uS / US_ROUNDTRIP_CM;
Serial.println(distance);
if(distance>10&& distance<15){
   myservo0.write(75);
  delay(1000);
   //
   rgg1=myservo2.read();
  b=(rgg1+19);
    delay(100);
   if(rgg1<b && b>0){
      for (pos = rgg1; pos <= b; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg1>b && b>0){
     for (pos = rgg1; pos >= b; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
   //
   rgg=myservo3.read();
    delay(100);
 int Q=(rgg+distance+8);
 Serial.println(distance);
c=Q;
   int rgg2=myservo3.read();
    delay(100);
   if(rgg2<c && c>0){
      for (pos = rgg2; pos <= c; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  } 
   }
   else if(rgg2>c && c>0){
     for (pos = rgg2; pos >= c; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }  
   }
rgg1=myservo2.read();
  b=(rgg1+distance);;
    delay(100);
   if(rgg1<b && b>0){
      for (pos = rgg1; pos <= b; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg1>b && b>0){
     for (pos = rgg1; pos >= b; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
   }
else if(distance>7&&distance<=10){
    myservo0.write(75);
    delay(1000);
 rgg=myservo3.read();
    delay(100);
 int Q=(rgg+10);
 Serial.println(distance);
c=Q;
   int rgg2=myservo3.read();
    delay(100);
   if(rgg2<c && c>0){
      for (pos = rgg2; pos <= c; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  } 
   }
   else if(rgg2>c && c>0){
     for (pos = rgg2; pos >= c; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }  
   }
  b=75;
int rgg1=myservo2.read();
    delay(100);
   if(rgg1<b && b>0){
      for (pos = rgg1; pos <= b; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg1>b && b>0){
     for (pos = rgg1; pos >= b; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
    a=82;
   int rgg9=myservo1.read();
    delay(100);
   if(rgg9<a&& a>0){
      for (pos = rgg9; pos <= a; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
 myservo1.write(pos); // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg9>a && a>0){
     for (pos = rgg9; pos >= a; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }//
   //
   //
  //
  myservo0.write(55);
  delay(1000);
 uS = sonar.ping();
distance=uS / US_ROUNDTRIP_CM;
Serial.println(distance);
 if(distance<3){
    myservo0.write(75);
    delay(1000);
 rgg=myservo3.read();
    delay(100);
 int Q=(rgg-10);
 Serial.println(distance);
c=Q;
   int rgg2=myservo3.read();
    delay(100);
   if(rgg2<c && c>0){
      for (pos = rgg2; pos <= c; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  } 
   }
   else if(rgg2>c && c>0){
     for (pos = rgg2; pos >= c; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }  
   }
  b=15;
int rgg1=myservo2.read();
    delay(100);
   if(rgg1<b && b>0){
      for (pos = rgg1; pos <= b; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg1>b && b>0){
     for (pos = rgg1; pos >= b; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
    a=70;
   int rgg9=myservo1.read();
    delay(100);
   if(rgg9<a&& a>0){
      for (pos = rgg9; pos <= a; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
 myservo1.write(pos); // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg9>a && a>0){
     for (pos = rgg9; pos >= a; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
   }
///
//
//
//
   }
   }
   //

   else if(distance<3){
    myservo0.write(75);
    delay(1000);
 rgg=myservo3.read();
    delay(100);
 int Q=(rgg-10);
 Serial.println(distance);
c=Q;
   int rgg2=myservo3.read();
    delay(100);
   if(rgg2<c && c>0){
      for (pos = rgg2; pos <= c; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  } 
   }
   else if(rgg2>c && c>0){
     for (pos = rgg2; pos >= c; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }  
   }
  b=15;
int rgg1=myservo2.read();
    delay(100);
   if(rgg1<b && b>0){
      for (pos = rgg1; pos <= b; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg1>b && b>0){
     for (pos = rgg1; pos >= b; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
    a=70;
   int rgg9=myservo1.read();
    delay(100);
   if(rgg9<a&& a>0){
      for (pos = rgg9; pos <= a; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
 myservo1.write(pos); // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg9>a && a>0){
     for (pos = rgg9; pos >= a; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
   }
   //
     else if(distance>7&&distance<=10){
    myservo0.write(75);
    delay(1000);
 rgg=myservo3.read();
    delay(100);
 int Q=(rgg+10);
 Serial.println(distance);
c=Q;
   int rgg2=myservo3.read();
    delay(100);
   if(rgg2<c && c>0){
      for (pos = rgg2; pos <= c; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  } 
   }
   else if(rgg2>c && c>0){
     for (pos = rgg2; pos >= c; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }  
   }
  b=34;
int rgg1=myservo2.read();
    delay(100);
   if(rgg1<b && b>0){
      for (pos = rgg1; pos <= b; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg1>b && b>0){
     for (pos = rgg1; pos >= b; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
    a=72;
   int rgg9=myservo1.read();
    delay(100);
   if(rgg9<a&& a>0){
      for (pos = rgg9; pos <= a; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
 myservo1.write(pos); // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg9>a && a>0){
     for (pos = rgg9; pos >= a; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
  myservo0.write(55);
  delay(2000);
 uS = sonar.ping();
distance=uS / US_ROUNDTRIP_CM;
Serial.println(distance);
if(distance<3){
    myservo0.write(75);
    delay(1000);
 rgg=myservo3.read();
    delay(100);
 int Q=(rgg-10);
 Serial.println(distance);
c=Q;
   int rgg2=myservo3.read();
    delay(100);
   if(rgg2<c && c>0){
      for (pos = rgg2; pos <= c; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  } 
   }
   else if(rgg2>c && c>0){
     for (pos = rgg2; pos >= c; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }  
   }
  b=15;
int rgg1=myservo2.read();
    delay(100);
   if(rgg1<b && b>0){
      for (pos = rgg1; pos <= b; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg1>b && b>0){
     for (pos = rgg1; pos >= b; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
    a=70;
   int rgg9=myservo1.read();
    delay(100);
   if(rgg9<a&& a>0){
      for (pos = rgg9; pos <= a; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
 myservo1.write(pos); // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg9>a && a>0){
     for (pos = rgg9; pos >= a; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
   }
   }
     myservo0.write(75);
       delay(2000);
    myservo0.write(55);
    delay(500);
   myservo5.write(90);
    delay(600);
   myservo5.write(180);
     delay(600);
    myservo5.write(90);
    delay(600);
    myservo5.write(180);
    delay(600);
      //AGAIN PICK
 int rgg2=myservo3.read();
      delay(100);
 if(rgg2>60){
  a=50;
   rgg=myservo1.read();
    delay(100);
   if(rgg<a&& a>0){
      for (pos = rgg; pos <= a; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
 myservo1.write(pos); // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg>a && a>0){
     for (pos = rgg; pos >= a; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
    rgg2=myservo3.read();
    delay(100);
    c=(rgg2-15);
    if(c>18){
   if(rgg2<c && c>0){
      for (pos = rgg2; pos <= c; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  } 
   }
   else if(rgg2>c && c>0){
     for (pos = rgg2; pos >= c; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }  
   }
    }
 }
   b=2;
 rgg1=myservo2.read();
    delay(100);
   if(rgg1<b && b>0){
      for (pos = rgg1; pos <= b; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg1>b && b>0){
     for (pos = rgg1; pos >= b; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
   
      c=18;
    rgg2=myservo3.read();
    delay(100);
   if(rgg2<c && c>0){
      for (pos = rgg2; pos <= c; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  } 
   }
   else if(rgg2>c && c>0){
     for (pos = rgg2; pos >= c; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }  
   }
   a=100;
   rgg=myservo1.read();
    delay(100);
   if(rgg<a&& a>0){
      for (pos = rgg; pos <= a; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
 myservo1.write(pos); // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg>a && a>0){
     for (pos = rgg; pos >= a; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
   // tell servo to go to position in variable 'pos'
   //drop
   d=110;
   int rgg3=myservo4.read();
    delay(100);
   if(rgg3<d && d>0){
      for (pos = rgg3; pos <= d; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo4.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg3>d && d>0){
     for (pos = rgg3; pos >= d; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo4.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
 }
}
  a=12;
 rgg=myservo1.read();
    delay(100);
   if(rgg<a&& a>0){
      for (pos = rgg; pos <= a; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
 myservo1.write(pos); // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg>a && a>0){
     for (pos = rgg; pos >= a; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
   rgg2=myservo3.read();
    delay(100);
   if(rgg2<c && c>0){
      for (pos = rgg2; pos <= c; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  } 
   }
   else if(rgg2>c && c>0){
     for (pos = rgg2; pos >= c; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }  
   }
   c=30;
    rgg2=myservo3.read();
    delay(100);
   if(rgg2<c && c>0){
      for (pos = rgg2; pos <= c; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  } 
   }
   else if(rgg2>c && c>0){
     for (pos = rgg2; pos >= c; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }  
   }
   b=130;
 rgg1=myservo2.read();
    delay(100);
   if(rgg1<b && b>0){
      for (pos = rgg1; pos <= b; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
   else if(rgg1>b && b>0){
     for (pos = rgg1; pos >= b; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   }
      c=18;
    rgg2=myservo3.read();
    delay(100);
   if(rgg2<c && c>0){
      for (pos = rgg2; pos <= c; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  } 
   }
   else if(rgg2>c && c>0){
     for (pos = rgg2; pos >= c; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }  
   }
   delay(1000);
    myservo0.write(75); 
    delay(1000);
    myservo0.write(55);
    for (pos = 18; pos >= 33; pos += 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
    for (pos = 130; pos >= 2; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
   for (pos = 12; pos <= 100; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
 myservo1.write(pos); // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
  cc=0;
   //end
   }

   }
  }
}
//end yy
//UNLOAD
else if(data=='N'){
      for (pos = 73; pos <=160; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
 myservo7.write(pos); // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
delay(300);
     for (pos = 180; pos >= 70; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo6.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);
   }
   delay(3000);
   for (pos = 70; pos <= 180; pos += 1) { // goes from 180 degrees to 0 degrees
    myservo6.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
   }
        for (pos = 160; pos >=73; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
 myservo7.write(pos); // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
}
//END UNLOAD
 
}
}


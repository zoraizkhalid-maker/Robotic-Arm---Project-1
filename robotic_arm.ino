#include <SoftwareSerial.h>
SoftwareSerial BT(3, 2); // RX, TX

int pin1  = A0;  
int pin2  = A1;  
int pin3  = A2;
int pin4  = A3;
int pin5  = A4;

int f1 = 0;       
int f2 = 0;
int f3 = 0;
int f4 = 0;
int f5 = 0;


int cont1 = 0;  
int cont2 = 0; 
int cont3 = 0; 
int cont4 = 0; 
int cont5 = 0;


void setup(){
Serial.begin(9600);  
BT.begin(9600);
pinMode(pin1, INPUT);   
pinMode(pin2, INPUT);
pinMode(pin3, INPUT);
pinMode(pin4, INPUT);
pinMode(pin5, INPUT);
delay(1000);
}

void loop(){
f1  = analogRead(pin1);  
f2  = analogRead(pin2);  
f3  = analogRead(pin3); 
f4  = analogRead(pin4);
f5  = analogRead(pin5);  
   
Serial.println(String(f1) +"\t"+ String(f2) +"\t"+ String(f3) +"\t"+ String(f4) +"\t"+ String(f5));

if(f1>495){cont1 = 0;}
else{cont1 = 1;}

if(f2>670){cont2 = 0;}
else{cont2 = 1;}

if(f3>670){cont3 = 0;}
else{cont3 = 1;}

if(f4>670){cont4 = 0;}
else{cont4 = 1;}

if(f5>580){cont5 = 0;}
else{cont5 = 1;}

Serial.print(cont1);
Serial.print(cont2);
Serial.print(cont3);
Serial.print(cont4);
Serial.println(cont5);
data();
delay(300);
}

void data(){
BT.print("OK"); 
BT.print(cont1);  
BT.print(cont2); 
BT.print(cont3); 
BT.print(cont4);
BT.println(cont5);  
}

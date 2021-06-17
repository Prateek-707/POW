#include <RF24Network.h>
#include <SPI.h>
#include <Servo.h> 
#include <RF24.h>

int ENA = 3;
int ENB = 5;
int MotorA1 = 2;
int MotorA2 = 4;
int MotorB1 = A1;
int MotorB2 = A0;

Servo myServo;
Servo myServo1;
Servo myServo2;

RF24 radio(8,7);

RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 002;   // Address of our node in Octal format ( 04,031, etc)
const uint16_t master00 = 00;    // Address of the other node in Octal format
const uint16_t master01 = 01;

int msg[5];
int moto[2];
int serv[3];

void setup() {

myServo.attach(9);
myServo1.attach(6);
myServo2.attach(10);

SPI.begin();               
radio.begin();                    
network.begin(90, this_node); //(channel, node address)
radio.setDataRate(RF24_2MBPS);   
radio.startListening();

pinMode(ENA, OUTPUT);
pinMode(ENB, OUTPUT);
pinMode(MotorA1, OUTPUT);
pinMode(MotorA2, OUTPUT);
pinMode(MotorB1, OUTPUT);
pinMode(MotorB2, OUTPUT);
}


void loop() {
  network.update();
 while( network.available()) {
    RF24NetworkHeader header;
    network.read(header,&msg, sizeof(msg));
 if(header.from_node==02){
 network.read(header,&moto, sizeof(moto));
     if(moto[1] > 400) {
      digitalWrite(MotorA1, LOW);
      digitalWrite(MotorA2, HIGH);
      digitalWrite(MotorB1, HIGH);
      digitalWrite(MotorB2, LOW);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
      
    }else if(moto[1] < 320) {
      digitalWrite(MotorA1, HIGH);
      digitalWrite(MotorA2, LOW);
      digitalWrite(MotorB1, LOW);
      digitalWrite(MotorB2, HIGH);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
    } else if(moto[0] < 320){
      digitalWrite(MotorA1, HIGH);
      digitalWrite(MotorA2, LOW);
      digitalWrite(MotorB1, HIGH);
      digitalWrite(MotorB2, LOW);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
    }else if(moto[0] > 400){
      digitalWrite(MotorA1, LOW);
      digitalWrite(MotorA2, HIGH);
      digitalWrite(MotorB1, LOW);
      digitalWrite(MotorB2, HIGH);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
    }else {
      digitalWrite(MotorA1, LOW);
      digitalWrite(MotorA2, LOW);
      digitalWrite(MotorB1, LOW);
      digitalWrite(MotorB2, LOW);
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
      }                      }
 if(header.from_node==00){ 
  network.read(header,&serv, sizeof(serv));
      myServo.write(serv[0]);
      myServo1.write(serv[1]);
      myServo2.write(serv[2]);
  
  
                         }
                                  }
}

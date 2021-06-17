#include <RF24Network.h>
#include <Servo.h>    
#include <SPI.h>      
#include <RF24.h>     

Servo myServo;
Servo myServo1;
Servo myServo2;
Servo myServo3;
Servo myServo4;       

RF24 radio(8,7);    

RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 001;   // Address of our node in Octal format ( 04,031, etc)
const uint16_t master00 = 00;    // Address of the other node in Octal format

int msg[5];

void setup(){

  myServo.attach(10);
  myServo1.attach(9);
  myServo2.attach(6);
  myServo3.attach(5);
  myServo4.attach(3); 
  SPI.begin();               
  radio.begin();                    
  network.begin(90, this_node); //(channel, node address)
  radio.setDataRate(RF24_2MBPS);   
  radio.startListening();     // ONCE CHECK THIS THING      
  }

void loop(){
  network.update();
  while ( network.available() ) {     // Is there any incoming data?            
    RF24NetworkHeader header;
      network.read(header,&msg, sizeof(msg));
      if (header.from_node ==00  ) {    // If data comes from Node 00
      myServo.write(msg[0]);
      myServo1.write(msg[1]);
      myServo2.write(msg[2]);
      myServo3.write(msg[3]);
      myServo4.write(msg[4]);
      }
    }
  }

#include <SPI.h>
#include <RF24Network.h>
#include "RF24.h"
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

int data[5];
int msg[3];

RF24 radio(8,7);
RF24Network network(radio);
const uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t node001 = 001;     // Address of the other node in Octal format 
const uint16_t node002 = 002;

void setup(void){
radio.begin();
SPI.begin();
network.begin(90, this_node);  //(channel, node address)
radio.setDataRate(RF24_2MBPS);
Wire.begin();
mpu.initialize();
}

void loop(void){
network.update();


mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
data[0] =  map (analogRead(A0), 0, 1023, 0, 180); 
data[1] =  map (analogRead(A1), 0, 1023, 0, 180);
data[2] =  map (analogRead(A2), 0, 1023, 0, 180);
data[3] =  map (analogRead(A3), 0, 1023, 0, 180);
data[4] =  map (analogRead(A6), 0, 1023, 0, 180);
RF24NetworkHeader header3(node001);     // (Address where the data is going)
bool ok = network.write(header3, &data, sizeof(data)); // Send the data


msg[0] = map(ax, -17000, 17000, 0,180);
msg[1] = map(ay, -17000, 17000, 0,180);
msg[2] = map (analogRead(A7), 0, 1023, 0, 180);
RF24NetworkHeader header4(node002);     // (Address where the data is going)
bool ok1 = network.write(header4, &msg, sizeof(msg)); // Send the data


 
}

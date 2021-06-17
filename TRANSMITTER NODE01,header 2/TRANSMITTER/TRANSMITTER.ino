#include <RF24Network.h>
#include <SPI.h>
#include "RF24.h"
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

int data[2];

RF24 radio(8,7);
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 01;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t node002 = 002;      // Address of the other node in Octal format

void setup(void){
SPI.begin();
Wire.begin();
mpu.initialize();
Serial.begin(9600);
radio.begin();
network.begin(90, this_node);  //(channel, node address)
radio.setDataRate(RF24_2MBPS);
}

void loop(void){
network.update();


mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
data[0] = map(ax, 10, 17000, 2,178);     //has to be changed 
data[1] = map(ay, 10, 17000, 2,178);    // check MPU practically and check
RF24NetworkHeader header4(node002);     // (Address where the data is going)
bool ok = network.write(header4, &data, sizeof(data)); // Send the data
   {

    Serial.println(data[0]);

    Serial.println(data[1]);
    }
 
}

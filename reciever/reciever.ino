#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

int ch_width_1 = 0;
int ch_width_2 = 0;
int ch_width_3 = 0;
int ch_width_4 = 0;

Servo ch1;
Servo ch2;
Servo ch3;
Servo ch4;

struct Signal{
byte throttle;
};

Signal data;
const uint64_t pipeIn = 0xE9E8F0F0E1LL;
RF24 radio(7, 8); 
void ResetData()
{
data.throttle = 0;
}
void setup()
{
  Serial.begin(9600);
  ch1.attach(3);
  // ch2.attach(3);
  // ch3.attach(4);
  // ch4.attach(5);
  ResetData();
  radio.begin();
  radio.openReadingPipe(1,pipeIn);
  radio.startListening();
}
unsigned long lastRecvTime = 0;
void recvData()
{
while ( radio.available() ) {
radio.read(&data, sizeof(Signal));
lastRecvTime = millis();
}
}
void loop()
{
recvData();
unsigned long now = millis();
if ( now - lastRecvTime > 1000 ) {
ResetData();
}
ch_width_1 = map(data.throttle, 0, 1023, 1000, 2000);
Serial.println(ch_width_1);
ch1.writeMicroseconds(ch_width_1);
}
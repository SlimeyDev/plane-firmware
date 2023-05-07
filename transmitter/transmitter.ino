#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define Xaxis_pin A0
#define Yaxis_pin A1
#define SW_pin 22

const uint64_t pipeOut = 0xE9E8F0F0E1LL;

RF24 radio(7, 8);

struct Signal{
byte throttle;
};

Signal data;

void ResetData(){
data.throttle = 0;
}

void setup()
{
//Start everything up
radio.begin();
radio.openWritingPipe(pipeOut);
radio.stopListening();
ResetData();
}


void loop()
{
data.throttle = (analogRead(Yaxis_pin));
radio.write(&data, sizeof(Signal));
delay(100);
}
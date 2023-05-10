#include <SPI.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7, 8);
const byte address[6] = "00001";

Servo motor;
Servo elevator;
Servo rudder;
Servo AileronL;
Servo AileronR;

int motorPin = 3;
int elevatorPin = 9;
int rudderPin = 5;
int AileronLPin = 10;
int AileronRPin = 6;
int minSpeed = 1000;
int maxSpeed = 2000;

struct PotentiometerData {
  int pot1Value;
  int pot2Value;
  int pot3Value;
  int pot4Value;
};

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  motor.attach(motorPin);
  motor.writeMicroseconds(minSpeed);
  elevator.attach(elevatorPin);
  rudder.attach(rudderPin);
  AileronL.attach(AileronLPin);
  AileronR.attach(AileronRPin);
}

void loop() {
  if (radio.available()) {
    PotentiometerData data;
    radio.read(&data, sizeof(data));

    int motorSpeed = map(data.pot1Value, 0, 1023, minSpeed, maxSpeed);
    motor.writeMicroseconds(motorSpeed);

    int elevatorPos = map(data.pot2Value, 0, 1023, 1000, 2000);
    elevator.writeMicroseconds(elevatorPos);

    int rudderPos = map(data.pot3Value, 0, 1023, 1000, 2000);
    rudder.writeMicroseconds(rudderPos);
    
    int aileronLPos = map(data.pot4Value, 0, 1023, 1000, 2000);
    AileronL.writeMicroseconds(aileronLPos);

    int aileronRPos = map(data.pot4Value, 0, 1023, 1000, 2000);
    AileronR.writeMicroseconds(aileronRPos);

    Serial.print("Motor speed: ");
    Serial.print(motorSpeed);
    Serial.print(", ");
    Serial.print("Elevator position: ");
    Serial.print(elevatorPos);
    Serial.print(", ");
    Serial.print("Rudder position: ");
    Serial.println(rudderPos);
    Serial.print(", ");
    Serial.print("Ailerons position: ");
    Serial.println(rudderPos);
  }
}
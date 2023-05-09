#include <SPI.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7, 8);
const byte address[6] = "00001";

Servo motor1;
Servo elevator;
Servo rudder;

int motor1Pin = 3;
int elevatorPin = 9;
int rudderPin = 5;
int minSpeed = 1000;
int maxSpeed = 2000;

int pot1Pin = A3;
int pot1Value = 0;
int pot2Pin = A1;
int pot2Value = 0;

struct PotentiometerData {
  int pot1Value;
  int pot2Value;
  int pot3Value;
};

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  motor1.attach(motor1Pin);
  motor1.writeMicroseconds(minSpeed);
  elevator.attach(elevatorPin);
  elevator.write(1000);
  rudder.attach(rudderPin);
  rudder.write(1000);
}

void loop() {
  if (radio.available()) {
    PotentiometerData data;
    radio.read(&data, sizeof(data));

    int motorSpeed = map(data.pot1Value, 0, 1023, minSpeed, maxSpeed);
    motor1.writeMicroseconds(motorSpeed);

    int elevatorPos = map(data.pot2Value, 0, 1023, 1000, 2000);
    elevator.writeMicroseconds(elevatorPos);

    int rudderPos = map(data.pot3Value, 0, 1023, 1000, 2000);
    rudder.writeMicroseconds(rudderPos);

    Serial.print("Motor speed: ");
    Serial.print(motorSpeed);
    Serial.print(", ");
    Serial.print("Elevator position: ");
    Serial.print(elevatorPos);
    Serial.print(", ");
    Serial.print("Rudder position: ");
    Serial.println(rudderPos);
  }
}
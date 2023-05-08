#include <SPI.h>
#include <RF24.h>
#include <Servo.h>

// NRF24L01+ module configuration
RF24 radio(7, 8); // CE, CSN pins
const byte address[6] = "00001";

// Motor configuration
Servo motor1;     // Create a servo object for the motor
Servo elevator;
Servo rudder;

int motor1Pin = 3; // PWM pin to control motor1 speed
int elevatorPin = 9;
int rudderPin = 5;
int minSpeed = 1000;  // Minimum motor speed (pulse width in microseconds)
int maxSpeed = 2000;  // Maximum motor speed (pulse width in microseconds)

// Potentiometer configuration
int pot1Pin = A3;  // Analog pin to read potentiometer1 value
int pot1Value = 0; // Current potentiometer1 value
int pot2Pin = A1;  // Analog pin to read potentiometer2 value
int pot2Value = 0; // Current potentiometer2 value

// Data structure to hold potentiometer values
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
  // Check if there is data available from the transmitter
  if (radio.available()) {
    // Read the potentiometer values from the transmitter
    PotentiometerData data;
    radio.read(&data, sizeof(data));

    // Update the motor speed using the motor potentiometer
    int motorSpeed = map(data.pot1Value, 0, 1023, minSpeed, maxSpeed);
    motor1.writeMicroseconds(motorSpeed);

    // Update the elevator position using the elevator potentiometer
    int elevatorPos = map(data.pot2Value, 0, 1023, 1000, 2000);
    elevator.writeMicroseconds(elevatorPos);

    int rudderPos = map(data.pot3Value, 0, 1023, 1000, 2000);
    rudder.writeMicroseconds(rudderPos);

    // Print the motor speed and elevator position on the serial monitor
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

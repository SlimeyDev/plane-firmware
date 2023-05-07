#include <SPI.h>
#include <RF24.h>
#include <Servo.h>

// NRF24L01+ module configuration
RF24 radio(7, 8); // CE, CSN pins
const byte address[6] = "00001";

// Motor configuration
Servo motor1, motor2;    // Create servo objects for the motors
int motor1Pin = 3; // PWM pin to control motor1 speed
int motor2Pin = 9; // PWM pin to control motor2 speed
int minSpeed = 1000;  // Minimum motor speed (pulse width in microseconds)
int maxSpeed = 2000;  // Maximum motor speed (pulse width in microseconds)

// Potentiometer configuration
int pot1Pin = A3;  // Analog pin to read potentiometer1 value
int pot2Pin = A1;  // Analog pin to read potentiometer2 value
int pot1Value = 0; // Current potentiometer1 value
int pot2Value = 0; // Current potentiometer2 value

void setup() {
  Serial.begin(9600);

  // NRF24L01+ module setup
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  // Motor setup
  motor1.attach(motor1Pin);
  // motor2.attach(motor2Pin);
  motor1.writeMicroseconds(minSpeed);
  // motor2.writeMicroseconds(minSpeed);
}

void loop() {
  // Check if there is data available from the transmitter
  if (radio.available()) {
    // Read the received data for potentiometer1
    radio.read(&pot1Value, sizeof(pot1Value));
    // Read the received data for potentiometer2
    radio.read(&pot2Value, sizeof(pot2Value));

    // Map the potentiometer values to the motor speed range
    int speed1 = map(pot1Value, 0, 1023, minSpeed, maxSpeed);
    // int speed2 = map(pot2Value, 0, 1023, minSpeed, maxSpeed);

    // Set the motor speeds
    motor1.writeMicroseconds(speed1);
    // motor2.writeMicroseconds(speed2);

    // Print the motor speeds on the serial monitor
    Serial.print("Motor1 speed: ");
    Serial.println(speed1);
    // Serial.print(" | Motor2 speed: ");
    // Serial.println(speed2);
  }
}
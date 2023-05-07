#include <SPI.h>
#include <RF24.h>

// NRF24L01+ module configuration
RF24 radio(7, 8); // CE, CSN pins
const byte address[6] = "00001";

// Potentiometer configuration
int potPin1 = A3; // Analog pin to read the first potentiometer value
int potPin2 = A1; // Analog pin to read the second potentiometer value
int potValue1 = 0; // Current value of the first potentiometer
int potValue2 = 0; // Current value of the second potentiometer

void setup() {
  Serial.begin(9600);

  // NRF24L01+ module setup
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  // Read the value of potentiometer1
  potValue1 = analogRead(potPin1);

  // Send the value of potentiometer1 over NRF24L01+ module
  bool success = radio.write(&potValue1, sizeof(potValue1));

  // Print the value and transmission status for potentiometer1
  Serial.print("Potentiometer 1 value: ");
  Serial.print(potValue1);
  Serial.print(" | Transmission status: ");
  Serial.println(success);

  // // Read the value of potentiometer2
  // potValue2 = analogRead(potPin2);

  // // Send the value of potentiometer2 over NRF24L01+ module
  // success = radio.write(&potValue2, sizeof(potValue2));

  // // Print the value and transmission status for potentiometer2
  // Serial.print("Potentiometer 2 value: ");
  // Serial.print(potValue2);
  // Serial.print(" | Transmission status: ");
  // Serial.println(success);

  // Wait for some time before sending the next data
  delay(100);
}
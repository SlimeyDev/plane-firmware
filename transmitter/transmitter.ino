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
  // Read the value of potentiometers
  potValue1 = analogRead(potPin1);
  potValue2 = analogRead(potPin2);

  // Create data object to hold the potentiometer values
  struct {
    int pot1Value;
    int pot2Value;
  } data;

  // Assign potentiometer values to data object
  data.pot1Value = potValue1;
  data.pot2Value = potValue2;

  // Send the data object over NRF24L01+ module
  bool success = radio.write(&data, sizeof(data));

  // Print the values and transmission status for potentiometers
  Serial.print("Potentiometer 1 value: ");
  Serial.print(potValue1);
  Serial.print(" | Potentiometer 2 value: ");
  Serial.print(potValue2);
  Serial.print(" | Transmission status: ");
  Serial.println(success);

  // Wait for some time before sending the next data
  delay(100);
}

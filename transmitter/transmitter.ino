#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8);
const byte address[6] = "00001";

int potPin1 = A3;
int potPin2 = A1;
int potPin3 = A2;
int potPin4 = A0;
int potValue1 = 0;
int potValue2 = 0;
int potValue3 = 0;
int potValue4 = 0;

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  potValue1 = analogRead(potPin1);
  potValue2 = analogRead(potPin2);
  potValue3 = analogRead(potPin3);
  potValue4 = analogRead(potPin4);

  struct {
    int pot1Value;
    int pot2Value;
    int pot3Value;
    int pot4Value;
  } data;

  data.pot1Value = potValue1;
  data.pot2Value = potValue2;
  data.pot3Value = potValue3;
  data.pot4Value = potValue4;

  bool success = radio.write(&data, sizeof(data));

  Serial.print("Potentiometer 1 value: ");
  Serial.print(potValue1);
  Serial.print(" | Potentiometer 2 value: ");
  Serial.print(potValue2);
  Serial.print(" | Potentiometer 3 value: ");
  Serial.print(potValue3);
  Serial.print(" | Potentiometer 4 value: ");
  Serial.print(potValue4);
  Serial.print(" | Transmission status: ");
  Serial.println(success);
  delay(100);
}
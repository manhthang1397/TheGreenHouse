#include <max6675.h>

// Define MAX6675 connections to Arduino
int thermoDO = 12;   // MISO (SO) pin on MAX6675
int thermoCS = 10;   // Chip Select (CS) pin
int thermoCLK = 13;  // Clock (SCK) pin

// Create an instance of MAX6675
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  Serial.begin(9600);
  delay(500); // Allow MAX6675 to stabilize 
  Serial.println("MAX6675 K-Type Thermocouple Reader");
}

void loop() {
  Serial.print("Temperature: ");
  Serial.print(thermocouple.readCelsius());
  Serial.println(" °C");

  delay(1000); // Read every 1 second
}

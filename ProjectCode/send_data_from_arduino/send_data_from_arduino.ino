//Include dht libraty to code
#include "DHT.h"

// Defien the pin for dht input
#define DHTPIN 5

// Define which type of DHT Sensor you are using
#define DHTTYPE DHT11

// Include the Software Serial Library 
#include <SoftwareSerial.h>

// Setup the RX and TX Pin for arduino uno
SoftwareSerial Arduino_to_Esp8266(2,3); // RX,TX

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);


// variable for Soil Moisture Sensor
int inputPin = A0; 
int moistureValue;  
int limit = 300;

// Setting up the variable for the DHT11 sensor
float humidity;
float tempInCelsius;
float tempInFahrenheit;



void setup() {
    // Open the serial communication to computer
    Serial.begin(115200);
    
    // Open the seial communication to Esp8266
    Arduino_to_Esp8266.begin(115200);

    // Pin mode for Soil Moisture Sensor
    pinMode(13, OUTPUT);

    // Begin the DHT Sensor
    dht.begin();

}

void loop() {
   // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  tempInCelsius = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  tempInFahrenheit = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(tempInCelsius) || isnan(tempInFahrenheit)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(tempInFahrenheit, humidity);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(tempInCelsius, humidity, false);



 // Getting and calculating the moisture value from the sensor
 moistureValue = analogRead(inputPin); 
 // Print the Moisture valur to the Serial Monitor
 Serial.println("Analog Value : ");
 Serial.println("This value is from Moisture Sensor");
 Serial.println(moistureValue);

 if (moistureValue<limit) {
 Serial.println("Value if low Low"); 
 }
 else {
 Serial.println("Value is High"); 
 }
 
 delay(1000); 


  //  Printing the DHT value
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(tempInCelsius);
  Serial.print(F("C "));
  Serial.print(tempInFahrenheit);
  Serial.print(F("F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("C "));
  Serial.print(hif);
  Serial.println(F("F"));


 // Send the data to the serial port
 Arduino_to_Esp8266.print(humidity, 2);          Arduino_to_Esp8266.print("A");
 Arduino_to_Esp8266.print(tempInCelsius, 2);     Arduino_to_Esp8266.print("B");
 Arduino_to_Esp8266.print(tempInFahrenheit, 2);  Arduino_to_Esp8266.print("C");
 Arduino_to_Esp8266.print(hif, 2);               Arduino_to_Esp8266.print("D");
 Arduino_to_Esp8266.print(hic, 2);               Arduino_to_Esp8266.print("E");
 Arduino_to_Esp8266.print(moistureValue);        Arduino_to_Esp8266.print("F");

 delay(1000);


}

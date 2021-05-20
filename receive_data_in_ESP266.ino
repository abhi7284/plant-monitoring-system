// include ESP wifi
#include <ESP8266WiFi.h>



// Include Software Serial Libbrary
//#include <SoftwareSerial.h>

// Declare SoftwareSerial
//SoftwareSerial mySerialForESP(2,3);



// Include Firebase module
#include <FirebaseESP8266.h>

// Define the Firebase Database project URL
#define FIREBASE_HOST "soil-monitoring-arduino-default-rtdb.firebaseio.com"

// Define Firebase Secret Key
#define FIREBASE_AUTH "3Pj4ltQWDf2RQShzOXcCpiCvJRmJ0Jv96YH5E3ox"

// Define Wifi SSID to connect ESP8266
#define WIFI_SSID "hyper"

// Define Wifi Password
#define WIFI_PASSWORD "quarterhalf" 

// Declare the Firebase Data object in the global scope
FirebaseData firebaseData;

// Global variable for incoming data
char c;
String dataIn;
int8_t indexOfA,indexOfB, indexOfC,indexOfD,indexOfE,indexOfF;
String humidity, tempInCelsius, tempInFahrenheit, heatIndexInFahrenheit,
       heatIndexInCelsius, moistureValue;

float humidityF, tempInCelsiusF, tempInFahrenheitF, heatIndexInFahrenheitF,
      heatIndexInCelsiusF;
int   moistureValueIN;




void setup() {
  // Onpen the serial communication
  Serial.begin(115200);

  Serial.println("Serial communication started\n\n");

  //Connect to the wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);

  // Check wifi is connected or not
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // Show the connected Status
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");

  //print local IP address
  Serial.println(WiFi.localIP());

  // Connect to the firebase and set it to auto reconnect
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  Firebase.reconnectWiFi(true);
  delay(1000);

  


}

void loop() {
  
  // Read the data in byte and sotore it to c temprarely
    dataIn = Serial.readString();
    
    // Parse the data at the end of reading
    parse_The_Data();

    // Sending the data to firebase
    sendDataToFirebase();
    
    // Reset the value
    dataIn = "";
    
    delay(2000);

}

// Parsing the data
void parse_The_Data(){

  indexOfA = dataIn.indexOf("A");
  indexOfB = dataIn.indexOf("B");
  indexOfC = dataIn.indexOf("C");
  indexOfD = dataIn.indexOf("D");
  indexOfE = dataIn.indexOf("E");
  indexOfF = dataIn.indexOf("F");


  humidity                = dataIn.substring(0, indexOfA);
  tempInCelsius           = dataIn.substring(indexOfA+1, indexOfB);
  tempInFahrenheit        = dataIn.substring(indexOfB+1, indexOfC);
  heatIndexInFahrenheit   = dataIn.substring(indexOfC+1, indexOfD);
  heatIndexInCelsius      = dataIn.substring(indexOfD+1, indexOfE);
  moistureValue           = dataIn.substring(indexOfE+1, indexOfF); 


  humidityF               = humidity.toFloat();
  tempInCelsiusF          = tempInCelsius.toFloat();
  tempInFahrenheitF       = tempInFahrenheit.toFloat();
  heatIndexInFahrenheitF  = heatIndexInFahrenheit.toFloat();
  heatIndexInCelsiusF     = heatIndexInCelsius.toFloat();
  moistureValueIN         = moistureValue.toInt();
 }

 void sendDataToFirebase(){

  Firebase.setFloat(firebaseData, "/humidity", humidityF);
  Firebase.setFloat(firebaseData, "/tempInCelsius", tempInCelsiusF);
  Firebase.setFloat(firebaseData, "/tempInFahrenheit", tempInFahrenheitF);
  Firebase.setFloat(firebaseData, "/heatIndexInFahrenheit", heatIndexInFahrenheitF);
  Firebase.setFloat(firebaseData, "/heatIndexInCelsius", heatIndexInCelsiusF);
  Firebase.setInt(firebaseData, "/moistureValue", moistureValueIN);
 }

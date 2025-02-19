#include <ArduinoBLE.h>

const int pressurePin = 34;
int pressureValue = 0;
int baselineValue = 0; 
int maxPressure = 4095; 
bool isBaselineSet = false;  

unsigned long previousMillis = 0; 
const long interval = 100; 

int totalPressure = 0; 
const int numReadings = 10; 
int readingCount = 0; 

BLEService signalService("180F");  
BLECharacteristic pressureCharacteristic("2A19", BLERead, 20);  

void setup() {
  Serial.begin(115200); 
  pinMode(pressurePin, INPUT); 

  if (!BLE.begin()) {  
    Serial.println("BLE initialization failed!");
    while (1); 
  }

  BLE.setLocalName("ESP32_Bluetooth");
  BLE.setAdvertisedService(signalService);
  signalService.addCharacteristic(pressureCharacteristic);
  BLE.addService(signalService);
  BLE.advertise();

  Serial.println("BLE Started! Waiting for connection...");
}

void loop() {
  if (!BLE.connected()) {
    Serial.println("Waiting for connection...");
    delay(500); 
    return;
  }

  unsigned long currentMillis = millis(); 

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  

    pressureValue = analogRead(pressurePin);
    totalPressure += pressureValue; 
    readingCount++;

    if (readingCount >= numReadings) {
      int averagePressure = totalPressure / numReadings; 
      Serial.print("Average Pressure Sensor Value: ");
      Serial.println(averagePressure);

      String pressureStr = String(averagePressure);

      pressureCharacteristic.setValue(pressureStr.c_str());

      totalPressure = 0;
      readingCount = 0;

      delay(100);
    }
  }
}

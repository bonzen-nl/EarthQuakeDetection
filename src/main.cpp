/**
 * @brief Voorbeeldcode voor het uitlezen van een MPU6050-sensor met een ESP32, RTC (DS3231) en SD-kaart met buffer.
 *
 * Deze code initialiseert de MPU6050-sensor, de DS3231 RTC en de SD-kaartmodule, en leest de
 * accelerometerwaarden uit met een interval van 10 milliseconden (100Hz sampling).
 * De waarden en de tijd worden eerst in een buffer opgeslagen en periodiek naar het
 * CSV-bestand op de SD-kaart geschreven.
 *
 * @details
 * - De MPU6050-sensor en de DS3231 RTC worden geinitialiseerd via de I2C-bus (SDA op pin 32, SCL op pin 33).
 * - De gyroscoop-offsets worden berekend tijdens de initialisatie.
 * - De SD-kaartmodule wordt geïnitialiseerd via SPI (MOSI op pin 23, MISO op pin 19, SCK op pin 18, CS op pin 5).
 * - In de hoofdloop wordt de sensor elke 10 milliseconden bijgewerkt en worden de
 * accelerometerwaarden en de tijd toegevoegd aan de buffer.
 * - Periodiek wordt de buffer naar het CSV-bestand op de SD-kaart geschreven.
 * - Foutafhandeling is toegevoegd voor de initialisatie van de RTC en de SD-kaartmodule.
 */

 #include <Arduino.h>
 #include <Wire.h>
 #include <MPU6050_light.h>
 #include <RTClib.h> // Include RTC library
 #include <SD.h>    // Include SD library
 
 MPU6050 mpu(Wire); // MPU6050 object with I2C address
 RTC_DS3231 rtc;    // RTC_DS3231 object
 
 unsigned long previousMillis = 0; // Tijdstempel van de vorige meting
 const long interval = 10;         // Interval in milliseconden (10ms voor 100Hz sampling)
 const int chipSelect = 5;         // CS pin voor SD-kaartmodule
 
 // Buffer voor SD-kaartdata
 const int bufferSize = 100; // Aantal regels in de buffer
 String dataBuffer[bufferSize];
 int bufferIndex = 0;
 
 // Declareer de functie writeBufferToSD()
void writeBufferToSD();
 
 // Timer voor het schrijven van de buffer naar SD-kaart
 unsigned long lastWriteTime = 0;
 const unsigned long writeInterval = 5000; // Schrijf interval in milliseconden (5 seconden)
 
 void setup() {
   Serial.begin(74880); // Initialiseer seriële communicatie
   Wire.begin(32, 33);  // Initialiseer I2C-bus
 
   mpu.begin();             // Initialiseer MPU6050-sensor
   mpu.calcGyroOffsets(); // Bereken gyroscoop-offsets
 
   if (!rtc.begin()) {
	 Serial.println("RTC niet gevonden!");
	 Serial.flush();
	 abort();
   }
 
   if (rtc.lostPower()) {
	 Serial.println("RTC stroom verloren, tijd instellen...");
	 rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   }
 
   // Controleer of de SD-kaart aanwezig is
   if (!SD.begin(chipSelect)) {
	 Serial.println("SD kaart initialisatie mislukt!");
	 if (SD.cardType() == CARD_NONE) {
	   Serial.println("Geen SD kaart gedetecteerd.");
	 } else {
	   Serial.println("SD kaart kon niet geinitialiseerd worden.");
	 }
	 while (1); // Stop verdere uitvoering bij fout
   }
   Serial.println("SD kaart initialisatie geslaagd.");
 }
 
 void loop() {
   unsigned long currentMillis = millis(); // Huidige tijd in milliseconden
 
   if (currentMillis - previousMillis >= interval) {
	 previousMillis = currentMillis;
	 mpu.update();
	 DateTime now = rtc.now();
 
	 // Data samenstellen en toevoegen aan de buffer
	 String dataString = "";
	 dataString += String(now.year()) + "," + String(now.month()) + "," + String(now.day()) + "," + String(now.hour()) + "," + String(now.minute()) + "," + String(now.second());
	 dataString += "," + String(mpu.getAccX()) + "," + String(mpu.getAccY()) + "," + String(mpu.getAccZ());
 
	 dataBuffer[bufferIndex] = dataString;
	 bufferIndex++;
 
	 // Buffer vol, schrijf naar SD-kaart
	 if (bufferIndex >= bufferSize) {
	   writeBufferToSD();
	   bufferIndex = 0; // Reset buffer index
	 }
 
	 // Controleer tijd om buffer naar SD te schrijven
	 if (currentMillis - lastWriteTime >= writeInterval) {
	   writeBufferToSD();
	   bufferIndex = 0; // Reset buffer index
	   lastWriteTime = currentMillis; // Update laatste schrijftijd
	 }
 
	 // Ook afdrukken naar de seriële monitor (optioneel)
	 Serial.println(dataString);
   }
 }
 
 // Functie om de buffer naar de SD-kaart te schrijven
 void writeBufferToSD() {
   File dataFile = SD.open("data.csv", FILE_APPEND);
   if (dataFile) {
	 for (int i = 0; i < bufferIndex; i++) {
	   dataFile.println(dataBuffer[i]);
	 }
	 dataFile.close();
   } else {
	 Serial.println("Fout bij openen van data.csv voor buffer schrijven.");
   }
 }
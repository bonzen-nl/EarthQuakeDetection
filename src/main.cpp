/**
 * @brief Voorbeeldcode voor het uitlezen van een MPU6050-sensor met een Arduino en RTC (DS3231).
 * * Deze code initialiseert de MPU6050-sensor en de DS3231 RTC, en leest de accelerometerwaarden uit
 * met een interval van 10 milliseconden (100Hz sampling). De waarden en de tijd worden via
 * de seriële monitor weergegeven.
 * * @details
 * - De MPU6050-sensor en de DS3231 RTC worden geinitialiseerd via de I2C-bus (SDA op pin 32, SCL op pin 33).
 * - De gyroscoop-offsets worden berekend tijdens de initialisatie.
 * - In de hoofdloop wordt de sensor elke 10 milliseconden bijgewerkt en worden de
 * accelerometerwaarden en de tijd naar de seriële monitor gestuurd.
 */
#include <Arduino.h>
 #include <Wire.h> 
 #include <MPU6050_light.h>
 #include <RTClib.h> // Include RTC library
 #include <SD.h> // Include SD library
 
 MPU6050 mpu(Wire); // MPU6050 object with I2C address
 RTC_DS3231 rtc; // RTC_DS3231 object
 
 unsigned long previousMillis = 0; // Tijdstempel van de vorige meting
 const long interval = 10; // Interval in milliseconden (10ms voor 100Hz sampling)
 const int chipSelect = 5; // CS pin voor SD-kaartmodule
 File dataFile; // Bestand voor het opslaan van gegevens
 
 void setup() { 
	 Serial.begin(74880); // Initialiseer seriële communicatie met 115200 baud
	 Wire.begin(32, 33); // Initialiseer I2C-bus met SDA op pin 32 en SCL op pin 33
 
	 mpu.begin(); // Initialiseer MPU6050-sensor
	 mpu.calcGyroOffsets(); // Bereken gyroscoop-offsets
 
	 if (!rtc.begin()) {
		 Serial.println("RTC niet gevonden!");
		 Serial.flush();
		 abort();
	 }
 
	 if (rtc.lostPower()) {
		 Serial.println("RTC stroom verloren, tijd instellen...");
		 // Stel de RTC in op de compileertijd (kan je veranderen naar manuele tijd indien nodig)
		 rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
	 }
	 if (!SD.begin(chipSelect)) { // Initialize SD card
		Serial.println("SD kaart initialisatie mislukt!");
		return;
	  }
	  Serial.println("SD kaart initialisatie geslaagd.");
 } 
 
 void loop() { 
	 unsigned long currentMillis = millis(); // Huidige tijd in milliseconden
 
	 if (currentMillis - previousMillis >= interval) { // Controleer of het interval is verstreken
		previousMillis = currentMillis; // Update de vorige tijdstempel
		mpu.update(); // Werk de sensorwaarden bij
		DateTime now = rtc.now(); // Haal de huidige tijd van de RTC op
		String dataString = ""; // String voor de data

		dataString += String(now.year()) + "/" + String(now.month()) + "/" + String(now.day()) + " " + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
    	dataString += ",";
    	dataString += String(mpu.getAccX()) + "," + String(mpu.getAccY()) + "," + String(mpu.getAccZ());
 
		dataFile = SD.open("data.txt", FILE_APPEND); // Open bestand om toe te kunnen voegen
		if (dataFile) {
			dataFile.println(dataString); // Ggevens toevoegen aan het bestand
			dataFile.close(); // Bestad sluiten
		} else {
			Serial.println("fout bij openen van data.txt");
		}

		Serial.println(dataString); // Ook afdrukken naar de seriële monitor
	}

 }
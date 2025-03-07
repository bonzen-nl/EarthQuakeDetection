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
 
 MPU6050 mpu; // MPU6050 object
 RTC_DS3231 rtc; // RTC_DS3231 object
 
 unsigned long previousMillis = 0; // Tijdstempel van de vorige meting
 const long interval = 10; // Interval in milliseconden (10ms voor 100Hz sampling)
 
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
 } 
 
 void loop() { 
	 unsigned long currentMillis = millis(); // Huidige tijd in milliseconden
 
	 if (currentMillis - previousMillis >= interval) { // Controleer of het interval is verstreken
		 previousMillis = currentMillis; // Update de vorige tijdstempel
		 mpu.update(); // Werk de sensorwaarden bij
		 DateTime now = rtc.now(); // Haal de huidige tijd van de RTC op
 
		 Serial.print(now.year(), DEC); // Print het jaar
		 Serial.print('/');
		 Serial.print(now.month(), DEC); // Print de maand
		 Serial.print('/');
		 Serial.print(now.day(), DEC); // Print de dag
		 Serial.print(" ");
		 Serial.print(now.hour(), DEC); // Print het uur
		 Serial.print(':');
		 Serial.print(now.minute(), DEC); // Print de minuut
		 Serial.print(':');
		 Serial.print(now.second(), DEC); // Print de seconde
		 Serial.print(" ");
 
		 Serial.print("ACCEL: x:"); 
		 Serial.print(mpu.getAccX()); // Lees en print de X-accelerometerwaarde
		 Serial.print(" y:"); 
		 Serial.print(mpu.getAccY()); // Lees en print de Y-accelerometerwaarde
		 Serial.print(" z:"); 
		 Serial.print(mpu.getAccZ()); // Lees en print de Z-accelerometerwaarde
		 Serial.println(); 
	 }
 }
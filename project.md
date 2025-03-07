# Projectdocumentatie: Seismologische Event Detector met ESP32

## Inleiding

Dit document beschrijft de ontwikkeling van een seismologische event detector gebaseerd op de ESP32-WROOM-32D microcontroller. Het project maakt gebruik van een MPU-6050 gyroscoop/accelerometer, een DS3231 Real-Time Clock (RTC), en een SD-kaartmodule voor gegevensopslag. Daarnaast wordt WiFi-functionaliteit geïmplementeerd om de RTC te synchroniseren via NTP en een live grafiek van de sensorwaarden weer te geven via een webinterface.

## Hardware

### Componenten

* ESP32-WROOM-32D Development Board
* MPU-6050 Gyroscoop/Accelerometer Module
* DS3231 Real-Time Clock (RTC) Module
* SPI SD-kaartmodule
* SD-kaart (geformatteerd als FAT32)

### Aansluitingsoverzicht

| Module           | ESP32-WROOM-32D Pin | Functie      | Opmerkingen                                                                                                                  |
| :--------------- | :------------------ | :----------- | :--------------------------------------------------------------------------------------------------------------------------- |
| MPU-6050         | GPIO 32             | SDA (I2C)    | Data lijn voor I2C communicatie                                                                                               |
| MPU-6050         | GPIO 33             | SCL (I2C)    | Kloklijn voor I2C communicatie                                                                                              |
| MPU-6050         | 3.3V                | VCC          | Voeding voor de MPU-6050                                                                                                     |
| MPU-6050         | GND                 | GND          | Aarding                                                                                                                      |
| DS3231 RTC       | GPIO 32             | SDA (I2C)    | Data lijn voor I2C communicatie (gedeeld met MPU-6050)                                                                       |
| DS3231 RTC       | GPIO 33             | SCL (I2C)    | Kloklijn voor I2C communicatie (gedeeld met MPU-6050)                                                                      |
| DS3231 RTC       | 3.3V                | VCC          | Voeding voor de DS3231                                                                                                       |
| DS3231 RTC       | GND                 | GND          | Aarding                                                                                                                      |
| SD-kaart Module  | GPIO 23             | MOSI (SPI)   | Master Out Slave In - Data uitgang van ESP32                                                                                |
| SD-kaart Module  | GPIO 19             | MISO (SPI)   | Master In Slave Out - Data ingang van ESP32                                                                                 |
| SD-kaart Module  | GPIO 18             | SCK (SPI)    | Seriële klok voor SPI communicatie                                                                                           |
| SD-kaart Module  | GPIO 5              | CS (SPI)     | Chip Select - Selecteert de SD-kaartmodule                                                                                  |
| SD-kaart Module  | 3.3V / 5V           | VCC          | Voeding voor de SD-kaartmodule (afhankelijk van module)                                                                      |
| SD-kaart Module  | GND                 | GND          | Aarding                                                                                                                      |
| ESP32 BOOT knop  | GPIO 0              | BOOT         | word gebruikt om de ESP32 in de download modus te zetten.                                                                   |
| ESP32 EN knop    | EN pin              | EN (CHIP_PU) | Reset de ESP32. Niet direct verbonden met een programmeerbare GPIO-pin.                                                     |

**Belangrijke opmerkingen:**

* **I2C:** De MPU-6050 en DS3231 delen de I2C-bus.
* **SPI:** De SD-kaartmodule gebruikt de SPI-bus.
* **Voeding:** Zorg ervoor dat de voedingsspanning (VCC) overeenkomt met de specificaties van de modules die je gebruikt.
* **Aarding:** Alle GND-verbindingen moeten met elkaar verbonden zijn.
* **Pull-up Weerstanden:** Vergeet niet de noodzakelijke pull-up weerstanden voor de I2C-bus.

## Software

### Arduino IDE

De software is ontwikkeld in de Arduino IDE met ESP32 board support. De volgende libraries worden gebruikt:

* Wire.h
* MPU6050\_light.h
* RTClib.h
* SD.h

### Functionaliteit

1.  **MPU-6050 Sensor Data Acquisition:**
    * De MPU-6050 sensor leest continu accelerometerwaarden uit met een sampling rate van 100Hz (10ms interval).
    * Gyroscope offsets worden berekend tijdens de initialisatie.
2.  **DS3231 RTC Synchronisatie:**
    * De DS3231 RTC wordt gesynchroniseerd via een NTP-server via WiFi.
    * Synchronisatie vindt plaats bij het opstarten en periodiek (eens per 24 uur).
    * Als WiFi niet beschikbaar is, wordt de RTC ingesteld op de compileertijd (of eventueel een handmatig ingestelde tijd).
3.  **SD-kaart Data Logging:**
    * Accelerometerwaarden en tijdstempels worden in CSV-formaat opgeslagen op de SD-kaart.
    * Data buffering is geïmplementeerd om het aantal schrijfacties te minimaliseren.
    * Foutafhandeling is toegevoegd voor SD-kaartinitialisatie en bestandsschrijven.
4.  **WiFi Configuratie en Webinterface:**
    * Als er geen opgeslagen WiFi-netwerkgegevens zijn of als de verbinding mislukt, gaat de ESP32 in AP-modus.
    * Een webinterface in AP-modus stelt gebruikers in staat om WiFi-netwerkgegevens in te stellen.
    * Bij een actieve WiFi-verbinding wordt een webserver gestart die een live grafiek van de accelerometerwaarden weergeeft in een browser.
    * De data voor de grafiek wordt in JSON-formaat beschikbaar gesteld.

### Todo-lijst

-   [ ] **WiFi Functionaliteit:**
    -   [ ] Implementeer WiFi-verbinding met opslag van netwerkgegevens in het flashgeheugen.
    -   [ ] Implementeer AP-modus met een webinterface voor WiFi-configuratie.
    -   [ ] Test de WiFi-verbinding en AP-modus grondig.
-   [ ] **NTP Synchronisatie:**
    -   [ ] Integreer een NTP-bibliotheek in het project.
    -   [ ] Implementeer automatische RTC-synchronisatie bij opstarten en periodiek (24 uur).
    -   [ ] Voeg foutafhandeling toe voor mislukte NTP-synchronisatie.
-   [ ] **Webserver en Live Grafiek:**
    -   [ ] Implementeer een webserver op de ESP32.
    -   [ ] Maak een webpagina met een live grafiek van de accelerometerwaarden.
    -   [ ] Zorg ervoor dat de grafiek real-time data weergeeft.
    -   [ ] Implementeer het wegschrijven van de data in JSON formaat.
-   [ ] **Data opslag op SD kaart.**
    -   [ ] Zorg ervoor dat de eerder geimplementeerde functie om de data weg te schrijven naar de SD-kaart behouden blijft.
    -   [ ] Zorg ervoor dat de data die via de webserver te bekijken is, overeen komt met de data op de SD kaart.
-   [ ] **Testen en Debuggen:**
    -   [ ] Test alle functionaliteiten grondig in verschillende scenario's.
    -   [ ] Voeg debug-informatie toe om eventuele problemen op te sporen.
    -   [ ] Test de code in verschillende netwerk omstandigheden.
-   [ ] **Event-detectie algoritmen:**
    -   [ ] Implementeer event-detectie algoritmen om alleen significante seismische gebeurtenissen op te slaan.
-   [ ] **Webinterface uitbreiding:**
    -   [ ] Breid de webinterface uit met extra functionaliteiten zoals het downloaden van opgeslagen data.
-   [ ] **Alarmfunctie:**
    -   [ ] Voeg een alarmfunctie toe bij het detecteren van een significant event.
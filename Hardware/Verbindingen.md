# Aansluitingsoverzicht ESP32-WROOM-32D met Modules

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

* **I2C:** De MPU-6050 en DS3231 delen de I2C-bus, wat betekent dat ze dezelfde SDA- en SCL-pinnen gebruiken.
* **SPI:** De SD-kaartmodule gebruikt de SPI-bus voor communicatie.
* **Voeding:** Zorg ervoor dat de voedingsspanning (VCC) overeenkomt met de specificaties van de modules die je gebruikt.
* **Aarding:** Alle GND-verbindingen moeten met elkaar verbonden zijn.
* **Pull-up Weerstanden:** Vergeet niet de noodzakelijke pull-up weerstanden voor de I2C-bus.
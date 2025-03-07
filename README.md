# Aardbevingsdetector

Dit project is een voorbeeldcode voor het uitlezen van een MPU6050-sensor met een Arduino en een RTC (DS3231). De code initialiseert de MPU6050-sensor en de DS3231 RTC, en leest de accelerometerwaarden uit met een interval van 10 milliseconden (100Hz sampling). De waarden en de tijd worden via de seriële monitor weergegeven.

## Omgevingssetup

### Vereisten

- Visual Studio Code (VSCode)
- PlatformIO IDE extensie voor VSCode
- Arduino board
- MPU6050-sensor
- DS3231 RTC

### Installatie van Visual Studio Code en PlatformIO

1. Download en installeer [Visual Studio Code](https://code.visualstudio.com/).
2. Open Visual Studio Code.
3. Ga naar de extensies (Ctrl+Shift+X) en zoek naar "PlatformIO IDE".
4. Installeer de "PlatformIO IDE" extensie.

### Het project clonen met GitHub in Visual Studio Code

1. Open Visual Studio Code.
2. Ga naar de bronbeheer sectie (Ctrl+Shift+G).
3. Klik op "Clone Repository".
4. Voer de URL van de GitHub repository in en druk op Enter.
5. Kies een lokale map waar je het project wilt opslaan.
6. Visual Studio Code zal het project clonen en openen in een nieuwe window.

### Initialisatie van PlatformIO voor dit project

1. Open Visual Studio Code.
2. Open de command palette (Ctrl+Shift+P) en typ `PlatformIO: Home` en selecteer het.
3. Klik op "Open Project" en selecteer de map `Aardbevingsdetector`.
4. PlatformIO zal nu de benodigde bestanden en configuraties laden.

### Aansluiting van de hardware

1. Sluit de MPU6050-sensor en de DS3231 RTC aan op de Arduino volgens de volgende verbindingen:
   - SDA op pin 32
   - SCL op pin 33
2. Zorg ervoor dat de Arduino correct is aangesloten op uw computer via een USB-kabel.

## Gebruik

1. Open het project in Visual Studio Code met PlatformIO.
2. Zorg ervoor dat de benodigde bibliotheken zijn geïnstalleerd:
   - `MPU6050_light`
   - `RTClib`
3. Upload de code naar de Arduino door op het upload-icoon in de statusbalk van PlatformIO te klikken.
4. Open de seriële monitor in de IDE.
5. Stel de baudrate in op 115200.
6. Bekijk de accelerometerwaarden en de tijd die elke 10 milliseconden worden bijgewerkt.

## Projectstructuur

### Mappen en hun functies

- **Hardware/**: Hier bevinden zich de fritzing project gegevens en overzichten van de gebruikte componenten.

- **include/**: Hier plaats je de header-bestanden (.h) die je in je project gebruikt. Dit zijn meestal je eigen header-bestanden die je gebruikt om functies en variabelen te declareren.

- **lib/**: Deze map is bedoeld voor externe bibliotheken die je project gebruikt. Je kunt hier bibliotheken plaatsen die niet via de PlatformIO Library Manager beschikbaar zijn.

- **src/**: Dit is de belangrijkste map voor je broncode. Hier plaats je je .cpp-bestanden, inclusief het hoofdprogramma (`main.cpp`).

- **test/**: Deze map is bedoeld voor unit tests. Hier kun je testbestanden plaatsen om je code te testen.

- **platformio.ini**: Dit is het configuratiebestand voor PlatformIO. Hierin specificeer je de instellingen voor je project, zoals de gebruikte board, frameworks, en bibliotheken.

- **README.md**: Dit is het documentatiebestand voor je project. Hierin kun je uitleg geven over je project, hoe het te gebruiken, en andere relevante informatie.

Hopelijk geeft dit je een goed overzicht van de projectstructuur en de functie van de verschillende mappen!

## Licentie

Dit project is gelicenseerd onder de MIT-licentie. Zie het LICENSE-bestand voor meer informatie.
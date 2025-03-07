# Project Specificaties en Todo-lijst

## Specificaties

1.  **RTC Synchronisatie via NTP:**
    * De ESP32 moet via WiFi verbinding maken met een NTP-server om de DS3231 RTC periodiek te synchroniseren.
    * Synchronisatie moet gebeuren bij het opstarten van de ESP32.
    * Daarna moet synchronisatie eenmaal per 24 uur automatisch worden uitgevoerd.
2.  **WiFi Configuratie:**
    * Als er geen opgeslagen WiFi-netwerkgegevens zijn of als de verbinding mislukt, moet de ESP32 in Access Point (AP) modus gaan.
    * In AP-modus moet een mobiele telefoon of ander apparaat verbinding kunnen maken met de ESP32 om WiFi-netwerkgegevens (SSID en wachtwoord) in te stellen via een webinterface.
    * De ingestelde wifi gegevens dienen te worden opgeslagen in het flashgeheugen van de ESP32.
3.  **Live Grafiek via Webpagina:**
    * Wanneer er een actieve WiFi-verbinding is, moet de ESP32 een webserver hosten.
    * Op een webpagina moet een live grafiek worden weergegeven van de gedetecteerde trillingen/bewegingen (accelerometerwaarden).
    * De webpagina moet toegankelijk zijn via een browser op hetzelfde netwerk.
    * De data moet in een JSON formaat beschikbaar gesteld worden.
4.  **Data opslag.**
    * De gegevens die door de MPU6050 gedetecteerd worden moeten nog steeds weggeschreven worden naar het SD kaartje.

## Todo-lijst

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
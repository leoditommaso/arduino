// Sketch to read temperature and humidity from several sensors.
// https://github.com/leoditommaso/arduino/weather_station
// Author: Leandro Di Tommaso (@leoditommaso)

// DHT library for DHT sensors.
#include "DHT.h"

// Some constants for later usage.
#define TOTAL_SENSORS       5
#define DHT_BATHROOM_PIN    2
#define DHT_BEDROOM_PIN     3
#define DHT_DININGROOM_PIN  4
#define DHT_KITCHEN_PIN     5
#define DHT_OUTDOOR_PIN     6
#define DHTTYPE_INDOOR      DHT11
#define DHTTYPE_OUTDOOR     DHT22
#define QUERY_INTERVAL      5000

// Define every sensor.
DHT dht_bathroom   (DHT_BATHROOM_PIN,   DHTTYPE_INDOOR);
DHT dht_bedroom    (DHT_BATHROOM_PIN,   DHTTYPE_INDOOR);
DHT dht_diningroom (DHT_DININGROOM_PIN, DHTTYPE_INDOOR);
DHT dht_kitchen    (DHT_BATHROOM_PIN,   DHTTYPE_INDOOR);
DHT dht_outdoor    (DHT_OUTDOOR_PIN,    DHTTYPE_OUTDOOR);

// This array will contain each sensor.
DHT sensors[TOTAL_SENSORS] = { dht_bathroom, dht_bedroom, dht_diningroom, dht_kitchen, dht_outdoor };

void setup() {
  // Setup serial port.
  Serial.begin(9600);
  // Initialize sensors.
  for (int i = 0; i < TOTAL_SENSORS; i = i + 1) {
    sensors[i].begin();
  }
}

void loop() {
  // Execute the loop code every QUERY_INTERVAL seconds.
  delay(QUERY_INTERVAL);

  // The following two arrays will store humidity and temperature information from each sensor.
  float a_hum[TOTAL_SENSORS];
  float a_temp[TOTAL_SENSORS];

  // Reads humidity and temperature from each sensor.
  for (int i = 0; i < TOTAL_SENSORS; i++) {
    a_hum[i] = sensors[i].readHumidity();
    a_temp[i] = sensors[i].readTemperature();

    // If humidity or temperature read is not a number print an error and return.
    if (isnan(a_hum[i]) || isnan(a_temp[i])) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  }

  // Print the results to serial port, each sensor information in a different line,
  // a comma separated values, with the sensor ID at the beggining, the humidity next and
  // temperature at the end.
  for (int i = 0; i < TOTAL_SENSORS; i = i + 1) {
    Serial.print(i);
    Serial.print(",");
    Serial.print(a_hum[i]);
    Serial.print(",");
    Serial.print(a_temp[i]);
    Serial.println("");
  }
}

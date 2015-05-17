// Sketch to read temperature and humidity from several sensors.
// https://github.com/leoditommaso/arduino/weather_station
// Author: Leandro Di Tommaso (@leoditommaso)

// DHT library for DHT sensors.
#include "DHT.h"

// Sensors configuration constants.
#define TOTAL_SENSORS       5
#define DHT_BATHROOM_PIN    2
#define DHT_BEDROOM_PIN     3
#define DHT_DININGROOM_PIN  4
#define DHT_KITCHEN_PIN     5
#define DHT_OUTDOOR_PIN     6
#define DHTTYPE_INDOOR      DHT11
#define DHTTYPE_OUTDOOR     DHT22

// Some other configuration constants.
#define QUERY_INTERVAL      5000
#define SERIAL_BAUD_RATE    115200

// Define every sensor.
DHT dht_bathroom   (DHT_BATHROOM_PIN,   DHTTYPE_INDOOR);
DHT dht_bedroom    (DHT_BATHROOM_PIN,   DHTTYPE_INDOOR);
DHT dht_diningroom (DHT_DININGROOM_PIN, DHTTYPE_INDOOR);
DHT dht_kitchen    (DHT_BATHROOM_PIN,   DHTTYPE_INDOOR);
DHT dht_outdoor    (DHT_OUTDOOR_PIN,    DHTTYPE_OUTDOOR);

// This array will contain each sensor.
DHT sensors[TOTAL_SENSORS] = { dht_bathroom, dht_bedroom, dht_diningroom, dht_kitchen, dht_outdoor };

// The following two arrays will store humidity and temperature information read from each sensor.
float a_hum[TOTAL_SENSORS];
float a_temp[TOTAL_SENSORS];

void setup() {
  // Setup serial port.
  Serial.begin(SERIAL_BAUD_RATE);
  // Initialize sensors.
  for (int i = 0; i < TOTAL_SENSORS; i = i + 1) {
    sensors[i].begin();
  }
}

void loop() {
  // Execute the loop code every QUERY_INTERVAL seconds.
  delay(QUERY_INTERVAL);

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

  // Initialize a new string which will hold all sensors values.
  String output = "";

  // Creates a new string holding every sensor information, separated by ';',
  // Sensor information is a comma separated values, with the sensor ID at the beggining,
  // the humidity next and temperature at the end.
  for (int i = 0; i < TOTAL_SENSORS; i = i + 1) {
    output = output + i + "," + a_hum[i] + "," + a_temp[i] + ";";
  }

  // Appends EOI special string as a final delimiter to output string.
  output = output + "EOI";

  // Print the output string to the serial port.
  Serial.println(output);

  // Waits for the print to output the information to serial port before
  // going on with program execution.
  Serial.flush();
}

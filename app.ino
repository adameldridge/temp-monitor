#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 7
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    Serial.println(F("Starting..."));

    dht.begin();
}

void loop() {
    delay(2000);

    float humidity = dht.readHumidity();
    float rawTemp = dht.readTemperature();

    if (isnan(humidity) || isnan(rawTemp)) {
        Serial.println(F("Error reading from sensor"));
        return;
    }

    float feelsLikeTemp = dht.computeHeatIndex(rawTemp, humidity, false);

    Serial.print("Humidity: ");
    Serial.print(humidity, 1);
    Serial.print("% | ");

    Serial.print("Temperature: ");
    Serial.print(rawTemp, 1);
    Serial.print("°C | ");

    Serial.print("Feels like: ");
    Serial.print(feelsLikeTemp, 1);
    Serial.println("°C | ");
}
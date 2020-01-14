#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set up sensor input
#define DHTPIN 7
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Set the LCD address to 0x27 for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

bool lcdBlinking;

void setup() {
    // Sensors
    dht.begin();

    // LCD 
    lcd.begin();
    lcd.print("Starting...");
    lcd.blink();
    lcdBlinking = true;
}

void loop() {
    
    delay(4000);
    lcd.clear();

    if(lcdBlinking){
        lcd.noBlink();
    }

    // Get temperature and humidity
    float humidity = dht.readHumidity();
    float rawTemp = dht.readTemperature();
    
    if (isnan(humidity) || isnan(rawTemp)) {
        Serial.println(F("Error reading from sensor"));
        return;
    }

    float feelsLikeTemp = dht.computeHeatIndex(rawTemp, humidity, false);

    // Print results
    displayHumidity(humidity, 0);
    displayrawTemp(rawTemp, 1);
    displayFeelTemp(feelsLikeTemp, 2);

}

void displayHumidity(float humidity, int row){
    lcd.setCursor(0, row);
    lcd.print("Humidity: ");
    lcd.print(humidity, 1);
    lcd.print("%");
}

void displayrawTemp(float rawTemp, int row){
    lcd.setCursor(0, row);
    lcd.print("Temp: ");
    lcd.print(rawTemp, 1);
    lcd.print((char)223);
    lcd.print("C");
}

void displayFeelTemp(float feelsLikeTemp, int row){
    lcd.setCursor(0, row);
    lcd.print("Feels like: ");
    lcd.print(feelsLikeTemp, 1);
    lcd.print((char)223);
    lcd.print("C");
}
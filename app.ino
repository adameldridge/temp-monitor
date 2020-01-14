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

bool firstRun;

void setup() {
    // Sensors
    dht.begin();

    // LCD 
    lcd.begin();
    lcd.print("Starting...");
    lcd.blink();
    firstRun = true;
}

void loop() {
    
    delay(4000);


    // Get temperature and humidity
    float humidity = dht.readHumidity();
    float currentTemp = dht.readTemperature();
    
    if (isnan(humidity) || isnan(currentTemp)) {
        displayError("Bad sensor reading");
        return;
    }

    // Set min and max temps
    float maxTemp;
    float minTemp;

    if(currentTemp > maxTemp || firstRun){
        maxTemp = currentTemp;
    }

    if(currentTemp < minTemp || firstRun){
        minTemp = currentTemp;
    }

    // Handle first run of loop
    if(firstRun){
        lcd.noBlink();
        lcd.clear();
        firstRun = false;
    }

    // Print results
    displayCurrentTemp(currentTemp, 0);
    displayMinTemp(minTemp, 1);
    displayMaxTemp(maxTemp, 2);
    displayHumidity(humidity, 3);
}

void displayCurrentTemp(float currentTemp, int row){
    lcd.setCursor(0, row);
    lcd.print("Cur Temp: ");
    lcd.print(currentTemp, 1);
    lcd.print((char)223);
    lcd.print("C");
}

void displayMinTemp(float minTemp, int row){
    lcd.setCursor(0, row);
    lcd.print("Min Temp: ");
    lcd.print(minTemp, 1);
    lcd.print((char)223);
    lcd.print("C ");

}

void displayMaxTemp(float maxTemp, int row){
    lcd.setCursor(0, row);
    lcd.print("Max Temp: ");
    lcd.print(maxTemp, 1);
    lcd.print((char)223);
    lcd.print("C");
}

void displayHumidity(float humidity, int row){
    lcd.setCursor(0, row);
    lcd.print("Humidity: ");
    lcd.print(humidity, 1);
    lcd.print("%");
}

void displayError(String errorMsg){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error:");
    lcd.setCursor(0, 1);
    lcd.print(errorMsg);
}


#include <Wire.h>
#include "DHT.h" 
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);  // 0x27 это адрес дисплея, адрес можно узнать через i2c scanner

void setup()
{
  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  delay(2000);
  lcd.clear();
  float h = dht.readHumidity();
  float t = dht.readTemperature(); //по Цельсию
  
  lcd.print("Temp = ");
  lcd.print(t);
  lcd.setCursor(0,1);
  lcd.print("Humidity = ");
  lcd.print(h); 
}

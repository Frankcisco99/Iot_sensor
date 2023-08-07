#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
const int DHTPin = 2;     // what digital pin we're connected to
DHT dht(DHTPin, DHTTYPE);

// Dirección I2C del LCD (pueden variar, verifica el tuyo)
#define I2C_ADDR 0x27

// Definir el número de columnas y filas del LCD
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// Inicializar el objeto LiquidCrystal_I2C
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);

void setup() {
  // Inicializar el LCD
  Serial.begin(115200);
  dht.begin();
  lcd.init();
  lcd.backlight(); // Encender el backlight (iluminación del LCD)

  // Mostrar un mensaje inicial en el LCD
  
}

void loop() {
  // Tu código puede ir aquí
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  lcd.setCursor(0, 0);
  lcd.print("Hum: ");
  lcd.print(h);
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(t);
  Serial.print(h);
  Serial.print(" ");
  Serial.println(t);
  delay(2000);
}

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <SoftwareSerial.h>
#include <MQUnifiedsensor.h>

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//Definir datos 
#define placa "Arduino UNO"
#define Voltage_Resolution 5
#define pin A0 //Analog input 0 of your arduino
#define type "MQ-135" //MQ135
#define ADC_Bit_Resolution 10 // For arduino UNO/MEGA/NANO
#define RatioMQ135CleanAir 3.6//RS / R0 = 3.6 ppm  
//#define calibration_button 13 //Pin to calibrate your sensor
const int DHTPin = 7;     // what digital pin we're connected to
DHT dht(DHTPin, DHTTYPE);
//Declarar sensor
MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);
SoftwareSerial bluetoothSerial(2, 3); // RX, TX pins for HC-05

// Dirección I2C del LCD (pueden variar, verifica el tuyo)
#define I2C_ADDR 0x27

// Definir el número de columnas y filas del LCD
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// Inicializar el objeto LiquidCrystal_I2C
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);

void setup() {
  // Inicializar el LCD
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight(); // Encender el backlight (iluminación del LCD)
  bluetoothSerial.begin(9600);
  //Modelo matematico
  MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ135.init(); 
  /*****************************  MQ Calibración ********************************************/ 
  Serial.print("Calibrating please wait.");
  float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    MQ135.update(); // Update data, the arduino will be read the voltage on the analog pin
    calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
    Serial.print(".");
  }
  MQ135.setR0(calcR0/10);
  Serial.println("  done!.");
  
  if(isinf(calcR0)) {Serial.println("Warning: Conection issue founded, R0 is infite (Open circuit detected) please check your wiring and supply"); while(1);}
  if(calcR0 == 0){Serial.println("Warning: Conection issue founded, R0 is zero (Analog pin with short circuit to ground) please check your wiring and supply"); while(1);}

}

void loop() {
  // Tu código puede ir aquí
  MQ135.update();
  MQ135.setA(110.47); MQ135.setB(-2.862); // Configurate the ecuation values to get CO2 concentration
  float CO2 = MQ135.readSensor();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  lcd.setCursor(0, 0);
  lcd.print("Hum: ");
  lcd.print(h);
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(t);
  delay(4000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Co2: ");
  lcd.print(CO2 + 400);
  // bluetoothSerial.println(CO2+400);
  // bluetoothSerial.println(t);
  // bluetoothSerial.println(h);
  String datosConcatenados = String(CO2 + 400) + " " + String(t) + " " + String(h);
  bluetoothSerial.println(datosConcatenados);
  
  delay(4000);
}

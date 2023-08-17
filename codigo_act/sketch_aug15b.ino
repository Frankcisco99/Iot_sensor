//Include the library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MQUnifiedsensor.h>
/************************Hardware Related Macros************************************/
#define         Board                   ("Arduino UNO")
#define         Pin                     (A0)  //Analog input 4 of your arduino
/***********************Software Related Macros************************************/
#define         Type                    ("MQ-9") //MQ9
#define         Voltage_Resolution      (5)
#define         ADC_Bit_Resolution      (10) // For arduino UNO/MEGA/NANO
#define         RatioMQ9CleanAir        (9.6) //RS / R0 = 60 ppm 
/*****************************Globals***********************************************/
//Declare Sensor
// Dirección I2C del LCD (pueden variar, verifica el tuyo)
#define I2C_ADDR 0x27

// Definir el número de columnas y filas del LCD
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// Inicializar el objeto LiquidCrystal_I2C
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);
MQUnifiedsensor MQ9(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight(); // Encender el backlight (iluminación del LCD)
  MQ9.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ9.init();
  float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    MQ9.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ9.calibrate(RatioMQ9CleanAir);
  }
  MQ9.setR0(calcR0/10);
}

void loop() {
  // put your main code here, to run repeatedly:
  MQ9.update();
  MQ9.setA(1000.5); MQ9.setB(-2.186); // Configure the equation to to calculate LPG concentration
  float LPG = MQ9.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  MQ9.setA(4269.6); MQ9.setB(-2.648); // Configure the equation to to calculate LPG concentration
  float CH4 = MQ9.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  String data = String(LPG) + " " + String(CH4);
  lcd.setCursor(0, 0);
  lcd.print("LPG: ");
  lcd.print(LPG);
  lcd.setCursor(0, 1);
  lcd.print("CH4: ");
  lcd.print(CH4);
  Serial.println(data);
  delay(500); //Sampling frequency
}

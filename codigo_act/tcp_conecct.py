# Importing Libraries 
import serial 
import time 
arduino = serial.Serial(port='COM8', baudrate=9600, timeout=.1)  
while True:
    if arduino.in_waiting > 0:
            dato_recibido = arduino.readline().decode('utf-8').strip()
            if len(dato_recibido):
                lpg, ch4 = map(float, dato_recibido.split())
                print(f"LPG: {lpg} PPM")
                print(f"CH4: {ch4} PPM")


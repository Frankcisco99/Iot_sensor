# Importing Libraries 
import serial 
import time 
arduino = serial.Serial(port='COM3', baudrate=115200, timeout=.1)  
while True: 
    time.sleep(2)
    data = arduino.readline()
    dato_sensores = data.decode().strip()
    
    if len(dato_sensores) >= 2:
        dato1, dato2 = map(float, dato_sensores.split())
        print(f"Humedad {dato1} %")
        print(f"Temperatura {dato2} °C")

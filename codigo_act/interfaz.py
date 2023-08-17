import serial
import tkinter as tk
import ttkbootstrap as ttk

# Configurar la conexión serial con Arduino
arduino = serial.Serial(port='COM7', baudrate=9600, timeout=.1)

# Crear la ventana tkinter
window = ttk.Window(themename="darkly")
window.title("Codigo Futuro")
window.geometry('800x400')

titulo = ttk.Label(master=window, text="Sensor MQ-9", font="Calibri 24 bold")
titulo.pack(pady=20)

div = ttk.Frame(master=window)

progress = ttk.Meter(master=div, bootstyle="success", subtext="Co2 (PPM)")
progress2 = ttk.Meter(master=div, bootstyle="warning", subtext="Temp (°C)")
progress3 = ttk.Meter(master=div, bootstyle="danger", subtext="Hum (%)")
div.pack()
progress.pack(side="left", padx=10)
progress2.pack(side="left")
progress3.pack(side="left", padx=10)

def update_values():
    if arduino.in_waiting > 0:
        dato_recibido = arduino.readline().decode('utf-8').strip()
        if len(dato_recibido):
            co2, temp, hum = map(float, dato_recibido.split())
            progress.configure(amountused = co2) 
            progress2.configure(amountused = temp) 
            progress3.configure(amountused = hum)
    window.after(500, update_values)  # Actualizar cada segundo

update_values()  # Iniciar la actualización de valores

window.mainloop()

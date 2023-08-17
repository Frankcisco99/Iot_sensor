import serial
import tkinter as tk
import threading

def serial_monitor():
    global co2, temp, hum
    serial_port = serial.Serial('COM7', 9600)  # Asegúrate de que el puerto COM sea el correcto

    while running:
        if serial_port.in_waiting > 0:
            dato_recibido = serial_port.readline().decode('utf-8').strip()
            co2, temp, hum = map(float, dato_recibido.split())
            print(f"Co2: {co2} PPM")
            print(f"Temperatura: {temp} °C")
            print(f"Humedad: {hum} %")

def update_values():
    co2_label.config(text=f"CO2: {co2} PPM")
    temp_label.config(text=f"Temperatura: {temp} °C")
    hum_label.config(text=f"Humedad: {hum} %")
    root.after(1000, update_values)

def on_closing():
    global running
    running = False
    root.destroy()

running = True
co2, temp, hum = 0, 0, 0

serial_thread = threading.Thread(target=serial_monitor)
serial_thread.start()

root = tk.Tk()
root.title("Sensor Data Monitor")

co2_label = tk.Label(root, text="CO2: 0 PPM")
co2_label.pack(padx=10, pady=5)

temp_label = tk.Label(root, text="Temperatura: 0 °C")
temp_label.pack(padx=10, pady=5)

hum_label = tk.Label(root, text="Humedad: 0 %")
hum_label.pack(padx=10, pady=5)

update_values()

root.protocol("WM_DELETE_WINDOW", on_closing)
root.mainloop()

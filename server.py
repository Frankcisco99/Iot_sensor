import serial
import tkinter as tk
import threading

def serial_monitor():
    global current_value
    serial_port = serial.Serial('COM5', 9600)  # Ajusta el nombre del puerto COM según tu configuración

    while running:
        if serial_port.in_waiting > 0:
            current_value = int(serial_port.readline().decode().strip())

def update_value():
    value_label.config(text=f"Valor actual: {current_value}")
    root.after(1000, update_value)

def on_closing():
    global running
    running = False
    root.destroy()

running = True
current_value = 0

serial_thread = threading.Thread(target=serial_monitor)
serial_thread.start()

root = tk.Tk()
root.title("Serial Monitor")

value_label = tk.Label(root, text="Valor actual: 0")
value_label.pack(padx=10, pady=10)

update_value()

root.protocol("WM_DELETE_WINDOW", on_closing)
root.mainloop()

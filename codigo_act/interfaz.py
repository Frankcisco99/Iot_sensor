import tkinter as tk
import ttkbootstrap as ttk

window = ttk.Window(themename="darkly")
window.title("Codigo Futuro")
window.geometry('600x400')

titulo = ttk.Label(master=window,text="Sensor MQ-9", font="Calibri 24 bold")
titulo.pack(pady=20)
div = ttk.Frame(master=window)

progress = ttk.Meter(master=div, bootstyle="success", subtext="CH4 (PPM)")
progress2 = ttk.Meter(master=div, bootstyle="warning", subtext="LPG (PPM)")
div.pack()
progress.pack( side="left", padx=10)
progress2.pack(side="left")
window.mainloop()
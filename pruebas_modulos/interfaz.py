import tkinter as tk
import json

# Cargar el archivo JSON con los códigos de error y descripciones
with open('error.json', 'r') as file:
    data = json.load(file)

def obtener_descripcion():
    codigo = codigo_entry.get().upper()  # Convertir el código a mayúsculas para ser insensible a mayúsculas/minúsculas
    print(codigo)
    descripcion = "Código de error no encontrado"
    for error in data['Errores']:
        if error['codigo'] == codigo:
            descripcion = error.get('desc', "Descripción no encontrada")
            break
    descripcion_label.config(text=descripcion)

# Crear la ventana principal
ventana = tk.Tk()
ventana.title("Búsqueda de Código de Error")

# Crear y configurar widgets
codigo_label = tk.Label(ventana, text="Ingrese el código de error:")
codigo_label.pack()

codigo_entry = tk.Entry(ventana)
codigo_entry.pack()

buscar_button = tk.Button(ventana, text="Buscar Descripción", command=obtener_descripcion)
buscar_button.pack()

descripcion_label = tk.Label(ventana, text="")
descripcion_label.pack()

# Ejecutar la aplicación
ventana.mainloop()

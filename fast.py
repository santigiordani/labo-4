import numpy as np

# Ruta al archivo
file_path = 'data/c_alta.txt'

# Leer los datos desde el archivo
with open(file_path, 'r') as f:
    data = [float(line.strip()) for line in f if line.strip()]

# Convertir a array de NumPy (por comodidad)
data_array = np.array(data)

# Calcular promedio y varianza muestral (ddof=1 para n-1)
mean = np.mean(data_array)
variance = np.var(data_array, ddof=1)

print(f'Promedio: {mean:.6e}')
print(f'Varianza muestral: {variance:.6e}')

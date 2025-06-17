import re
import matplotlib.pyplot as plt

# Inicializar estructuras de datos
n_values = []
results = {
    "ARR_OPT": [],
    "ARR": [],
    "HEAP_OPT": [],
    "HEAP": []
}

# Leer el archivo
with open("log.txt", "r") as file:
    lines = file.readlines()

current_n = None
pattern_n = re.compile(r"=== Results for N = (\d+) ===")
pattern_result = re.compile(r"(\w+): ran \d+ times, avg = ([\d.]+) ms")

for line in lines:
    line = line.strip()

    # Ignorar la sección de promedios finales
    if "=== Overall Averages" in line:
        break

    match_n = pattern_n.match(line)
    if match_n:
        current_n = int(match_n.group(1))
        n_values.append(current_n)
        continue

    match_result = pattern_result.match(line)
    if match_result and current_n is not None:
        algo, avg_time = match_result.groups()
        if algo in results:
            results[algo].append(float(avg_time))

# Verificación básica
for algo, times in results.items():
    if len(times) != len(n_values):
        print(f"Advertencia: {algo} tiene {len(times)} valores, pero hay {len(n_values)} tamaños N.")

# Graficar resultados
plt.figure(figsize=(10, 6))
for algo, times in results.items():
    if len(times) == len(n_values):  # Evita errores si alguna lista está desalineada
        plt.plot(n_values, times, marker='o', label=algo)

plt.xlabel('Tamaño de entrada N')
plt.ylabel('Tiempo promedio (ms)')
plt.title('Comparación de algoritmos por tamaño de entrada')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

import re
import matplotlib.pyplot as plt
import sys

# find_calls.py
# code based on graph.py <Ateuluz>

# Inicializar estructuras de datos
n_values = []
results = {
    "ARR_OPT": [],
    "ARR": [],
    "HEAP_OPT": [],
    "HEAP": []
}
diff_arr = []
diff_heap = []
# Leer el archivo
with open("log.txt", "r") as file:
    lines = file.readlines()

current_n = None
pattern_n:re = re.compile(r"=== Finds for N = (\d+) ===")
pattern_result = re.compile(r"(\w+): find calls: (\d+)")

for line in lines:
    line = line.strip()

    # Ignorar la sección de promedios finales
    if "=== Overall Averages" in line:
        break

    match_n = pattern_n.match(line)
    print("Processing line:", line, "Match N:", match_n)
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


for i in range(len(results["ARR_OPT"])):
    # print("----------------------------")
    # if results["ARR"][i] - results["ARR_OPT"][i] < 0:
        # print(f"Diferencia negativa encontrada en ARR:\n\tindice : {i}", f"no opt = {results["ARR"][i]}", "vs", f"opt = {results["ARR_OPT"][i]}")
        diff_arr.append((results["ARR"][i] - results["ARR_OPT"][i], i))
    # if results["HEAP"][i] - results["HEAP_OPT"][i] < 0:
        # print(f"Diferencia negativa encontrada en HEAP:\n\tindice = {i}", f"no opt = {results["HEAP"][i]}", "vs", f"opt = {results["HEAP_OPT"][i]}")
        diff_heap.append((results["HEAP"][i] - results["HEAP_OPT"][i], i))

print("Diferencias entre ARR_OPT y ARR:")
for i in range(len(diff_arr)):
    print(f"\t{diff_arr[i]}")
print("Diferencias entre HEAP_OPT y HEAP:")
for i in range(len(diff_heap)):
    print(f"\t{diff_heap[i]}")

# Graficar resultados
cmp = ""
if sys.argv[1] == "heap": cmp = "HEAP"
elif sys.argv[1] == "arr": cmp = "ARR"
    
plt.figure(figsize=(10, 6))
for algo, times in results.items():
    if algo[:len(cmp)] != cmp: continue
    if len(times) == len(n_values):  # Evita errores si alguna lista está desalineada
        plt.plot(n_values, times, marker='o', label=algo)

plt.xlabel('Tamaño de entrada N')
plt.ylabel('Llamadas a find')
plt.title('Comparación de algoritmos con y sin optimización según tiempo por tamaño de entrada')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

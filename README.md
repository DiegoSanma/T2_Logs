# T2_Logs

# Árbol de Cobertura Mínima con el Algoritmo de Kruskal

## Descripción General

Este proyecto implementa cuatro variantes del algoritmo de Kruskal para calcular el Árbol de Cobertura Mínima (MST) en un grafo completo de puntos aleatorios en el cuadrado \[0,1\]²:

- **ARR_OPT**: Arreglo ordenado + path-compression  
- **ARR**: Arreglo ordenado sin optimizaciones  
- **HEAP_OPT**: Min-heap + path-compression  
- **HEAP**: Min-heap sin optimizaciones  

Medimos el tiempo de ejecución para distintos tamaños de entrada y comparamos su rendimiento.

## Estructura del Repositorio

```text
.
├── geometry.h / geometry.cpp      # Definiciones de Punto, InfoEntrePuntos, ArbolCoberturaMinimo
├── utils.h    / utils.cpp         # Generación de puntos y construcción de aristas
├── union_find.h / union_find.cpp  # Estructura Union-Find con path-compression
├── kruskal.h  / kruskal.cpp       # Implementaciones de Kruskal (array / heap)
├── main.cpp                       # Programa principal de experimentos
└── README.md                      # Este documento
```

## Ejecución de experimentos

### Windows

Para ejecutar el código, se debe primero compilar el programa. Para esto, se debe realizar una llamada a **./build.bat** que creará el ejecutable "experiments.exe", lo
corerrá y almacenará resultados, generando los gráficos correspondientes en secuencia. Para ver los resultados numericos, se puede consultar el archivo **log.txt**.

### Linux
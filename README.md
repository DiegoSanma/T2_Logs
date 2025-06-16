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
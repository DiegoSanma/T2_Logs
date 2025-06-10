#!/usr/bin/env bash
#
# build.sh — compila todos los .cpp y enlaza el ejecutable de experimentos

set -euo pipefail

# —— Configuración de compilador ——
CXX=${CXX:-g++}
CXXFLAGS="-std=c++17 -O2 -Wall -Wextra -I."

# —— Fuentes & binario ——
SRCS=(
  crear_puntos.cpp
  geometry.cpp
  union_find.cpp
  utils.cpp
  kruskal.cpp
  main.cpp
)
TARGET="experiments"

# —— Limpieza —— 
echo "Cleaning old build artifacts..."
rm -f "${SRCS[@]/%.cpp/.o}" "$TARGET"

# —— Compilación —— 
echo "Compiling sources..."
for src in "${SRCS[@]}"; do
  obj="${src%.cpp}.o"
  echo "  $CXX $CXXFLAGS -c $src -o $obj"
  $CXX $CXXFLAGS -c "$src" -o "$obj"
done

# —— Enlazado —— 
echo "Linking into $TARGET..."
$CXX $CXXFLAGS "${SRCS[@]/%.cpp/.o}" -o "$TARGET"

echo "Build complete! Run ./$TARGET to execute your experiments."

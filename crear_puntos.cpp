/*───────────────────────────────────────────────────────────────*
 *  crear_array.cpp   — fast, cross‑platform generator
 *  Keeps the same CrearPuntos interface; no other code changes
 *  required in your project or Docker setup.
 *───────────────────────────────────────────────────────────────*/

 #include "crear_puntos.h"

 #include <cstdint>
 #include <cstdlib>
 #include <cstring>
 #include <fstream>
 #include <iostream>
 #include <random>
 #include <vector>
 #include <queue>
 
 #ifndef _WIN32
 #  include <sys/mman.h>
 #  include <sys/stat.h>
 #  include <fcntl.h>
 #  include <unistd.h>
 #  include <thread>
 #endif
 
/*────────  constructor & simple accessors (unchanged)  ───────*/
CrearPuntos::CrearPuntos(const char* fnamePuntos, const char* fnameDistancias, int N, int X)
    : filePuntos(fnamePuntos), fileDistancias(fnameDistancias), N(N), X(X) {}
const char* CrearPuntos::getFilePuntos() const { return filePuntos; }
const char* CrearPuntos::getFileDistancias() const { return fileDistancias; }
int  CrearPuntos::getN()  const { return N; }
int  CrearPuntos::getX()  const { return X; }
void CrearPuntos::setX(int x)   { X = x;   }

#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <cstdio>      // std::remove
#include <cstdint>
#include <algorithm>   // std::min

struct Punto {
    double x;
    double y;

    double distancia(const Punto& otro) const {
        return std::sqrt((x - otro.x) * (x - otro.x) + (y - otro.y) * (y - otro.y));
    }
};

struct InfoEntrePuntos {
    Punto p1;
    Punto p2;
    double distancia;
};

struct Comparador {
    bool operator()(const InfoEntrePuntos& a, const InfoEntrePuntos& b) const {
        return a.distancia > b.distancia; // menor distancia → más prioritario
    }
};

int CrearPuntos::CrearPuntosNArreglo() const
{
    // Eliminar el archivo si ya existe
    if (std::remove(filePuntos) == 0) {
        std::cout << "Archivo existente eliminado: " << filePuntos << std::endl;
    } else {
        std::cerr << "No se pudo eliminar el archivo (puede que no exista): " << filePuntos << std::endl;
    }
    if (std::remove(fileDistancias) == 0) {
        std::cout << "Archivo existente eliminado: " << fileDistancias << std::endl;
    } else {
        std::cerr << "No se pudo eliminar el archivo (puede que no exista): " << fileDistancias << std::endl;
    }
    if (N == 0) {
        std::cerr << "Intestaste de crear 0 puntos\n";
        return 1;
    }

    std::ofstream outPuntos(filePuntos, std::ios::binary | std::ios::trunc);
    if (!outPuntos) {
        std::cerr << "No se pudo abrir " << filePuntos << '\n';
        return 1;
    }
    std::ofstream outDistancias(fileDistancias, std::ios::binary | std::ios::trunc);
    if (!outDistancias) {
        std::cerr << "No se pudo abrir " << fileDistancias << '\n';
        return 1;
    }
    std::vector<Punto> puntos(N);
    std::mt19937_64 rng{ std::random_device{}() };
    std::uniform_real_distribution<double> distX(0.0, 1.0);  // Distribución uniforme para X
    std::uniform_real_distribution<double> distY(0.0, 1.0); // Distribución uniforme para Y
    // Generar N puntos aleatorios usando las distribuciones de arriba
    for (auto& p : puntos) {
        p = { distX(rng), distY(rng) };
    }
    //Ahora, calculo la matriz de distancias entre todos mis puntos
    std::vector<InfoEntrePuntos> distancias;
    distancias.reserve((N * (N - 1)) / 2);  // espacio exacto para la mitad de la matriz
    for (uint64_t i = 0; i < N; ++i) {
        for (uint64_t j = i + 1; j < N; ++j) {
            double d = puntos[i].distancia(puntos[j]);
            InfoEntrePuntos info = { puntos[i], puntos[j], d };
            distancias.push_back(info);
        }
    }

    // (Opcional) Ordenar por distancia
    std::sort(distancias.begin(), distancias.end(),
              [](const InfoEntrePuntos& a, const InfoEntrePuntos& b) {
                  return a.distancia < b.distancia;
              });

    uint64_t total_pares = distancias.size();
    outDistancias.write(reinterpret_cast<const char*>(&total_pares), sizeof(uint64_t));

    outPuntos.close();
    outDistancias.close();
    return 0;
}

int CrearPuntos::CrearPuntosNHeap() const {
    if (std::remove(fileDistancias) == 0) {
        std::cout << "Archivo existente eliminado: " << fileDistancias << std::endl;
    } else {
        std::cerr << "No se pudo eliminar el archivo (puede que no exista): " << fileDistancias << std::endl;
    }
    if (N == 0) {
        std::cerr << "Intestaste de crear 0 puntos\n";
        return 1;
    }
    std::ofstream outDistancias(fileDistancias, std::ios::binary | std::ios::trunc);
    if (!outDistancias) {
        std::cerr << "No se pudo abrir " << fileDistancias << '\n';
        return 1;
    }
    std::vector<Punto> puntos(N);
    std::mt19937_64 rng{ std::random_device{}() };
    std::uniform_real_distribution<double> distX(0.0, 1.0);  // Distribución uniforme para X
    std::uniform_real_distribution<double> distY(0.0, 1.0); // Distribución uniforme para Y
    // Generar N puntos aleatorios usando las distribuciones de arriba
    for (auto& p : puntos) {
        p = { distX(rng), distY(rng) };
    }
    //Ahora, calculo la matriz de distancias entre todos mis puntos
    std::priority_queue<InfoEntrePuntos, std::vector<InfoEntrePuntos>, Comparador> heap;
    for (uint64_t i = 0; i < N; ++i) {
        for (uint64_t j = i + 1; j < N; ++j) {
            double d = puntos[i].distancia(puntos[j]);
            InfoEntrePuntos info = { puntos[i], puntos[j], d };
            heap.push(info);
        }
    }

    uint64_t total_pares = heap.size();
    outDistancias.write(reinterpret_cast<const char*>(&total_pares), sizeof(uint64_t));

    outDistancias.close();
    return 0;
}
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
CrearPuntos::CrearPuntos(const char* fnamePuntos, const char* fnameDistancias, int N)
    : filePuntos(fnamePuntos), fileDistancias(fnameDistancias), N(N) {}
const char* CrearPuntos::getFilePuntos() const { return filePuntos; }
const char* CrearPuntos::getFileDistancias() const { return fileDistancias; }
int  CrearPuntos::getN()  const { return N; }
std::vector<Punto> CrearPuntos::getPuntos() {
    if (puntos.empty()) {
        std::cerr << "Error: No se han creado puntos." << std::endl;
    }
    return puntos; // Retorna los puntos generados
}

std::vector<InfoEntrePuntos> CrearPuntos::getArregloDistancias() {
    if (arreglo_distancias.empty()) {
        std::cerr << "Error: No se han calculado distancias." << std::endl;
    }
    return arreglo_distancias; // Retorna el arreglo de distancias
}

std::priority_queue<InfoEntrePuntos, std::vector<InfoEntrePuntos>, Comparador> CrearPuntos::getHeapDistancias() {
    if (heap_distancias.empty()) {
        std::cerr << "Error: No se han calculado distancias." << std::endl;
    }
    return heap_distancias; // Retorna el heap de distancias
}



int CrearPuntos::CrearPuntosNArreglo()
{
    std::vector<Punto> puntos_nuevos(N);
    std::mt19937_64 rng{ std::random_device{}() };
    std::uniform_real_distribution<double> distX(0.0, 1.0);  // Distribución uniforme para X
    std::uniform_real_distribution<double> distY(0.0, 1.0); // Distribución uniforme para Y
    // Generar N puntos aleatorios usando las distribuciones de arriba
    int ids = 0; // Contador para asignar IDs únicos a los puntos
    for (auto& p : puntos_nuevos) {
        p = Punto(distX(rng), distY(rng),&p,ids++); // Crea cada punto único
    }
    this->puntos = puntos_nuevos; // Guardar los puntos generados en el objeto
    //Ahora, calculo la matriz de distancias entre todos mis puntos
    std::vector<InfoEntrePuntos> distancias;
    distancias.reserve((N * (N - 1)) / 2);  // espacio exacto para la mitad de la matriz
    for (double i = 0; i < N; ++i) {
        for (double j = i + 1; j < N; ++j) {
            double d = puntos[i].distancia(puntos[j]);
            InfoEntrePuntos info = { &puntos[i], &puntos[j], d };
            distancias.push_back(info);
        }
    }

    // (Opcional) Ordenar por distancia
    std::sort(distancias.begin(), distancias.end(),
              [](const InfoEntrePuntos& a, const InfoEntrePuntos& b) {
                  return a.distancia < b.distancia;
              });
    this->arreglo_distancias = distancias; // Guardar el arreglo de distancias en el objeto
    return 0;
}

int CrearPuntos::CrearPuntosNHeap(){
    if (std::remove(fileDistancias) == 0) {
        std::cout << "Archivo existente eliminado: " << fileDistancias << std::endl;
    } else {
        std::cerr << "No se pudo eliminar el archivo (puede que no exista): " << fileDistancias << std::endl;
    }
    if (std::remove(filePuntos) == 0) {
        std::cout << "Archivo existente eliminado: " << filePuntos << std::endl;
    } else {
        std::cerr << "No se pudo eliminar el archivo (puede que no exista): " << filePuntos << std::endl;
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
    std::vector<Punto> puntos_nuevos(N);
    std::mt19937_64 rng{ std::random_device{}() };
    std::uniform_real_distribution<double> distX(0.0, 1.0);  // Distribución uniforme para X
    std::uniform_real_distribution<double> distY(0.0, 1.0); // Distribución uniforme para Y
    // Generar N puntos aleatorios usando las distribuciones de arriba
    int ids = 0; // Contador para asignar IDs únicos a los puntos
    for (auto& p : puntos) {
        p = Punto(distX(rng), distY(rng),&p,ids++); // Crea cada punto único
    }
    //Ahora, calculo la matriz de distancias entre todos mis puntos
    std::priority_queue<InfoEntrePuntos, std::vector<InfoEntrePuntos>, Comparador> heap;
    for (double i = 0; i < N; ++i) {
        for (double j = i + 1; j < N; ++j) {
            double d = puntos[i].distancia(puntos[j]);
            InfoEntrePuntos info = {&puntos[i],&puntos[j], d };
            heap.push(info);
        }
    }
    this->heap_distancias = heap; // Guardar el heap de distancias en el objeto
    return 0;
}
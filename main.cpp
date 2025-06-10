#include "crear_puntos.h"
#include <iostream>
#include <csignal>
#include <cstdio>
#include <chrono>

#include <chrono>
#include <ctime>
#include <iomanip>

#define M       50  //50mb
#define B       4096 //4096kb
#define Xtest   60 //Tamaño de arreglo para cálculo de aridad
#define Default 50 //Aridad óptima en caso de no correr código con find alpha

// 0: no corre esa prueba, 1: sí la corre
#define RunAll 1 //Corre todas las pruebas
#define RunOptiHeap 1 //Corre la prueba de optimización de find con un heap
#define RunOptiArreglo 1 //Corre la prueba de optimización de find con un arreglo
#define RunHeap 0 //Corre la prueba sin la optimización con un heap
#define RunArreglo 1 //Corre la prueba sin la optimización con un arreglo

int nlogs = 0; // número de logs generados

static const char* FILE_ALPHA   = "arreglos_aridad.bin";

static void delete_temp_files()
{
    std::remove(FILE_ALPHA);
}

int main() {
    
    std::cout << "Hola desde Docker!" << std::endl;
    std::signal(SIGINT,  [](int){ delete_temp_files(); std::exit(130); });
    std::signal(SIGTERM, [](int){ delete_temp_files(); std::exit(143); });
    
    // Primero, inicializo la clase que crea el arreglo
    const char * filePuntos = "puntos.bin";
    const char * fileDistancias = "distancias.bin";
    CrearPuntos creador(filePuntos, fileDistancias, 32, Xtest);

    // bool findAplpha;
    // std::cout << "¿Quieres encontrar la aridad? (X=" << Xtest << ") [1: sí, 0: no]: ";
    // std::cin >> findAplpha;
    int alfa;
    if (RunOptiArreglo||RunAll) {
        std::cout << "Parto creando los puntos" << std::endl;
        int result = creador.CrearPuntosNArreglo();
        if (result != 0) {
            std::cerr << "Error al crear puntos: " << result << std::endl;
            return result;
        }

    }

    if (RunOptiHeap||RunAll) {
        std::cout << "Parto creando los puntos en un heap" << std::endl;
        int result = creador.CrearPuntosNHeap();
        if (result != 0) {
            std::cerr << "Error al crear puntos en un heap: " << result << std::endl;
            return result;
        }
    }

    return 0;
}
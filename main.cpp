#include "crear_puntos.h"
#include "kruskal.h"
#include "kruskal_opti.h"
#include <iostream>
#include <csignal>
#include <cstdio>
#include <chrono>
#include <queue>

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
#define RunHeap o //Corre la prueba sin la optimización con un heap
#define RunArreglo 1 //Corre la prueba sin la optimización con un arreglo

int nlogs = 0; // número de logs generados


int main() {
    
    std::cout << "Hola desde Docker!" << std::endl;




    if (RunOptiArreglo||RunAll) {
        double N = 16;
        //for(int i = 5;i<=12;i++) {
            N *= 2;
          //  for(int j = 0; j < 3; j++) {
                std::cout << "Parto creando los puntos en un arreglo de tamaño " << N << std::endl;
                CrearPuntos creador("puntos.txt", "distancias.txt", N);
                //Inicio el tiempo de ejecución
                auto start = std::chrono::high_resolution_clock::now();
                int result = creador.CrearPuntosNArreglo();
                if (result != 0) {
                    std::cerr << "Error al crear puntos en un arreglo: " << result << std::endl;
                    return result;
                }
                int tamaño_arbol = 0;
                KruskalOpti kruskal(creador.getPuntos());
                while (tamaño_arbol < N - 1) {
                    InfoEntrePuntos arista;
                    std::vector<InfoEntrePuntos> distancias = creador.getArregloDistancias();
                    arista = distancias.front(); // Obtiene la arista con menor distancia
                    if (kruskal.findArbolMinimo(&arista)) {
                        tamaño_arbol++;
                    }
                    distancias.erase(distancias.begin()); // Elimina la arista del arreglo
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                std::cout << "Tiempo de ejecución con arreglo: " << duration << " ms" << std::endl;
            //}
        //}
    }

    if (RunOptiHeap||RunAll) {
double N = 16;
        //for(int i = 5;i<=12;i++) {
            N *= 2;
          //  for(int j = 0; j < 3; j++) {
                std::cout << "Parto creando los puntos en un arreglo de tamaño " << N << std::endl;
                CrearPuntos creador("puntos.txt", "distancias.txt", N);
                //Inicio el tiempo de ejecución
                auto start = std::chrono::high_resolution_clock::now();
                int result = creador.CrearPuntosNArreglo();
                if (result != 0) {
                    std::cerr << "Error al crear puntos en un arreglo: " << result << std::endl;
                    return result;
                }
                int tamaño_arbol = 0;
                KruskalOpti kruskal(creador.getPuntos());
                while (tamaño_arbol < N - 1) {
                    InfoEntrePuntos arista;
                    std::priority_queue<InfoEntrePuntos, std::vector<InfoEntrePuntos>, Comparador> distancias = creador.getHeapDistancias();
                    arista = distancias.top(); // Obtiene la arista con menor distancia
                    if (kruskal.findArbolMinimo(&arista)) {
                        tamaño_arbol++;
                    }
                    distancias.pop(); // Elimina la arista del heap
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                std::cout << "Tiempo de ejecución con arreglo: " << duration << " ms" << std::endl;
            //}
        //}
    }

    return 0;
}
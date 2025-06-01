#include "kruskal.h"

// Constructor de Kruskal que inicializa los grupos con los puntos dados
Kruskal::Kruskal(const std::vector<Punto>& puntos) : grupos(puntos), n(puntos.size()) {
    arbol_minimo.reserve(n - 1); // Reservar espacio para el árbol mínimo
}

//Función que actualiza la raíz de un punto
void Kruskal::setRaiz(Punto* i, Punto* raiz) {
    i->raiz = raiz;
}

// Función que retorna el árbol mínimo cobertor
std::vector<InfoEntrePuntos> Kruskal::getArbolMinimo() {
    return arbol_minimo; 
}

//Función que realiza la unión de dos puntos en el algoritmo de Kruskal
//Siempre se va a a llamar cuando los dos puntos no estén en el mismo grupo
void Kruskal::Union(Punto* i, Punto* j) {
    // Unir los grupos de i y j
    if (i->tamaño < j->tamaño) {
        setRaiz(i, j->raiz);
        j->tamaño += i->tamaño;
    } else {
        setRaiz(j, i->raiz);
        i->tamaño += j->tamaño;
    }
};
// Función que revisa si el siguiente arista pertenece al árbol mínimo
//Retorna 1 si la arista se agrega al árbol mínimo, 0 si no se agrega
int Kruskal::findArbolMinimo(InfoEntrePuntos* arista) {
    Punto* p1 = arista->p1;
    Punto* p2 = arista->p2;

    // Encontrar las raíces de los puntos
    Punto* raiz1 = find(p1);
    Punto* raiz2 = find(p2);

    // Si las raíces son diferentes, unir los grupos
    if (!(raiz1->iguales(*raiz2))) {
        Union(raiz1, raiz2);
        arbol_minimo.push_back(*arista); // Agregar la arista al árbol mínimo
        return 1; // Se agregó al árbol mínimo
    }
    return 0; // No se agregó al árbol mínimo
}


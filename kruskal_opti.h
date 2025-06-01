#ifndef KRUSKAL_OPTI_H
#define KRUSKAL_OPTI_H

#include "crear_puntos.h"
#include "puntos.h"
#include "kruskal.h"

class KruskalOpti : public Kruskal {
public:
    KruskalOpti(const std::vector<Punto>& puntos);

    Punto *find(Punto* i) override;
};

#endif
#ifndef NODOAVL_H
#define NODOAVL_H

#include "paciente.h"

struct nodoAVL {
    paciente* dato;
    nodoAVL* izquierdo;
    nodoAVL* derecho;
    int altura;

    nodoAVL(paciente* p) : dato(p), izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

#endif
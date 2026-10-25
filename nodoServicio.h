#ifndef NODOSERVICIO_H
#define NODOSERVICIO_H

#include <string>
#include "arbolAVL.h"

struct nodoServicio {
    std::string nombreS;
    arbolAVL pacientesEnServicio;
    nodoServicio* next;

    nodoServicio(std::string nombre) : nombreS(nombre), next(nullptr) {}
};

#endif
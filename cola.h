#ifndef COLA_H
#define COLA_H

#include "nodoPaciente.h"
#include <string>

class cola {
private:
    nodoPaciente* frente;
    nodoPaciente* final;
    int cant;

public:
    cola();
    ~cola();

    void encolar(paciente* p);
    paciente* desencolar();
    bool estaVacia();
    int getCantidad();
    void mostrarCola();
    bool buscarPaciente(const std::string& id);
};

#endif
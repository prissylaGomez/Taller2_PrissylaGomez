#ifndef NODOPACIENTE_H
#define NODOPACIENTE_H

#include "paciente.h"

struct nodoPaciente {
    paciente* nPaciente;
    nodoPaciente* next;

    nodoPaciente(paciente* p) : nPaciente(p), next(nullptr) {}
};

#endif
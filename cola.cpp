#include "cola.h"
#include <iostream>

cola::cola() : frente(nullptr), final(nullptr), cant(0) {}

cola::~cola() {
    while (!estaVacia()) {
        paciente* p = desencolar();
        delete p;
    }
}

void cola::encolar(paciente* p) {
    nodoPaciente* nuevoNodo = new nodoPaciente(p);
    if (estaVacia()) {
        frente = final = nuevoNodo;
    } else {
        final->next = nuevoNodo;
        final = nuevoNodo;
    }
    cant++;
}

paciente* cola::desencolar() {
    if (estaVacia()) {
        return nullptr;
    }
    nodoPaciente* nodotemp = frente;
    paciente* p = nodotemp->nPaciente;
    frente = frente->next;
    if (frente == nullptr) {
        final = nullptr;
    }
    delete nodotemp;
    cant--;
    return p;
}

bool cola::estaVacia() {
    return frente == nullptr;
}

int cola::getCantidad() {
    return cant;
}

void cola::mostrarCola() {
    if (estaVacia()) {
        std::cout << "No hay pacientes en la cola." << std::endl;
        return;
    }
    nodoPaciente* actual = frente;
    int numAtencion = 1;
    std::cout << "Fila de pacientes" << std::endl;
    std::cout << "Numero de atencion/id/nombre" << std::endl;
    while (actual != nullptr) {
        std::cout << numAtencion << ". " << actual->nPaciente->getId() << ", " << actual->nPaciente->getNombre() << std::endl;
        actual = actual->next;
        numAtencion++;
    }
}

bool cola::buscarPaciente(const std::string& id) {
    nodoPaciente* actual = frente;
    while (actual != nullptr) {
        if (actual->nPaciente->getId() == id) {
            return true;
        }
        actual = actual->next;
    }
    return false;
}
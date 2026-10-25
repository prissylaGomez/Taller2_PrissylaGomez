#include "servicios.h"
#include <iostream>

servicios::servicios() : inicio(nullptr) {}

servicios::~servicios() {
    nodoServicio* actual = inicio;
    while (actual != nullptr) {
        nodoServicio* siguiente = actual->next;
        delete actual;
        actual = siguiente;
    }
}

void servicios::agregarServicio(std::string nombre) {
    nodoServicio* nuevo = new nodoServicio(nombre);
    if (inicio == nullptr) {
        inicio = nuevo;
    } else {
        nodoServicio* actual = inicio;
        while (actual->next != nullptr) {
            actual = actual->next;
        }
        actual->next = nuevo;
    }
}

nodoServicio* servicios::buscarServicio(std::string nombre) {
    nodoServicio* actual = inicio;
    while (actual != nullptr) {
        if (actual->nombreS == nombre) {
            return actual;
        }
        actual = actual->next;
    }
    return nullptr;
}

nodoServicio* servicios::buscarServicioPorIndice(int indice) {
    nodoServicio* actual = inicio;
    int cont = 1;
    while (actual != nullptr) {
        if (cont == indice) {
            return actual;
        }
        actual = actual->next;
        cont++;
    }
    return nullptr;
}

bool servicios::buscarPacienteEnServicios(std::string& criterio, paciente*& pacienteEncontrado, std::string& ruta, std::string& nombreServicio) {
    nodoServicio* actual = inicio;
    while (actual != nullptr) {
        paciente* p = actual->pacientesEnServicio.buscarPorId(criterio, ruta);
        if (p == nullptr) {
            p = actual->pacientesEnServicio.buscarPorNombre(criterio, ruta);
        }
        if (p != nullptr) {
            pacienteEncontrado = p;
            nombreServicio = actual->nombreS;
            return true;
        }
        actual = actual->next;
    }
    return false;
}

bool servicios::buscarPacientePorId(std::string& id) {
    std::string dummyRuta = "";
    nodoServicio* actual = inicio;
    while (actual != nullptr) {
        if (actual->pacientesEnServicio.buscarPorId(id, dummyRuta) != nullptr) {
            return true;
        }
        actual = actual->next;
    }
    return false;
}

void servicios::mostrarTodosLosServicios() {
    nodoServicio* actual = inicio;
    while (actual != nullptr) {
        std::cout << actual->nombreS << std::endl;
        if (actual->pacientesEnServicio.estaVacio()) {
            std::cout << "Sin pacientes" << std::endl;
        } else {
            std::cout << "Pacientes:" << std::endl;
            actual->pacientesEnServicio.mostrarInorden();
        }
        actual = actual->next;
    }
}
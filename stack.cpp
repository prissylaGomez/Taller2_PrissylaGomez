#include "stack.h"
#include <iostream>

Stack::Stack() : tope(nullptr) {}

Stack::~Stack() {
    while (!estaVacia()) {
        nodoStack* temp = tope;
        tope = tope->next;
        delete temp;
    }
}

void Stack::agregar(std::string nombre, int edad, std::string servicio) {
    registroAtencion reg {nombre, edad, servicio};
    tope = new nodoStack(reg, tope);
}

bool Stack::estaVacia() {
    return tope == nullptr;
}

void Stack::mostrarHistorial() {
    if (estaVacia()) {
        std::cout << "Historial de atencion vacio." << std::endl;
        return;
    }
    nodoStack* actual = tope;
    std::cout << "Historial de atencion" << std::endl;
    std::cout << "Nombre | Edad | Servicio" << std::endl;
    while (actual != nullptr) {
        std::cout << actual->atencion.nombre << " | " << actual->atencion.edad << " | " << actual->atencion.servicio << std::endl;
        actual = actual->next;
    }
}
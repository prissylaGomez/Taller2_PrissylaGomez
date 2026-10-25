#ifndef STACK_H
#define STACK_H
    
#include <string>

struct registroAtencion {
    std::string nombre;
    int edad;
    std::string servicio;
};

struct nodoStack {
    registroAtencion atencion;
    nodoStack* next;

    nodoStack(registroAtencion reg, nodoStack* sig = nullptr)
        : atencion(reg), next(sig) {}
};

class Stack {
private:
    nodoStack* tope;

public:
    Stack();
    ~Stack();

    void agregar(std::string nombre, int edad, std::string servicio);
    bool estaVacia();
    void mostrarHistorial();
};

#endif
#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include "nodoAVL.h"
#include <string>

class arbolAVL {
private:
    nodoAVL* raiz;
    int cantidad;

    int obtenerAltura(nodoAVL* n);
    int obtenerBalance(nodoAVL* n);
    int max(int a, int b);

    nodoAVL* rotacionDerecha(nodoAVL* y);
    nodoAVL* rotacionIzquierda(nodoAVL* x);

    nodoAVL* insertar(nodoAVL* nodo, paciente* p);
    nodoAVL* nodoValorMinimo(nodoAVL* nodo);
    nodoAVL* eliminar(nodoAVL* nodo, const std::string& id);


public:
    arbolAVL();
    ~arbolAVL();

    void insertar(paciente* p);
    void eliminar(std::string& id);
   
    int getAltura();
    int getFactorBalanceRaiz();
    int getCantidad();
    bool estaVacio();
};

#endif
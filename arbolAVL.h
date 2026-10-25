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
    
    void inorden(nodoAVL* nodo);
    void preorden(nodoAVL* nodo);
    void postorden(nodoAVL* nodo);

    paciente* buscarPorIdRec(nodoAVL* nodo, std::string& id, std::string& ruta);
    paciente* buscarPorNombreRec(nodoAVL* nodo, std::string& nombre, std::string& ruta);

    void destruirRecursivo(nodoAVL* nodo);

public:
    arbolAVL();
    ~arbolAVL();

    void insertar(paciente* p);
    void eliminar(std::string& id);
    paciente* buscarPorId(std::string& id, std::string& ruta);
    paciente* buscarPorNombre(std::string& nombre, std::string& ruta);
    void mostrarInorden();
    void mostrarPreorden();
    void mostrarPostorden();

    int getAltura();
    int getFactorBalanceRaiz();
    int getCantidad();
    bool estaVacio();
};

#endif
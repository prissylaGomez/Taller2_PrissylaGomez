#include "arbolAVL.h"
#include <iostream>

arbolAVL::arbolAVL() : raiz(nullptr), cantidad(0) {}

arbolAVL::~arbolAVL() {
    destruirRecursivo(raiz);
}

void arbolAVL::destruirRecursivo(nodoAVL* nodo) {
    if (nodo != nullptr) {
        destruirRecursivo(nodo->izquierdo);
        destruirRecursivo(nodo->derecho);
        delete nodo->dato;
        delete nodo;
    }
}
int arbolAVL::obtenerAltura(nodoAVL* n){
    return (n == nullptr) ? 0 : n->altura;
}
int arbolAVL::max(int a, int b){
    return (a > b) ? a : b;
}
int arbolAVL::obtenerBalance(nodoAVL* n){
    return (n == nullptr) ? 0 : obtenerAltura(n->izquierdo) - obtenerAltura(n->derecho);
}
nodoAVL* arbolAVL::rotacionDerecha(nodoAVL* y) {
    nodoAVL* x = y->izquierdo;
    nodoAVL* T2 = x->derecho;

    x->derecho = y;
    y->izquierdo = T2;

    y->altura = max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;
    x->altura = max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;

    return x;
}
nodoAVL* arbolAVL::rotacionIzquierda(nodoAVL* x) {
    nodoAVL* y = x->derecho;
    nodoAVL* T2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T2;

    y->altura = max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;
    x->altura = max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;

    return y;
}
nodoAVL* arbolAVL::insertar(nodoAVL* nodo, paciente* p) {
    if (nodo == nullptr) {
        cantidad++;
        return new nodoAVL(p);
    }

    if (p->getId() < nodo->dato->getId()) {
        nodo->izquierdo = insertar(nodo->izquierdo, p);
    } else if (p->getId() > nodo->dato->getId()) {
        nodo->derecho = insertar(nodo->derecho, p);
    } else {
        return nodo;
    }

    nodo->altura = 1 + max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));
    int balance = obtenerBalance(nodo);

    if (balance > 1 && p->getId() < nodo->izquierdo->dato->getId()) {
        return rotacionDerecha(nodo);
    }
    if (balance < -1 && p->getId() > nodo->derecho->dato->getId()) {
        return rotacionIzquierda(nodo);
    }
    if (balance > 1 && p->getId() > nodo->izquierdo->dato->getId()) {
        nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
        return rotacionDerecha(nodo);
    }
    if (balance < -1 && p->getId() < nodo->derecho->dato->getId()) {
        nodo->derecho = rotacionDerecha(nodo->derecho);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}
void arbolAVL::insertar(paciente* p) {
    raiz = insertar(raiz, p);
}
nodoAVL* arbolAVL::nodoValorMinimo(nodoAVL* nodo) {
    nodoAVL* actual = nodo;
    while (actual->izquierdo != nullptr) {
        actual = actual->izquierdo;
    }
    return actual;
}

nodoAVL* arbolAVL::eliminar(nodoAVL* nodo, const std::string& id) {
    if (nodo == nullptr) return nodo;

    if (id < nodo->dato->getId()) {
        nodo->izquierdo = eliminar(nodo->izquierdo, id);
    } else if (id > nodo->dato->getId()) {
        nodo->derecho = eliminar(nodo->derecho, id);
    } else {
        if ((nodo->izquierdo == nullptr) || (nodo->derecho == nullptr)) {
            nodoAVL* temp = nodo->izquierdo ? nodo->izquierdo : nodo->derecho;
            if (temp == nullptr) {
                temp = nodo;
                nodo = nullptr;
            } else {
                *nodo = *temp;
            }
            delete temp->dato;
            delete temp;
            cantidad--;
        } else {
            nodoAVL* temp = nodoValorMinimo(nodo->derecho);
            nodo->dato = temp->dato;
            nodo->derecho = eliminar(nodo->derecho, temp->dato->getId());
        }
    }
    if (nodo == nullptr) return nodo;

    nodo->altura = 1 + max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));
    int balance = obtenerBalance(nodo);

    if (balance > 1 && obtenerBalance(nodo->izquierdo) >= 0) {
        return rotacionDerecha(nodo);
    }
    if (balance > 1 && obtenerBalance(nodo->izquierdo) < 0) {
        nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
        return rotacionDerecha(nodo);
    }
    if (balance < -1 && obtenerBalance(nodo->derecho) <= 0) {
        return rotacionIzquierda(nodo);
    }
    if (balance < -1 && obtenerBalance(nodo->derecho) > 0) {
        nodo->derecho = rotacionDerecha(nodo->derecho);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

void arbolAVL::eliminar(std::string& id) {
    raiz = eliminar(raiz, id);
}
paciente* arbolAVL::buscarPorIdRec(nodoAVL* nodo, std::string& id, std::string& ruta){
    if (nodo == nullptr) return nullptr;

    if (ruta.empty()) {
        ruta = nodo->dato->getId();
    } else {
        ruta += " -> " + nodo->dato->getId();
    }

    if (nodo->dato->getId() == id) {
        return nodo->dato;
    }
    if (id < nodo->dato->getId()) {
        return buscarPorIdRec(nodo->izquierdo, id, ruta);
    }
    return buscarPorIdRec(nodo->derecho, id, ruta);
}

paciente* arbolAVL::buscarPorId(std::string& id, std::string& ruta){
    ruta = "";
    return buscarPorIdRec(raiz, id, ruta);
}

paciente* arbolAVL::buscarPorNombreRec(nodoAVL* nodo, std::string& nombre, std::string& ruta){
    if (nodo == nullptr) return nullptr;

    if (ruta.empty()) {
        ruta = nodo->dato->getId();
    } else {
        ruta += " -> " + nodo->dato->getId();
    }

    if (nodo->dato->getNombre() == nombre) {
        return nodo->dato;
    }

    paciente* encontrado = buscarPorNombreRec(nodo->izquierdo, nombre, ruta);
    if (encontrado != nullptr) return encontrado;

    return buscarPorNombreRec(nodo->derecho, nombre, ruta);
}

paciente* arbolAVL::buscarPorNombre(std::string& nombre, std::string& ruta){
    ruta = "";
    return buscarPorNombreRec(raiz, nombre, ruta);
}

void arbolAVL::inorden(nodoAVL* nodo){
    if (nodo != nullptr) {
        inorden(nodo->izquierdo);
        std::cout << "- " << nodo->dato->getNombre() << " (" << nodo->dato->getId() << ")" << std::endl;
        inorden(nodo->derecho);
    }
}

void arbolAVL::preorden(nodoAVL* nodo){
    if (nodo != nullptr) {
        std::cout << "- " << nodo->dato->getNombre() << " (" << nodo->dato->getId() << ")" << std::endl;
        preorden(nodo->izquierdo);
        preorden(nodo->derecho);
    }
}

void arbolAVL::postorden(nodoAVL* nodo){
    if (nodo != nullptr) {
        postorden(nodo->izquierdo);
        postorden(nodo->derecho);
        std::cout << "- " << nodo->dato->getNombre() << " (" << nodo->dato->getId() << ")" << std::endl;
    }
}

void arbolAVL::mostrarInorden() { inorden(raiz); }
void arbolAVL::mostrarPreorden() { preorden(raiz); }
void arbolAVL::mostrarPostorden() { postorden(raiz); }
int arbolAVL::getAltura() { return obtenerAltura(raiz); }
int arbolAVL::getFactorBalanceRaiz() { return obtenerBalance(raiz); }
int arbolAVL::getCantidad() { return cantidad; }
bool arbolAVL::estaVacio() { return raiz == nullptr; }
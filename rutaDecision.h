#ifndef RUTADECISION_H
#define RUTADECISION_H

#include "paciente.h"
#include <string>

enum class TipoPregunta {
    HOJA,
    ES_PEDIATRIA,
    TIENE_TRAUMA,
    REQUIERE_CIRUGIA,
    SINTOMAS_NEUROLOGICOS,
    DOLOR_PECHO,
    URGENCIAS_CRITICO,
    REQUIERE_HOSPITALIZACION
};

struct NodoDecision {
    TipoPregunta tipo;
    std::string textoPregunta;
    std::string servicioResultado;
    NodoDecision* si;
    NodoDecision* no;

    NodoDecision(TipoPregunta tipo, std::string texto)
        : tipo(tipo), textoPregunta(texto), servicioResultado(""), si(nullptr), no(nullptr) {}

    NodoDecision(std::string servicio)
        : tipo(TipoPregunta::HOJA), textoPregunta(""), servicioResultado(servicio), si(nullptr), no(nullptr) {}
};

class rutaDecision {
private:
    NodoDecision* raiz;

    void destruirRecursivo(NodoDecision* nodo);
    void preordenRec(NodoDecision* nodo);
    void inordenRec(NodoDecision* nodo);
    void postordenRec(NodoDecision* nodo);

public:
    rutaDecision();
    ~rutaDecision();

    void construirArbol();
    std::string evaluar(paciente* p, std::string& rutaExplicativa);
    void mostrarPreorden();
    void mostrarInorden();
    void mostrarPostorden();
};

#endif
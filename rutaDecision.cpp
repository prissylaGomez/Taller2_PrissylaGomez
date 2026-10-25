#include "rutaDecision.h"
#include <iostream>

rutaDecision::rutaDecision() : raiz(nullptr) {
    construirArbol();
}

rutaDecision::~rutaDecision() {
    destruirRecursivo(raiz);
}

void rutaDecision::destruirRecursivo(NodoDecision* nodo) {
    if (nodo != nullptr) {
        destruirRecursivo(nodo->si);
        destruirRecursivo(nodo->no);
        delete nodo;
    }
}

void rutaDecision::construirArbol() {
    raiz = new NodoDecision(TipoPregunta::ES_PEDIATRIA, "Edad < 14");
    
    raiz->si = new NodoDecision("pediatria");

    NodoDecision* nTrauma = new NodoDecision(TipoPregunta::TIENE_TRAUMA, "Trauma == 1");
    raiz->no = nTrauma;

    NodoDecision* nCirugiaTrauma = new NodoDecision(TipoPregunta::REQUIERE_CIRUGIA, "RequiereCirugia == 1");
    nTrauma->si = nCirugiaTrauma;
    nCirugiaTrauma->si = new NodoDecision("cirugia");
    nCirugiaTrauma->no = new NodoDecision("traumatologia");

    NodoDecision* nNeuro = new NodoDecision(TipoPregunta::SINTOMAS_NEUROLOGICOS, "SintomasNeurologicos == 1");
    nTrauma->no = nNeuro;
    nNeuro->si = new NodoDecision("neurologia");

    NodoDecision* nCardio = new NodoDecision(TipoPregunta::DOLOR_PECHO, "TipoDolor == pecho o Presion >= 140");
    nNeuro->no = nCardio;
    nCardio->si = new NodoDecision("cardiologia");

    NodoDecision* nUrgencias = new NodoDecision(TipoPregunta::URGENCIAS_CRITICO, "Temperatura >= 39.0 o Dolor >= 8");
    nCardio->no = nUrgencias;
    nUrgencias->si = new NodoDecision("urgencias");

    NodoDecision* nHosp = new NodoDecision(TipoPregunta::REQUIERE_HOSPITALIZACION, "DiasHospitalizacion >= 2");
    nUrgencias->no = nHosp;
    nHosp->si = new NodoDecision("hospitalizacion");
    nHosp->no = new NodoDecision("medicina general");
}

std::string rutaDecision::evaluar(paciente* p, std::string& rutaExplicativa){
    if (raiz == nullptr || p == nullptr) return "medicina general";

    NodoDecision* actual = raiz;
    rutaExplicativa = "";

    while (actual != nullptr && actual->tipo != TipoPregunta::HOJA) {
        bool condicion = false;
        std::string paso = "";

        switch (actual->tipo) {
            case TipoPregunta::ES_PEDIATRIA:
                condicion = (p->getEdad() < 14);
                paso = condicion ? "Edad < 14" : "Edad >= 14";
                break;
            case TipoPregunta::TIENE_TRAUMA:
                condicion = (p->getTrauma() == 1);
                paso = condicion ? "Trauma == 1" : "Trauma == 0";
                break;
            case TipoPregunta::REQUIERE_CIRUGIA:
                condicion = (p->getRequiereCirugia() == 1);
                paso = condicion ? "RequiereCirugia == 1" : "RequiereCirugia == 0";
                break;
            case TipoPregunta::SINTOMAS_NEUROLOGICOS:
                condicion = (p->getSintomasNeurologicos() == 1);
                paso = condicion ? "Sintomas Neurologicos == 1" : "Sintomas Neurologicos == 0";
                break;
            case TipoPregunta::DOLOR_PECHO:
                condicion = (p->getTipoDolor() == "pecho" || p->getPresionArterial() >= 140);
                paso = condicion ? "TipoDolor == pecho" : "TipoDolor != pecho";
                break;
            case TipoPregunta::URGENCIAS_CRITICO:
                condicion = (p->getTemperatura() >= 39.0 || p->getDolor() >= 8);
                paso = condicion ? "Temperatura >= 39.0 o Dolor >= 8" : "Temperatura < 39.0 y Dolor < 8";
                break;
            case TipoPregunta::REQUIERE_HOSPITALIZACION:
                condicion = (p->getDiasHospitalizacion() >= 2);
                paso = condicion ? "DiasHospitalizacion >= 2" : "DiasHospitalizacion < 2";
                break;
            default:
                break;
        }

        if (rutaExplicativa.empty()) {
            rutaExplicativa = paso;
        } else {
            rutaExplicativa += " -> " + paso;
        }

        actual = condicion ? actual->si : actual->no;
    }

    if (actual != nullptr) {
        return actual->servicioResultado;
    }
    return "medicina general";
}

void rutaDecision::preordenRec(NodoDecision* nodo){
    if (nodo == nullptr) return;
    if (nodo->tipo == TipoPregunta::HOJA) {
        std::cout << "[Hoja: " << nodo->servicioResultado << "] ";
    } else {
        std::cout << "[" << nodo->textoPregunta << "] ";
    }
    preordenRec(nodo->si);
    preordenRec(nodo->no);
}

void rutaDecision::inordenRec(NodoDecision* nodo){
    if (nodo == nullptr) return;
    inordenRec(nodo->si);
    if (nodo->tipo == TipoPregunta::HOJA) {
        std::cout << "[Hoja: " << nodo->servicioResultado << "] ";
    } else {
        std::cout << "[" << nodo->textoPregunta << "] ";
    }
    inordenRec(nodo->no);
}

void rutaDecision::postordenRec(NodoDecision* nodo){
    if (nodo == nullptr) return;
    postordenRec(nodo->si);
    postordenRec(nodo->no);
    if (nodo->tipo == TipoPregunta::HOJA) {
        std::cout << "[Hoja: " << nodo->servicioResultado << "] ";
    } else {
        std::cout << "[" << nodo->textoPregunta << "] ";
    }
}

void rutaDecision::mostrarPreorden(){
    preordenRec(raiz);
    std::cout << std::endl;
}

void rutaDecision::mostrarInorden(){
    inordenRec(raiz);
    std::cout << std::endl;
}

void rutaDecision::mostrarPostorden(){
    postordenRec(raiz);
    std::cout << std::endl;
}
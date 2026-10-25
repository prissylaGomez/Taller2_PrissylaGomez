#ifndef SERVICIOS_H
#define SERVICIOS_H

#include "nodoServicio.h"
#include <string>

class servicios {
private:
    nodoServicio* inicio;

public:
    servicios();
    ~servicios();

    void agregarServicio(std::string nombre);
    nodoServicio* buscarServicio(std::string nombre);
    nodoServicio* buscarServicioPorIndice(int indice);
    bool buscarPacienteEnServicios(std::string& criterio, paciente*& pacienteEncontrado, std::string& ruta, std::string& nombreServicio);
    bool buscarPacientePorId(std::string& id);
    void mostrarTodosLosServicios();
};

#endif
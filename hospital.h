#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "cola.h"
#include "servicios.h"
#include "stack.h"
#include "rutaDecision.h"
#include <string>

class hospital {
private:
    cola colaAtencion;
    servicios listaServicios;
    Stack historialAtenciones;
    rutaDecision clasificador;
    std::string normalizar(std::string& str);

public:
    hospital();
    ~hospital();

    bool agregarPacientes(std::string rutaArchivo);
    void mostrarPacientesPorAtender();
    void atenderPacientes(int cant);
    void infoServicios(int eleccion);
    void mostrarEstadoGeneralDepartamentos();
    void buscarPaciente(std::string& criterio);
    void mostrarHistorialAtenciones();
    void mostrarInordenServicio(int eleccion);
    void mostrarPreordenServicio(int eleccion);
    void mostrarPostordenServicio(int eleccion);
    void mostrarMetricasServicio(int eleccion);
};

#endif
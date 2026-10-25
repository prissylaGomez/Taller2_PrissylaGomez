#include "hospital.h"
#include <iostream>
#include <fstream>
#include <sstream>

hospital::hospital() {
    int totalS = 8;
    std::string* serviciosArr = new std::string[totalS];

    *(serviciosArr + 0) = "urgencias";
    *(serviciosArr + 1) = "medicina general";
    *(serviciosArr + 2) = "cardiologia";
    *(serviciosArr + 3) = "neurologia";
    *(serviciosArr + 4) = "traumatologia";
    *(serviciosArr + 5) = "cirugia";
    *(serviciosArr + 6) = "pediatria";
    *(serviciosArr + 7) = "hospitalizacion";

    std::string* ptr = serviciosArr;
    for (int i = 0; i < totalS; ++i) {
        listaServicios.agregarServicio(*ptr);
        ++ptr;
    }
    delete[] serviciosArr;
}

hospital::~hospital() {}

std::string hospital::normalizar(std::string& str) {
    std::string res = "";
    for (size_t i = 0; i < str.size(); ++i) {
        unsigned char c = str[i];
        if (c == 0xC3 && i + 1 < str.size()) {
            unsigned char next = str[i + 1];
            if (next == 0xAD || next == 0x8D) { res += 'i'; i++; continue; }
            if (next == 0xA1 || next == 0x81) { res += 'a'; i++; continue; }
            if (next == 0xA9 || next == 0x89) { res += 'e'; i++; continue; }
            if (next == 0xB3 || next == 0x93) { res += 'o'; i++; continue; }
            if (next == 0xBA || next == 0x9A) { res += 'u'; i++; continue; }
        }
        res += std::tolower(c);
    }
    return res;
}

bool hospital::agregarPacientes(std::string rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << rutaArchivo << std::endl;
        return false;
    }

    std::string linea;
    int nlinea = 0;
    while (std::getline(archivo, linea)) {
        nlinea++;
        if (linea.empty() || linea.find(';') == std::string::npos) continue;

        std::stringstream ss(linea);
        std::string id, nombre, edadT, tempT, presT, dolorT, tipoDolor, traumaT, snT, rcT, hospT;

        if (!std::getline(ss, id, ';') ||
            !std::getline(ss, nombre, ';') ||
            !std::getline(ss, edadT, ';') ||
            !std::getline(ss, tempT, ';') ||
            !std::getline(ss, presT, ';') ||
            !std::getline(ss, dolorT, ';') ||
            !std::getline(ss, tipoDolor, ';') ||
            !std::getline(ss, traumaT, ';') ||
            !std::getline(ss, snT, ';') ||
            !std::getline(ss, rcT, ';') ||
            !std::getline(ss, hospT)) {
            std::cerr << "Advertencia: En linea " << nlinea << " formato invalido, omitiendo...\n";
            continue;
        }

        if (id.empty() || nombre.empty()) {
            std::cerr << "Advertencia: En linea " << nlinea << " hay campos vacios obligatorios, omitiendo...\n";
            continue;
        }

        if (colaAtencion.buscarPaciente(id) || listaServicios.buscarPacientePorId(id)) {
            std::cerr << "Advertencia: En linea " << nlinea << " el paciente con ID '" << id << "' ya existe, omitiendo...\n";
            continue;
        }

        try {
            int edad = std::stoi(edadT);
            double temp = std::stod(tempT);
            int pres = std::stoi(presT);
            int dolor = std::stoi(dolorT);
            std::string tDolorNorm = normalizar(tipoDolor);
            int trauma = std::stoi(traumaT);
            int sn = std::stoi(snT);
            int rc = std::stoi(rcT);
            int hosp = std::stoi(hospT);

            paciente* nuevo = new paciente(id, nombre, edad, temp, pres, dolor, tDolorNorm, trauma, sn, rc, hosp);
            colaAtencion.encolar(nuevo);
        } catch (...) {
            std::cerr << "Advertencia: En linea " << nlinea << " error al procesar valores numericos, omitiendo...\n";
            continue;
        }
    }

    archivo.close();
    return true;
}

void hospital::mostrarPacientesPorAtender() {
    colaAtencion.mostrarCola();
}
void hospital::atenderPacientes(int cant) {
    if (colaAtencion.estaVacia()) {
        std::cout << "No hay pacientes en la cola de atencion." << std::endl;
        return;
    }

    int listos = 0;
    while (listos < cant && !colaAtencion.estaVacia()) {
        paciente* p = colaAtencion.desencolar();

        std::cout << "ID: " << p->getId() << std::endl;
        std::cout << "Nombre: " << p->getNombre() << std::endl;
        std::cout << "Edad: " << p->getEdad() << std::endl;
        std::cout << "Temperatura: " << p->getTemperatura() << std::endl;
        std::cout << "Dolor: " << p->getDolor() << std::endl;
        std::cout << "TipoDolor: " << p->getTipoDolor() << std::endl;
        std::cout << "Trauma: " << p->getTrauma() << std::endl;
        std::cout << "Sintomas Neurologicos: " << p->getSintomasNeurologicos() << std::endl;
        std::cout << "Requiere Cirugia: " << p->getRequiereCirugia() << std::endl;
        std::cout << "DiasHospitalizacion: " << p->getDiasHospitalizacion() << std::endl;

        std::string rutaDec = "";
        std::string servicioAsignado = clasificador.evaluar(p, rutaDec);
        p->setServicio(servicioAsignado);

        std::cout << "Ruta: " << rutaDec << std::endl;
        std::cout << "Servicio asignado: " << servicioAsignado << std::endl;

        nodoServicio* servicioEncontrado = listaServicios.buscarServicio(servicioAsignado);
        if (servicioEncontrado != nullptr) {
            servicioEncontrado->pacientesEnServicio.insertar(p);
            std::cout << "Paciente insertado en el AVL de " << servicioEncontrado->nombreS << "." << std::endl;
            historialAtenciones.agregar(p->getNombre(), p->getEdad(), servicioEncontrado->nombreS);
        } else {
            std::cout << "Servicio no encontrado." << std::endl;
            delete p;
        }

        std::cout << "---------------------------------------------" << std::endl;
        ++listos;
    }
}

void hospital::mostrarEstadoGeneralDepartamentos() {
    std::cout << "=== ESTADO DE LOS DEPARTAMENTOS ===" << std::endl;
    listaServicios.mostrarTodosLosServicios();
}

void hospital::infoServicios(int eleccion) {
    nodoServicio* servicio = listaServicios.buscarServicioPorIndice(eleccion);
    if (servicio != nullptr) {
        std::cout << "Departamento de " << servicio->nombreS << std::endl;
        std::cout << "Cantidad de pacientes atendidos: " << servicio->pacientesEnServicio.getCantidad() << std::endl;
        std::cout << "Altura del AVL: " << servicio->pacientesEnServicio.getAltura() << std::endl;
        std::cout << "Factor de balance de la raiz: " << servicio->pacientesEnServicio.getFactorBalanceRaiz() << std::endl;
        servicio->pacientesEnServicio.mostrarInorden();
    } else {
        std::cout << "Servicio no encontrado." << std::endl;
    }
}

void hospital::buscarPaciente(std::string& criterio) {
    std::cout << "Buscando en AVL..." << std::endl;
    paciente* encontrado = nullptr;
    std::string ruta = "";
    std::string nombreServicio = "";

    if (listaServicios.buscarPacienteEnServicios(criterio, encontrado, ruta, nombreServicio)) {
        std::cout << "Paciente encontrado:" << std::endl;
        std::cout << "ID: " << encontrado->getId() << std::endl;
        std::cout << "Nombre: " << encontrado->getNombre() << std::endl;
        std::cout << "Edad: " << encontrado->getEdad() << std::endl;
        std::cout << "Departamento: " << nombreServicio << std::endl;
        std::cout << "T: " << encontrado->getTemperatura()
                  << " | D: " << encontrado->getDolor()
                  << " | TD: " << encontrado->getTipoDolor()
                  << " | T: " << (encontrado->getTrauma() ? "Si" : "No")
                  << " | SN: " << (encontrado->getSintomasNeurologicos() ? "Si" : "No")
                  << " | RC: " << (encontrado->getRequiereCirugia() ? "Si" : "No")
                  << " | DH: " << encontrado->getDiasHospitalizacion() << std::endl;
        std::cout << "Ruta de busqueda:" << std::endl;
        std::cout << ruta << std::endl;
    } else {
        std::cout << "Paciente no encontrado." << std::endl;
    }
}
void hospital::mostrarInordenServicio(int eleccion) {
    nodoServicio* servicio = listaServicios.buscarServicioPorIndice(eleccion);
    if (servicio != nullptr) {
        std::cout << "\n--- Recorrido Inorden: " << servicio->nombreS << " ---" << std::endl;
        if (servicio->pacientesEnServicio.estaVacio()) {
            std::cout << "El arbol no tiene pacientes." << std::endl;
        } else {
            servicio->pacientesEnServicio.mostrarInorden();
        }
    } else {
        std::cout << "Servicio no encontrado." << std::endl;
    }
}

void hospital::mostrarPreordenServicio(int eleccion) {
    nodoServicio* servicio = listaServicios.buscarServicioPorIndice(eleccion);
    if (servicio != nullptr) {
        std::cout << "\n--- Recorrido Preorden: " << servicio->nombreS << " ---" << std::endl;
        if (servicio->pacientesEnServicio.estaVacio()) {
            std::cout << "El arbol no tiene pacientes." << std::endl;
        } else {
            servicio->pacientesEnServicio.mostrarPreorden();
        }
    } else {
        std::cout << "Servicio no encontrado." << std::endl;
    }
}

void hospital::mostrarPostordenServicio(int eleccion) {
    nodoServicio* servicio = listaServicios.buscarServicioPorIndice(eleccion);
    if (servicio != nullptr) {
        std::cout << "\n--- Recorrido Postorden: " << servicio->nombreS << " ---" << std::endl;
        if (servicio->pacientesEnServicio.estaVacio()) {
            std::cout << "El arbol no tiene pacientes." << std::endl;
        } else {
            servicio->pacientesEnServicio.mostrarPostorden();
        }
    } else {
        std::cout << "Servicio no encontrado." << std::endl;
    }
}

void hospital::mostrarMetricasServicio(int eleccion) {
    nodoServicio* servicio = listaServicios.buscarServicioPorIndice(eleccion);
    if (servicio != nullptr) {
        std::cout << "\n--- Metricas AVL: " << servicio->nombreS << " ---" << std::endl;
        std::cout << "Cantidad de pacientes: " << servicio->pacientesEnServicio.getCantidad() << std::endl;
        std::cout << "Altura del arbol: " << servicio->pacientesEnServicio.getAltura() << std::endl;
        std::cout << "Factor de balance de la raiz: " << servicio->pacientesEnServicio.getFactorBalanceRaiz() << std::endl;
    } else {
        std::cout << "Servicio no encontrado." << std::endl;
    }
}
void hospital::mostrarHistorialAtenciones() {
    historialAtenciones.mostrarHistorial();
}
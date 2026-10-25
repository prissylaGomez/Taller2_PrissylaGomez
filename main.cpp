#include <iostream>
#include <string>
#include "hospital.h"

void mostrarMenuDepartamentos() {
    std::cout << "1. Urgencias" << std::endl;
    std::cout << "2. Medicina General" << std::endl;
    std::cout << "3. Cardiologia" << std::endl;
    std::cout << "4. Neurologia" << std::endl;
    std::cout << "5. Traumatologia" << std::endl;
    std::cout << "6. Cirugia" << std::endl;
    std::cout << "7. Pediatria" << std::endl;
    std::cout << "8. Hospitalizacion" << std::endl;
}
int main() {

    int opcion = 0;
    int dep = 0;
    hospital hospitalM;
    hospitalM.agregarPacientes("pacientes.txt");
    
    do{
        std::cout << "----Bienvenido al menu del Hospital----" << std::endl;
        std::cout << "1. Atender pacientes" << std::endl;
        std::cout << "2. Ver departamentos" << std::endl;
        std::cout << "3. Buscar paciente" << std::endl;
        std::cout << "4. Mostrar recorridos de un servicio" << std::endl;
        std::cout << "5. Mostrar altura y factor de balance de un servicio" << std::endl;
        std::cout << "6. Mostrar historial de atencion" << std::endl;
        std::cout << "7. Salir" << std::endl;
        std::cout << "Ingrese una opcion: ";

        while(!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Opcion  invalida, intente de nuevo." << std::endl;
        }
        switch (opcion){
            case 1:{
                int pacientes = 0;
                hospitalM.mostrarPacientesPorAtender();
                std::cout << std::endl;
                std::cout << "¿Cuantos pacientes desea atender?: ";
                std::cin >> pacientes;
                if (!std::cin >> pacientes) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Opcion invalida, intente de nuevo." << std::  endl;
                    break;
                }
                std::cout << std::endl;
                std::cout << "Pacientes en atencion" << std::endl;
                hospitalM.atenderPacientes(pacientes);
                break;
            }
            case 2:{
                hospitalM.mostrarEstadoGeneralDepartamentos();
                break;
            }
            case 3:{
                std::string criterio;
                std::cout << "Ingrese el ID o Nombre del paciente: ";
                std::cin.ignore();
                std::getline(std::cin, criterio);
                hospitalM.buscarPaciente(criterio);
                break;
            }
            case 4:{
                int eleccion = 0;
                while (eleccion != 4) {
                    std::cout << "¿Que recorrido desea ver?" << std::endl;
                    std::cout << "1. inOrden" << std::endl;
                    std::cout << "2. preOrden" << std::endl;
                    std::cout << "3. postOrden" << std::endl;
                    std::cout << "4. Volver al menu" << std::endl;
                    std::cout << "Ingrese una opcion: ";
                    std::cin >> eleccion;
                    switch (eleccion) {
                        case 1:
                            dep = 0;
                            mostrarMenuDepartamentos();
                            std::cout << "Seleccione el departamento: ";
                            if (std::cin >> dep && dep >= 1 && dep <= 8) {
                                hospitalM.mostrarInordenServicio(dep);
                            } else {
                                std::cin.clear();
                                std::cin.ignore(10000, '\n');
                                std::cout << "Departamento invalido." << std::endl;
                            }
                            break;
                        case 2:
                            dep = 0;
                            mostrarMenuDepartamentos();
                            std::cout << "Seleccione el departamento: ";
                            if (std::cin >> dep && dep >= 1 && dep <= 8) {
                                hospitalM.mostrarPreordenServicio(dep);
                            } else {
                                std::cin.clear();
                                std::cin.ignore(10000, '\n');
                                std::cout << "Departamento invalido." << std::endl;
                            }
                            break;
                        case 3:
                            dep = 0;
                            mostrarMenuDepartamentos();
                            std::cout << "Seleccione el departamento: ";
                            if (std::cin >> dep && dep >= 1 && dep <= 8) {
                                hospitalM.mostrarPostordenServicio(dep);
                            } else {
                                std::cin.clear();
                                std::cin.ignore(10000, '\n');
                                std::cout << "Departamento invalido." << std::endl;
                            }
                            break;
                        case 4:
                            std::cout << "Volviendo al menu principal..." << std::endl;
                            break;
                        default:
                            std::cout << "Opcion invalida, intente de nuevo." << std::endl;
                            break;
                    }
                }
                break;
            }
            case 5:{
                dep = 0;
                mostrarMenuDepartamentos();
                std::cout << "Seleccione el departamento: ";
                if (std::cin >> dep && dep >= 1 && dep <= 8) {
                    hospitalM.mostrarMetricasServicio(dep);
                } else {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Departamento invalido." << std::endl;
                }
                break;
            }
            case 6:{
                hospitalM.mostrarHistorialAtenciones();
                break;
            }
            case 7:{
                std::cout << "Saliendo del hospital" << std::endl;
                break;
            }
            default:{
                std::cout << "Opcion invalida, intente de nuevo." << std::endl;
                break;
            }
        }
    }while (opcion != 7);
    return 0;
}
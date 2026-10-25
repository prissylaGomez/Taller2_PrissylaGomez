#include <iostream>

int main() {

    int opcion = 0;
    
    do{
        std::cout << "----Bienvenido al menu del Hospital----" << std::endl;
        std::cout << "1. Atender pacientes" << std::endl;
        std::cout << "2. Ver departamento" << std::endl;
        std::cout << "3. Buscar paciente" << std::endl;
        std::cout << "4. Salir" << std::endl;
        std::cout << "Ingrese una opcion: ";

        while(!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Opcion  invalida, intente de nuevo." << std::endl;
        }
        switch (opcion){
            case 1:{
                int pacientes = 0;
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
                break;
            }
            case 2:{
                int departamento;
                std::cout << "Departamentos y servicios" << std::endl;
                std::cout << "1. Urgencias" << std::endl;
                std::cout << "2. Medicina General" << std::endl;
                std::cout << "3. Cardiología" << std::endl;
                std::cout << "4. Neurología" << std::endl;
                std::cout << "5. Traumatología" << std::endl;
                std::cout << "6. Cirugía" << std::endl;
                std::cout << "7. Pediatría" << std::endl;
                std::cout << "8. Hospitalización" << std::endl;
                std::cout << "¿Que departamento desea ver?: ";
                std::cin >> departamento;
                if (!std::cin >> departamento) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Opcion invalida, intente de nuevo." << std::endl;
                    break;
                }
                std::cout << std::endl;
                break;
            }
            case 3:{
                std::cout << "Buscando paciente..." << std::endl;
                break;
            }
            case 4:{
                std::cout << "Saliendo del hospital" << std::endl;
                break;
            }
            default:{
                std::cout << "Opcion invalida, intente de nuevo." << std::endl;
                break;
            }
        }
    }while (opcion != 4);
    return 0;
}
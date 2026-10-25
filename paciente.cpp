#include "paciente.h"

paciente::paciente(std::string id, std::string nombre, int edad, double temperatura,
                   int presionArterial, int dolor, std::string tipoDolor,
                   int trauma, int sintomasNeurologicos, int requiereCirugia,
                   int diasHospitalizacion)
    : id(id), nombre(nombre), edad(edad), temperatura(temperatura),
      presionArterial(presionArterial), dolor(dolor), tipoDolor(tipoDolor),
      trauma(trauma), sintomasNeurologicos(sintomasNeurologicos),
      requiereCirugia(requiereCirugia), diasHospitalizacion(diasHospitalizacion),
      servicio("") {}

paciente::~paciente() {}

std::string paciente::getId() const { return id; }
std::string paciente::getNombre() const { return nombre; }
int paciente::getEdad() const { return edad; }
double paciente::getTemperatura() const { return temperatura; }
int paciente::getPresionArterial() const { return presionArterial; }
int paciente::getDolor() const { return dolor; }
std::string paciente::getTipoDolor() const { return tipoDolor; }
int paciente::getTrauma() const { return trauma; }
int paciente::getSintomasNeurologicos() const { return sintomasNeurologicos; }
int paciente::getRequiereCirugia() const { return requiereCirugia; }
int paciente::getDiasHospitalizacion() const { return diasHospitalizacion; }
std::string paciente::getServicio() const { return servicio; }

void paciente::setServicio(const std::string& serv) {
    servicio = serv;
}
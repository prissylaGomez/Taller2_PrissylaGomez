#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>

class paciente {
private:
    std::string id;
    std::string nombre;
    int edad;
    double temperatura;
    int presionArterial;
    int dolor;
    std::string tipoDolor;
    int trauma;
    int sintomasNeurologicos;
    int requiereCirugia;
    int diasHospitalizacion;
    std::string servicio;

public:
    paciente(std::string id, std::string nombre, int edad, double temperatura,
             int presionArterial, int dolor, std::string tipoDolor,
             int trauma, int sintomasNeurologicos, int requiereCirugia,
             int diasHospitalizacion);
    ~paciente();

    std::string getId() const;
    std::string getNombre() const;
    int getEdad() const;
    double getTemperatura() const;
    int getPresionArterial() const;
    int getDolor() const;
    std::string getTipoDolor() const;
    int getTrauma() const;
    int getSintomasNeurologicos() const;
    int getRequiereCirugia() const;
    int getDiasHospitalizacion() const;
    std::string getServicio() const;

    void setServicio(const std::string& serv);
};

#endif
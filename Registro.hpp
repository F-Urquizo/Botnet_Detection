#ifndef Registro_hpp
#define Registro_hpp

#include <iostream>
#include <vector>

class Registro {
private:
    std::string fecha;
    std::string hora;
    std::string ip_origen;
    std::string puerto_origen;
    std::string nombre_origen;
    std::string ip_destino;
    std::string puerto_destino;
    std::string nombre_destino;    
public:
    Registro() {}

    void set_data(std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string);

    std::string getFecha() const;
    std::string getNombreOrigen() const;
    std::string getNombreOrigen2() const;
    std::string getNombreDestino() const;
    std::string getNombreDestino2() const;
    std::string IPredInterna(const std::vector<Registro>& registros) const;
    std::string getIPorigen2() const;
    std::string getIPdestino() const;
    std::string getPuertoDestino() const;

    
    static bool compara_fecha_asc(Registro, Registro);
    static bool compara_fecha_eq(Registro, Registro);
    
    friend std::ostream & operator<<(std::ostream & os, const Registro & registo);

    std::vector<int> ParseDate(const std::string& date) const;
    bool operator<=(const Registro& other) const;
    bool operator!=(const Registro& other) const;
    bool operator==(const Registro& other) const;

};


#endif /* Registro_hpp */
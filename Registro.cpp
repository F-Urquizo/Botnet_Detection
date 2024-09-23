#include "Registro.hpp"
#include <fstream>
#include <sstream>
#include <vector>

void Registro::set_data(std::string f, std::string h, std::string ipo,
                        std::string po, std::string no, std::string ipd,
                        std::string pd, std::string nd) {
  fecha = f;
  hora = h;
  ip_origen = ipo;
  puerto_origen = po;
  nombre_origen = no;
  ip_destino = ipd;
  puerto_destino = pd;
  nombre_destino = nd;
}

std::string Registro::getFecha() const { return fecha; }

std::string Registro::getNombreOrigen() const {
  std::vector<std::string> partes;
  std::stringstream ss(nombre_origen);
  std::string elemento;

  while (std::getline(ss, elemento, '.')) {
    partes.push_back(elemento);
  }
  return partes[0];
}



std::string Registro::getNombreDestino() const {
  std::vector<std::string> partes;
  std::stringstream ss(nombre_destino);
  std::string elemento;

  while (std::getline(ss, elemento, '.')) {
    partes.push_back(elemento);
  }
  return partes[0];
}

std::string Registro::getNombreDestino2() const { return nombre_destino; }

std::string Registro::getNombreOrigen2() const { return nombre_origen; }


std::string Registro::IPredInterna(const std::vector<Registro>& registros) const {
    for (const Registro& registro : registros) {
        if (registro.ip_origen != "-") {
            std::vector<std::string> partes;
            std::stringstream ss(registro.ip_origen);
            std::string elemento;

            while (std::getline(ss, elemento, '.')) {
                partes.push_back(elemento);
            }

            std::string concatenated;
            for (int i = 0; i < 3; ++i) {
                if (i != 2) {
                    concatenated += partes[i];
                    concatenated += ".";
                } else {
                    concatenated += partes[i];
                }
            }

            return concatenated;
        }
    }

    return "No se encontró dirección de origen.";
}


/*
std::string Registro::IPredInterna(const std::vector<Registro>& registros) const {
  for (const Registro& registro : registros)
    {
    if (registro.ip_origen != "-") {
  
      std::vector<std::string> partes;
      std::stringstream ss(registro.ip_origen);
      std::string elemento;
  
      while (std::getline(ss, elemento, '.')) {
        partes.push_back(elemento);
      }
  
      std::string concatenated;
      for (int i = 0; i < 3; ++i) {
        if (i != 2) {
          concatenated += partes[i];
          concatenated += ".";
        } else {
          concatenated += partes[i];
        }
      }
  
      return concatenated;
    
    } 
    }
  else {
    return "No se encontró dirección de origen.";
  }
}
*/
std::string Registro::getIPorigen2() const { return ip_origen; }

std::string Registro::getIPdestino() const { return ip_destino; }

std::string Registro::getPuertoDestino() const { return puerto_destino; }

bool Registro::compara_fecha_asc(Registro a, Registro b) {
  return a.fecha < b.fecha;
}

bool Registro::compara_fecha_eq(Registro a, Registro b) {
  return a.fecha == b.fecha;
}

std::ostream &operator<<(std::ostream &os, const Registro &registro) {
  os << registro.fecha << " | ";
  os << registro.hora << " | ";
  os << registro.ip_origen << " | ";
  os << registro.puerto_origen << " | ";
  os << registro.nombre_origen << " | ";
  os << registro.ip_destino << " | ";
  os << registro.puerto_destino << " | ";
  os << registro.nombre_destino;

  os << std::endl;

  return os;
}

bool Registro::operator<=(const Registro &other) const {
  // Descomponer las fechas en día, mes y año
  std::vector<int> dateComponents = ParseDate(fecha);
  std::vector<int> otherComponents = ParseDate(other.fecha);

  // Comparar años
  if (dateComponents[2] != otherComponents[2]) {
    return dateComponents[2] <= otherComponents[2];
  }

  // Comparar meses
  if (dateComponents[1] != otherComponents[1]) {
    return dateComponents[1] <= otherComponents[1];
  }

  // Comparar días
  return dateComponents[0] <= otherComponents[0];
}

bool Registro::operator!=(const Registro &other) const {
  return this->ip_origen != other.ip_origen ||
         this->ip_destino != other.ip_destino;
}

bool Registro::operator==(const Registro &other) const {
  return this->ip_origen == other.ip_origen ||
         this->ip_destino == other.ip_destino;
}

// Función para descomponer la fecha en día, mes y año
std::vector<int> Registro::ParseDate(const std::string &date) const {
  std::vector<int> dateComponents;
  std::stringstream ss(date);
  std::string token;

  while (std::getline(ss, token, '-')) {
    dateComponents.push_back(std::stoi(token));
  }

  return dateComponents;
}

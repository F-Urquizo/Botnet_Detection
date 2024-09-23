#include "LecturaCSV.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

std::vector<Registro> leerArchivoCSV(const std::string& nombreArchivo) {
    std::vector<Registro> registros;

    std::ifstream fs(nombreArchivo);
    std::string line;

    while (getline(fs, line)) {
        std::stringstream ss(line);
        std::string entrada;
        std::vector<std::string> datos;

        while (getline(ss, entrada, ',')) {
            datos.push_back(entrada);
        }

        if (datos.size() == 8) {
            Registro registro;
            registro.set_data(datos[0], datos[1], datos[2], datos[3], datos[4],
                            datos[5], datos[6], datos[7]);
            registros.push_back(registro);
        } else {
            std::cerr << "Error: número incorrecto de campos en la línea: " << line
                    << std::endl;
        }
    }

    fs.close();

    return registros;
}
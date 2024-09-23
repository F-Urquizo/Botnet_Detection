#ifndef CSV_READER_HPP
#define CSV_READER_HPP

#include "Registro.hpp"
#include <vector>

std::vector<Registro> leerArchivoCSV(const std::string& nombreArchivo);

#endif /* CSV_READER_HPP */

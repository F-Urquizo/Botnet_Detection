#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include <vector>
#include "Registro.hpp" // Include the necessary header for Registro if needed

class MergeSort {
public:
    static void merge(std::vector<Registro>& vec, int l, int m, int r);
    static void mergeSort(std::vector<Registro>& vec, int l, int r);
};

#endif
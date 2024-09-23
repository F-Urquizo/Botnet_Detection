#include "MergeSort.hpp"

void MergeSort::merge(std::vector<Registro>& vec, int l, int m, int r) {
  int n1 = m - l + 1;
      int n2 = r - m;
  
      std::vector<Registro> L(n1);
      std::vector<Registro> R(n2);
  
      for (int i = 0; i < n1; i++)
          L[i] = vec[l + i];
      for (int j = 0; j < n2; j++)
          R[j] = vec[m + 1 + j];
  
      int i = 0;
      int j = 0;
      int k = l;
  
      while (i < n1 && j < n2) {
          if (L[i] <= R[j]) { // Comparación por fecha
              vec[k] = L[i];
              i++;
          } else {
              vec[k] = R[j];
              j++;
          }
          k++;
      }
  
      while (i < n1) {
          vec[k] = L[i];
          i++;
          k++;
      }
  
      while (j < n2) {
          vec[k] = R[j];
          j++;
          k++;
      }
}

void MergeSort::mergeSort(std::vector<Registro>& vec, int l, int r) {
      if (l >= r)
          return;
  
      int m = l + (r - l) / 2;
      mergeSort(vec, l, m);
      mergeSort(vec, m + 1, r);
      merge(vec, l, m, r);
}
#include <Rcpp.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <functional>

using namespace std;
using namespace Rcpp;

typedef vector<int> StdVector;

// Funció per llegir el fitxer i omplir el vector
// [[Rcpp::export]]
StdVector llegirFitxer(const string& path) {
  ifstream file(path);
  if (!file) {
    Rcpp::Rcerr << "Error: File not found" << endl;
  }
  StdVector vector;
  int value;
  while (file >> value) {
    vector.push_back(value);
  }
  file.close();
  return vector;
}

// Algorisme QuickSort
// [[Rcpp::export]]
void quickSort(StdVector& vec, int low, int high) {
  if (low < high) {
    int pivot = vec[high];
    int i = low - 1;
    
    for (int j = low; j <= high - 1; j++) {
      if (vec[j] <= pivot) {
        i++;
        swap(vec[i], vec[j]);
      }
    }
    swap(vec[i + 1], vec[high]);
    
    quickSort(vec, low, i);
    quickSort(vec, i + 2, high);
  }
}

// Algorisme MergeSort
// [[Rcpp::export]]
void mergeSort(StdVector& vec, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSort(vec, left, mid);
    mergeSort(vec, mid + 1, right);
    
    // Merging sorted halves
    vector<int> leftVec(mid - left + 1), rightVec(right - mid);
    for (int i = 0; i < leftVec.size(); ++i) leftVec[i] = vec[left + i];
    for (int i = 0; i < rightVec.size(); ++i) rightVec[i] = vec[mid + 1 + i];
    
    int i = 0, j = 0, k = left;
    while (i < leftVec.size() && j < rightVec.size()) {
      if (leftVec[i] <= rightVec[j]) {
        vec[k++] = leftVec[i++];
      } else {
        vec[k++] = rightVec[j++];
      }
    }
    
    while (i < leftVec.size()) {
      vec[k++] = leftVec[i++];
    }
    
    while (j < rightVec.size()) {
      vec[k++] = rightVec[j++];
    }
  }
}

// Algorisme BubbleSort
// [[Rcpp::export]]
void bubbleSort(StdVector& vec) {
  int n = vec.size();
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (vec[j] > vec[j + 1]) {
        swap(vec[j], vec[j + 1]);
      }
    }
  }
}

// Algorisme SelectionSort
// [[Rcpp::export]]
void selectionSort(StdVector& vec) {
  int n = vec.size();
  for (int i = 0; i < n - 1; i++) {
    int min_idx = i;
    for (int j = i + 1; j < n; j++) {
      if (vec[j] < vec[min_idx]) {
        min_idx = j;
      }
    }
    swap(vec[i], vec[min_idx]);
  }
}

// Algorisme InsertionSort
// [[Rcpp::export]]
void insertionSort(StdVector& vec) {
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    auto const insertion_point = std::upper_bound(vec.begin(), it, *it);
    std::rotate(insertion_point, it, it + 1);
  }
}

// Funció per mesurar el temps d'execució d'una funció concreta
// [[Rcpp::export]]
long long medirTempsQuickSort(StdVector& vec, const string& name) {
  auto start = chrono::high_resolution_clock::now();
  quickSort(vec, 0, vec.size() - 1);
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
  Rcpp::Rcout << name << " - Temps: " << duration.count() << " ns" << endl;
  return duration.count();
}

// Funció per mesurar el temps d'execució de MergeSort
// [[Rcpp::export]]
long long medirTempsMergeSort(StdVector& vec, const string& name) {
  auto start = chrono::high_resolution_clock::now();
  mergeSort(vec, 0, vec.size() - 1);
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
  Rcpp::Rcout << name << " - Temps: " << duration.count() << " ns" << endl;
  return duration.count();
}

// Funció per mesurar el temps d'execució de BubbleSort
// [[Rcpp::export]]
long long medirTempsBubbleSort(StdVector& vec, const string& name) {
  auto start = chrono::high_resolution_clock::now();
  bubbleSort(vec);
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
  Rcpp::Rcout << name << " - Temps: " << duration.count() << " ns" << endl;
  return duration.count();
}

// Funció per mesurar el temps d'execució de SelectionSort
// [[Rcpp::export]]
long long medirTempsSelectionSort(StdVector& vec, const string& name) {
  auto start = chrono::high_resolution_clock::now();
  selectionSort(vec);
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
  Rcpp::Rcout << name << " - Temps: " << duration.count() << " ns" << endl;
  return duration.count();
}

// Funció per mesurar el temps d'execució de InsertionSort
// [[Rcpp::export]]
long long medirTempsInsertionSort(StdVector& vec, const string& name) {
  auto start = chrono::high_resolution_clock::now();
  insertionSort(vec);
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
  Rcpp::Rcout << name << " - Temps: " << duration.count() << " ns" << endl;
  return duration.count();
}

// Funció per mesurar la memòria ocupada pel vector (en bytes)
// [[Rcpp::export]]
size_t mesurarMemoria(const StdVector& vec) {
  // Mida del vector + mida dels elements
  size_t mem = sizeof(vec);  // Mida de l'estructura del vector
  mem += vec.size() * sizeof(int);  // Mida de tots els elements
  return mem;
}
// Funció per mesurar la memòria utilitzada per MergeSort
// Aquest mètode estima la memòria en funció dels subconjunts creats durant la recursió.
// [[Rcpp::export]]
double medirMemoriaMergeSort(StdVector& vec) {
  int n = vec.size();
  
  // La memòria utilitzada per MergeSort és aproximadament
  // el nombre total d'elements en les divisions recursives,
  // més la memòria per les subdivisions temporals durant el merge.
  
  double total_memoria = 0.0;
  
  // El nombre màxim de nivells de recursió es basa en la mida del vector
  int max_levels = std::log2(n) + 1;  // afegir 1 per nivell base
  
  // Afegir memòria per cada nivell de recursió (subdivisions temporals)
  for (int level = 0; level < max_levels; ++level) {
    total_memoria += n / std::pow(2, level);  // Afegir memòria per cada nivell
  }
  
  // Afegir memòria pels elements de les divisions (subvector)
  total_memoria += n;  // Aquest n és per a la divisió final de l'array
  
  // A cada nivell, MergeSort crea temporals per fusionar les parts
  // Així que, al final, la memòria total és proporcional al nombre total d'elements.
  return total_memoria * sizeof(int);  // Multiplicar pel nombre d'elements del vector
}

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

void selectionSort(std::vector<int>& arreglo) {
    int n = arreglo.size();
    for (int i = 0; i < n-1; i++) {
        int minimo = i;
        for (int j = i+1; j < n; j++) {
            if (arreglo[j] < arreglo[minimo]) {
                minimo = j;
            }
        }
        std::swap(arreglo[i], arreglo[minimo]);
    }
}

std::vector<int> Leer(const std::string& archivo) {
    std::ifstream infile(archivo);
    std::vector<int> arreglo;
    int value;
    while (infile >> value) {
        arreglo.push_back(value);
    }
    return arreglo;
}

void Escribir(const std::vector<int>& arreglo, const std::string& archivo) {
    std::ofstream outfile(archivo);
    for (const int& value : arreglo) {
        outfile << value << " ";
    }
}

int main() {
    std::string NombreIn = "InputCienMil.txt"; // Archivo con los datos de entrada, cambiar el nombre para probar con otros archivos
    std::string NombreOut = "InputOrdenado.txt";
    
    std::vector<int> arreglo = Leer(NombreIn);

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    selectionSort(arreglo);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Tiempo de Selection Sort: " << elapsed.count() << " segundos" << std::endl;

    Escribir(arreglo, NombreOut);

    return 0;
}


#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm> // Para std::sort
#include <chrono>    // Para medir el tiempo de ejecución

using namespace std;
using namespace std::chrono;

int main() {
    // Abrir archivo de entrada
    ifstream inputFile("SemiOrdenadoUnMillon.txt"); // Cambiar el nombre del archivo según el caso
    if (!inputFile) {
        cerr << "No se pudo abrir el archivo input.txt" << endl;
        return 1;
    }

    // Leer los números del archivo
    vector<int> arreglo;
    int num;
    while (inputFile >> num) {
        arreglo.push_back(num);
    }
    inputFile.close();

    // Medición del tiempo de ejecución
    high_resolution_clock::time_point start = high_resolution_clock::now();
    
    // Usar la función sort de la biblioteca estándar
    sort(arreglo.begin(), arreglo.end());
    
    high_resolution_clock::time_point stop = high_resolution_clock::now();

    std::chrono::microseconds duration = duration_cast<std::chrono::microseconds>(stop - start);

    // Escribir el arreglo ordenado en el archivo de salida
    ofstream outputFile("output.txt");
    if (!outputFile) {
        cerr << "No se pudo abrir el archivo output.txt" << endl;
        return 1;
    }

    for (int i = 0; i < arreglo.size(); i++) {
        outputFile << arreglo[i] << " ";
    }
    outputFile.close();

    cout << "Tiempo de ejecución: " << duration.count() << " microsegundos" << endl;

    return 0;
}
